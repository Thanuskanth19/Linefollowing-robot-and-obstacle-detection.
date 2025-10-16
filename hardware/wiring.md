# Wiring & Pin Map (ATmega328P + L298N + HC-SR04 + IR Sensors)

> Matches `firmware/src/main.ino`. If your build differs, edit here.

## Power
- Battery: 2×18650 pack (≈7.4–8.4 V) → **L298N 12V/VIN** (or 2-cell JST).
- Onboard 5 V for logic:
  - Option A (recommended): **Buck converter** (e.g., MP1584, set to 5.0 V) → 5V rail.
  - Option B: **L298N 5V-EN** regulator (only if your board provides a stable 5 V and current < 500 mA).
- **ATmega328P VCC/AVCC = 5 V**, **GND common** with all modules.
- **HC-SR04** and **IR sensors** powered from 5 V.

> Add a 1 A fuse on battery + line and a power switch. Keep motor power and logic power traces separated until they meet at the star ground.

## Motor Driver (L298N)
| L298N Pin | Arduino/ATmega328P | Notes |
|---|---|---|
| ENA (Right PWM) | D5 | PWM speed right motor |
| IN1 | D7 | Right dir1 |
| IN2 | D8 | Right dir2 |
| IN3 | D9 | Left dir1 |
| IN4 | D10 | Left dir2 |
| ENB (Left PWM) | D6 | PWM speed left motor |
| 12V/VIN | Battery + | 7–12 V ok |
| GND | Battery − & Logic GND | Common ground |
| 5V (if present) | 5 V rail (optional) | Use only if stable |

> If motors spin backward, swap IN1/IN2 (right) or IN3/IN4 (left).

## IR Line Sensors (digital)
Active LOW on black line (most modules). Use `INPUT_PULLUP`.
| Sensor | Pin | Notes |
|---|---|---|
| IR_LEFT | A1 | With pull-up |
| IR_RIGHT | A2 | With pull-up |
| IR_CENTER (optional) | A0 | Enable `USE_THREE_SENSORS=true` in code |

> If your sensors are HIGH on black, set `ACTIVE_LOW=false`.

## Ultrasonic Sensor (HC-SR04)
| HC-SR04 | Pin |
|---|---|
| TRIG | D3 |
| ECHO | D2 (INT0 capable) |
| VCC | 5 V |
| GND | GND |

## Status & Controls
| Signal | Pin | Notes |
|---|---|---|
| LED_OBS | D13 | Obstacle indicator |
| MODE/Button (optional) | A3 | Use `INPUT_PULLUP` (to GND when pressed) |

## ATmega328P Essentials
- 16 MHz crystal + 22 pF caps to GND (or use internal if bootloaded accordingly).
- 0.1 µF decoupling at VCC, AVCC; 10 µF bulk near 5 V rail.
- AVCC tied to 5 V via ferrite bead or 10 Ω (optional noise isolation).
- RESET via 10 kΩ to 5 V; 100 nF from RESET to GND optional for stability.
