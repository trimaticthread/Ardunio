# Arduino Learning Collection

This repository documents an Arduino course, organized week by week.
Each folder contains sketches for a specific hardware module or topic.

## Weekly Overview

| Week | Topic | Folder |
|---|---|---|
| Early weeks | LEDs, 7-segment, sensors | `one-light-blink`, `two-light-sametimeblink`, `7-digit-display`, `ultrasonic-distance-sensor-aunoconn`, `lcdekran`, `water_sensor` |
| Week 5 | Security systems — servo, keypad, IR remote | `servo-motor`, `fourmultfourkeypad`, `remote_Control` |
| Week 7 | Wireless communication — LoRa module | `LoRaCon` |

## Project List

| Folder | Description |
|---|---|
| `one-light-blink` | Blinks one LED on/off with 1 s delay |
| `two-light-sametimeblink` | Runs a 3-LED chase sequence |
| `7-digit-display` | Counts 0–9 on a 7-segment display |
| `ultrasonic-distance-sensor-aunoconn` | Measures distance with HC-SR04, prints to Serial Monitor |
| `lcdekran` | LCD text display and LM35 temperature sensor demos |
| `servo-motor` | Basic servo control: fixed angles, sweep, button-driven open/close |
| `water_sensor` | Reads water level sensor and drives threshold LEDs |
| `fourmultfourkeypad` | 4×4 keypad projects: LCD display, password lock, servo door — **Week 5** |
| `remote_Control` | IR remote control: password lock with servo + LCD — **Week 5** (to be updated by Efe) |
| `LoRaCon` | LoRa E32 basic transmitter (fixed packet every 5 s) — **Week 7** |
| `LoRaCon/LoRa_UVSensor` | LoRa + UV sensor: transmits raw analog UV reading every 10 s — **Week 7** |
| `LoRaCon/LoRa_MHMQGasSensor` | LoRa + MQ gas sensor: transmits raw value + mapped concentration every 10 s — **Week 7** |

## Quick Start
1. Install Arduino IDE.
2. Connect Arduino UNO via USB.
3. Open any `.ino` file.
4. Select **Board: Arduino UNO** and **Port: COMx**.
5. Click **Verify**, then **Upload**.
6. Open **Serial Monitor** (9600 baud) if the sketch prints output.

## Key Concepts

| Term | Meaning |
|---|---|
| VCC | +5V power |
| GND | Ground (0V) |
| HIGH / LOW | Pin ON / OFF |
| I2C | 2-wire bus — SDA (A4) + SCL (A5) on UNO |
| PWM | Pulse-width modulation — used for servo control |
| IR | Infrared — used by TV-style remote controls |
| LoRa | Long Range wireless — low power, km-scale range |

## Safety Rules
1. Unplug USB before changing wires.
2. Always connect all GND pins together.
3. Use a 220 Ω resistor in series with every LED.
4. **Never use Pin 0 (RX) or Pin 1 (TX) for LEDs** — the bootloader uses them at startup.
5. Double-check VCC/GND on IR sensors and LoRa modules before powering on.

## Common Problems

| Problem | Fix |
|---|---|
| LCD blank | Try I2C address `0x3F` instead of `0x27` |
| IR sensor always LOW | VCC/GND reversed, or sensor damaged — replace VS1838B |
| Servo jitters | Needs stable 5 V; avoid sharing supply with other loads |
| LoRa send fails | Check SoftwareSerial pin order and module supply voltage |
| Upload error | Verify correct Board and COM port in Tools menu |

## Libraries
Local copies are included under `libraries/`:
- `LiquidCrystal_I2C`
- `Servo` (also built into Arduino IDE)
- `IRremote` (v3.x)
- `Keypad`
