/*  Line Follower + Obstacle Stop (ATmega328P / Arduino Uno)
 *  Board: Arduino Uno (ATmega328P @16MHz)
 *  Motor driver: L298N (ENA/ENB = PWM)
 *  IR sensors: 2 or 3 (active LOW on black line)
 *  Ultrasonic: HC-SR04  (stop if obstacle < OBST_CM)
 *  License: MIT (see LICENSE)
 */

// ---------------- user options ----------------
#define USE_THREE_SENSORS   false   // true = 3-sensor array, false = 2-sensor
#define OBST_CM             18      // stop if obstacle closer than this (cm)
#define BASE_PWM            140     // straight speed (0–255)
#define TURN_PWM            115     // inside wheel during correction
#define FAST_LOOP_HZ        200     // control loop frequency
// (If your IR boards output HIGH on black, flip ACTIVE_LOW below)
#define ACTIVE_LOW          true

// ---------------- pin mapping -----------------
// L298N
const uint8_t ENA = 5;   // PWM right
const uint8_t ENB = 6;   // PWM left
const uint8_t IN1 = 7;   // right dir1
const uint8_t IN2 = 8;   // right dir2
const uint8_t IN3 = 9;   // left  dir1
const uint8_t IN4 = 10;  // left  dir2
// IR sensors (change if needed)
const uint8_t IR_L  = A1;
const uint8_t IR_R  = A2;
const uint8_t IR_C  = A0;  // center (only if USE_THREE_SENSORS)
// Ultrasonic
const uint8_t US_TRIG = 3;
const uint8_t US_ECHO = 2; // INT0-capable but we’ll poll non-blocking
// Status LED (optional)
const uint8_t LED_OBS = 13;

// ------------------------------------------------

inline bool irRead(uint8_t pin) {
  // normalize: return true when "on black line"
  int v = digitalRead(pin);
  return ACTIVE_LOW ? (v == LOW) : (v == HIGH);
}

void motorSet(int leftPWM, int rightPWM) {
  // direction from sign, magnitude from abs
  int lp = constrain(abs(leftPWM), 0, 255);
  int rp = constrain(abs(rightPWM), 0, 255);

  if (leftPWM >= 0) { digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
  else              { digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH); }

  if (rightPWM >= 0){ digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); }
  else              { digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH); }

  analogWrite(ENB, lp);
  analogWrite(ENA, rp);
}

void motorBrake() {
  // active brake (both lows on EN, both highs on H-bridge sides)
  digitalWrite(IN1, LOW);  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);     analogWrite(ENB, 0);
}

// Non-blocking ultrasonic (median of N quick pings optional)
unsigned long pingCM() {
  // short trigger
  digitalWrite(US_TRIG, LOW); delayMicroseconds(2);
  digitalWrite(US_TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(US_TRIG, LOW);

  // pulseIn with short timeout to keep loop snappy
  unsigned long dur = pulseIn(US_ECHO, HIGH, 20000UL); // 20 ms ~ 3.4 m
  if (dur == 0) return 999; // timeout => no object
  // convert us to cm (sound ~ 343 m/s): cm = us / 58.0
  return dur / 58UL;
}

enum TrackState { TRACK_CENTER, TRACK_LEFT, TRACK_RIGHT, TRACK_LOST };

TrackState readTrack() {
  bool L = irRead(IR_L);
  bool R = irRead(IR_R);
  if (USE_THREE_SENSORS) {
    bool C = irRead(IR_C);
    if (C && !L && !R) return TRACK_CENTER;
    if (L && !C)       return TRACK_LEFT;
    if (R && !C)       return TRACK_RIGHT;
    if (L && R && C)   return TRACK_CENTER;   // all on line at junction
  } else {
    if (L && R)   return TRACK_CENTER;
    if (L && !R)  return TRACK_LEFT;
    if (!L && R)  return TRACK_RIGHT;
  }
  return TRACK_LOST;
}

void setup() {
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  pinMode(IR_L, INPUT_PULLUP);
  pinMode(IR_R, INPUT_PULLUP);
  if (USE_THREE_SENSORS) pinMode(IR_C, INPUT_PULLUP);

  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
  pinMode(LED_OBS, OUTPUT);

  motorBrake();
}

void loop() {
  static unsigned long tLoop = 0;
  const unsigned long dt = 1000UL / FAST_LOOP_HZ;
  const uint8_t base = BASE_PWM;
  const uint8_t turn = TURN_PWM;

  if (millis() - tLoop >= dt) {
    tLoop += dt;

    // 1) obstacle check (every Nth cycle to save time)
    static uint8_t obstDiv = 0;
    static unsigned long lastCM = 999;
    if (++obstDiv >= 5) { // ~40 Hz if FAST_LOOP_HZ=200
      obstDiv = 0;
      lastCM = pingCM();
    }
    bool blocked = (lastCM <= OBST_CM);
    digitalWrite(LED_OBS, blocked ? HIGH : LOW);

    if (blocked) {
      motorBrake();
      return;
    }

    // 2) line following
    TrackState st = readTrack();
    switch (st) {
      case TRACK_CENTER:
        motorSet(base, base);
        break;
      case TRACK_LEFT:   // line under left sensor => steer left
        motorSet(turn, base);
        break;
      case TRACK_RIGHT:  // line under right sensor => steer right
        motorSet(base, turn);
        break;
      case TRACK_LOST:
      default:
        // slow search: rotate gently to find line again
        motorSet(+90, -90);
        break;
    }
  }
}
