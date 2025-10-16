# Bill of Materials (BOM)

| Item | Qty | Example Part | Notes |
|---|---:|---|---|
| ATmega328P-PU (with Uno bootloader or bare) | 1 | ATmega328P-PU | Use DIP for perfboard |
| 16 MHz crystal + 22 pF capacitors | 1 + 2 | HC-49 | Optional if using external crystal |
| L298N motor driver module | 1 | Standard red module | TB6612FNG is a lighter, more efficient alternative |
| DC Gear Motors + Wheels | 2 | 6 V–12 V, 120–200 RPM | JGB37-555 or TT motors |
| IR line sensors (digital) | 2–3 | TCRT5000 modules | 3 sensors recommended for better tracking |
| Ultrasonic sensor | 1 | HC-SR04 | — |
| Battery holder | 1 | 2×18650 | With switch if possible |
| 18650 cells | 2 | 2000–3000 mAh | Use good quality cells |
| Buck converter (recommended) | 1 | MP1584 / LM2596 | Set to 5.0 V for logic |
| LEDs + resistors | 2–3 | 5 mm + 220 Ω | Status |
| Push button | 1 | 6×6 mm tact | Mode/reset |
| Perfboard or custom PCB | 1 | 7×9 cm | As in your build |
| Headers, jumpers, wires | — | — | Dupont or screw terminals |
| Capacitors | several | 0.1 µF, 10 µF | Decoupling & bulk |
| Fuse + holder (recommended) | 1 | 1 A fast | Battery protection |

**Optional upgrades**
- TB6612FNG driver (cooler, lower voltage drop)
- 5-sensor array + PID
- Wheel encoders for closed-loop speed
