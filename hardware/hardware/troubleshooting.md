# Troubleshooting

- **Random resets / jitter** → Add bulk caps, separate grounds, use a buck for logic.
- **Motors only one direction** → Check IN1..IN4 wiring; L298N ENA/ENB must be PWM pins.
- **No line detection** → Polarity mismatch; set `ACTIVE_LOW` accordingly; adjust IR pots.
- **Ultrasonic always 0 or 999 cm** → ECHO on D2, TRIG on D3; avoid long echo timeouts; check 5 V.
- **Crooked drive** → Different motor speeds; increase `TURN_PWM` or trim PWM left/right.
