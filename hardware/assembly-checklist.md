# Assembly & Bring-Up Checklist

1. **Dry fit**: place modules to keep short, wide motor traces and separate logic area.
2. **Power first**: connect battery → buck (5 V) → verify 5.0 V with multimeter.
3. **ATmega alone**: power the MCU, confirm ~5 V on VCC/AVCC, RESET pulled up, 16 MHz oscillating.
4. **Upload a blink** (D13) to prove MCU and power are OK.
5. **Add L298N**: test each motor channel with a tiny sketch (no sensors).
6. **Add sensors**: read IR digital pins; adjust onboard pots until black = ACTIVE state.
7. **Ultrasonic**: verify distance reading is sane (serial prints) before full integration.
8. **Cable management**: twist motor wires; keep sensor wires away from motor leads.
9. **Final test**: with wheels off floor, verify forward/turn/brake, then try on track.
