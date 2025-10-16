# Schematic Notes (KiCad/Fritzing)

- **Blocks**: Battery & switch → Buck 5 V → MCU, Sensors, L298N (VIN direct).
- **Nets**:
  - `VBAT` (~8.4–7.0 V), `+5V`, `GND`.
  - Digital nets per `wiring.md` table.
- **Symbols**:
  - ATmega328P-PU (DIP-28), 16 MHz crystal + 22 pF to GND on XTAL1/2.
  - L298N module header (ENA, IN1, IN2, IN3, IN4, ENB, VIN, 5V, GND).
  - HC-SR04 (VCC, TRIG, ECHO, GND).
  - IR modules (VCC, GND, DOUT) × 2 or 3.
- **Decoupling**: 0.1 µF at MCU VCC/AVCC; 100 µF on +5 V near MCU; 100 µF on VIN near L298N.
- **Connectors**: Use polarized headers or screw terminals for motors and battery.
