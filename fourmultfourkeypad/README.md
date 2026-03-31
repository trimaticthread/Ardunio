# 4×4 Keypad Projects — Week 5

Sketches built during Week 5 using a 4×4 matrix keypad.
The theme of Week 5 was modern security systems — password locks, access control, and servo-based door mechanisms.

## Hardware Used

| Component | Pins |
|---|---|
| 4×4 Keypad | Row: D9, D8, D7, D6 — Col: D5, D4, D3, D2 |
| LCD I2C (16×2) | SDA = A4, SCL = A5 — I2C address: 0x27 |
| Green LED | D12 |
| Red LED | D13 |
| Servo Motor | D11 |

**Keypad Layout:**
```
[ 1 ][ 2 ][ 3 ][ A ]
[ 4 ][ 5 ][ 6 ][ B ]
[ 7 ][ 8 ][ 9 ][ C ]
[ * ][ 0 ][ # ][ D ]
```

## Projects

### `keypad_plus_lcd/` — Keypad + LCD Display
Basic keypad input — every pressed key is printed on the LCD and Serial Monitor.
Good starting point for understanding keypad reading.

### `keypad_lcd_password_leds/` — Password Lock (LEDs only)
4-digit password entry with LED feedback.
- `#` → check password
- `*` → clear input
- Correct: green LED (D12) on for 3 s
- Wrong: red LED (D13) on for 2 s
- **Password:** `1234`

### `keypad_lcd_pass_led_servo/` — Password Lock (LEDs + Servo)
Same as above but also drives a servo motor when the password is correct.
- Correct: green LED + servo sequence (0° → 90° → 100°)
- **Password:** `1234`

### `entry/` — Entry / Draft Sketch
Early draft used during the first run of keypad experiments.

## Libraries Required
- `Keypad` — included under `libraries/Keypad`
- `LiquidCrystal_I2C`

## Common Problems

| Problem | Fix |
|---|---|
| No key detected | Recheck row/column pin order on the keypad header |
| LCD blank | Try I2C address 0x3F instead of 0x27 |
| Random characters | Debounce or check for loose keypad ribbon |
