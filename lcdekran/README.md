# LCD and LM35 Temperature Projects

This folder has LCD and LM35 examples.
Each sketch is small and easy to test.

## Sketches
| Sketch | What it does |
|---|---|
| lcdekran.ino | Shows text on LCD |
| lcd_plus_heat_all/lcd_plus_heat_Sensor/lcd_plus_heat_Sensor.ino | Shows Celsius |
| lcd_plus_heat_all/lcd_celcius_fahreinheight/lcd_c_f_sensor.ino | Shows Celsius and Fahrenheit |
| lcd_plus_heat_all/lcd_celcius_kelvin_fahreinheight_display/lcd_c_k_f_sensor.ino | Shows C, K, F and controls 2 LEDs |

## Wiring
### I2C LCD (UNO)
- VCC -> 5V
- GND -> GND
- SDA -> A4
- SCL -> A5

### LM35
- VCC -> 5V
- VOUT -> A0
- GND -> GND

## Temperature Math
1. raw = analogRead(A0)
2. voltage = raw * (5.0 / 1023.0)
3. tempC = voltage * 100.0
4. tempF = (tempC * 9.0 / 5.0) + 32.0
5. tempK = tempC + 273.15

Why 1023:
UNO ADC range is 0 to 1023.

## Common Problems
| Problem | Check |
|---|---|
| LCD is blank | Try 0x27 or 0x3F address |
| Wrong temperature | Check LM35 pin direction |
| Flickering values | Check wire quality and GND |
