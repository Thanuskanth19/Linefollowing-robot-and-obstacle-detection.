# Power & Noise Notes

- Motors inject noise; route motor currents separately from logic and join at a **star ground** near the battery negative.
- Place a **100 µF electrolytic** near the L298N VIN and a **100 µF** near the 5 V logic rail.
- Each IC/module should have a **0.1 µF** ceramic close to VCC–GND.
- If brownouts occur when motors start:
  - Increase bulk capacitance on 5 V rail (220–470 µF).
  - Use a **buck converter** for logic instead of L298N’s onboard 5 V.
  - Add **flyback diodes** if using a raw H-bridge (L298N has internal diodes).
- Battery protection: use a **1 A fuse** on the battery positive and a proper switch.
