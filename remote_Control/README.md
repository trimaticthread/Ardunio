# Remote Control Projects — Week 5

IR (infrared) remote control sketches built during Week 5 of the Arduino course.
The goal was to control a servo motor and LEDs by pressing buttons on an IR remote.

> **Note:** This section will be updated by Efe in the future.

## Hardware Used

| Component | Pin |
|---|---|
| IR Receiver (VS1838B) | Digital Pin 3 — DATA (left leg) |
| Red LED | Digital Pin 2 |
| Green LED | Digital Pin 4 |
| Servo Motor | Digital Pin 9 |
| LCD I2C (16×2) | SDA = A4, SCL = A5 — I2C address: 0x27 |

> **IR Sensor Wiring (flat face toward you):**
> Left leg → DATA (Digital Pin 3) | Middle leg → GND | Right leg → VCC (5V)

> ⚠️ **Do NOT use Pin 0 or Pin 1 for LEDs.** These are the RX/TX Serial pins and the
> bootloader holds them HIGH at startup, which will light up any connected LED.

## Projects

### `remote_lcd_servo_led/` — Password Lock with IR Remote
A 4-digit password entry system using an IR remote.

- Press digit keys (0–9) to enter the password — each digit shows as `*` on LCD line 2
- Press **EQ / PLAY / CH+** to confirm
- Press **CH− / CH / 100+ / 200+** to clear input
- **Correct password** → green LED on, servo opens to 90°, waits 3 s, closes back to 0°
- **Wrong password** → red LED on for 2 s

**Password:** `9966` (change the `sifre` variable in the sketch)

**Remote HEX codes used:**

| Key | HEX |
|---|---|
| 0 | 0x68 |
| 1 | 0x30 |
| 2 | 0x18 |
| 3 | 0x7A |
| 4 | 0x10 |
| 5 | 0x38 |
| 6 | 0x5A |
| 7 | 0x42 |
| 8 | 0x4A |
| 9 | 0x52 |
| EQ (confirm) | 0x90 |
| PLAY (confirm) | 0xC2 |
| CH+ (confirm) | 0xE2 |
| CH− (clear) | 0xA2 |

### `ir_kod_test/` — IR Receiver Debug Sketch
Minimal sketch that prints every received IR command to the Serial Monitor.
Use this to find the HEX codes of any IR remote before writing the main sketch.

**Steps:**
1. Upload `ir_kod_test.ino`
2. Open Serial Monitor at 9600 baud
3. Press each button on the remote
4. Copy the printed HEX values into the main sketch

## Libraries Required
- `IRremote` (v3.x) — included under `libraries/IRremote`
- `LiquidCrystal_I2C`
- `Servo` (built-in)

## Common Problems

| Problem | Fix |
|---|---|
| IR sensor constantly LOW / noise spam | Sensor is likely damaged from reversed VCC/GND — replace it |
| Both LEDs on at startup | Green LED is on Pin 0 or Pin 1 (TX/RX) — move to Pin 4 or higher |
| Serial Monitor shows nothing | Check baud rate is 9600; make sure `Serial.begin(9600)` is in setup() |
| Servo doesn't move | Check servo signal wire is on the correct pin; servo needs its own 5V supply for heavy loads |
