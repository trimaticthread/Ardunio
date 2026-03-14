# Arduino Learning Collection

This repository is for beginners.
Each folder has one small Arduino project.
You can open one project, wire it, upload it, and test it.

## What You Will Learn
- How to connect parts to Arduino UNO
- How to read sensor values
- How to print values on LCD and Serial Monitor
- How to control LED and servo outputs

## Project List
| Folder | What it does |
|---|---|
| one-light-blink | Blinks one LED |
| two-light-sametimeblink | Runs a 3-LED sequence |
| 7-digit-display | Shows numbers 0 to 9 on 7-segment |
| ultrasonic-distance-sensor-aunoconn | Measures distance with HC-SR04 |
| lcdekran | LCD text and LM35 temperature demos |
| servo-motor | Basic servo projects |
| water_sensor | Reads water level and lights level LEDs |

## Important Words
| Word | Easy meaning |
|---|---|
| VCC | +5V power line |
| GND | Ground (0V), common return line |
| HIGH | Pin is ON |
| LOW | Pin is OFF |
| ADC | Converts analog voltage to number |
| I2C | 2-wire communication (SDA, SCL) |
| Baud rate | Serial speed, must match monitor |

## Safety Rules
1. Unplug USB before changing wires.
2. Always connect all grounds together (common GND).
3. Use a 220R resistor with every LED.
4. Check pin labels before upload.

For diagrams, open: docs/WIRING_GUIDE.md

## Quick Start
1. Install Arduino IDE.
2. Connect Arduino UNO with USB.
3. Open one .ino file.
4. Select Board: Arduino UNO.
5. Select Port: COMx.
6. Click Verify, then Upload.
7. Open Serial Monitor if needed.

## Project Notes

### 1) one-light-blink/one-light-blink.ino
- LED on D5 turns ON 1 second, OFF 1 second.

### 2) two-light-sametimeblink/two-light-sametimeblink.ino
- LEDs on D5, D6, D7 run one by one.

### 3) 7-digit-display/7-digit.ino
- Segments A to G and DP are connected to D2 to D9.
- Code shows 0,1,2,...,9.
- If your display is common-anode, invert ON/OFF logic.

### 4) ultrasonic-distance-sensor-aunoconn/ultrasonic-distance-sensor-aunoconn.ino
- TRIG: D9, ECHO: D10.
- Formula: distance_cm = time_us * 0.034 / 2.
- Serial Monitor prints distance every 500 ms.

### 5) lcdekran/lcdekran.ino
- LCD shows two greeting lines.

### 6) lcdekran/lcd_plus_heat_all/lcd_plus_heat_Sensor/lcd_plus_heat_Sensor.ino
- LM35 on A0.
- Convert raw value to voltage, then to Celsius.

### 7) lcdekran/lcd_plus_heat_all/lcd_celcius_fahreinheight/lcd_c_f_sensor.ino
- Shows Celsius and Fahrenheit.

### 8) lcdekran/lcd_plus_heat_all/lcd_celcius_kelvin_fahreinheight_display/lcd_c_k_f_sensor.ino
- Shows Celsius, Kelvin, Fahrenheit.
- LED1 ON when temperature < 25C, else LED2 ON.

### 9) servo-motor/servo_only_firstRun/sketch_mar10a/sketch_mar10a.ino
- Servo goes to fixed angles (0, 90, 100).

### 10) servo-motor/servo_secondRun/sketch_mar10b_servo2/sketch_mar10b_servo2.ino
- Reverse sweep works.
- Forward loop currently misses myServo.write(pos).

### 11) servo-motor/servoledbuton/servoledbuton.ino
- Button D9 opens servo, button D8 closes servo.
- Red/green LEDs show state.

### 12) water_sensor/water/water.ino
- Reads water value from A0 and shows it on LCD.
- Turns on one of 4 LEDs by threshold.
- Note: setup pinMode list and loop digitalWrite list are not fully aligned.

## Common Problems
| Problem | What to check |
|---|---|
| LCD blank | Try I2C address 0x27 or 0x3F |
| Sensor values wrong | Check VCC/GND and pin numbers |
| Random button behavior | Use pull-up/pull-down logic |
| Upload error | Check board and COM port |

## Libraries
This repo includes local copies of:
- libraries/LiquidCrystal_I2C
- libraries/Servo
