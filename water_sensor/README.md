# Water Sensor Project

This project reads water level and shows one value on LCD.
It also lights one of four level LEDs.

## Sketch
- water/water.ino

## Wiring
### Water sensor
- VCC -> 5V
- GND -> GND
- AOUT -> A0

### I2C LCD
- VCC -> 5V
- GND -> GND
- SDA -> A4
- SCL -> A5

### Level LEDs
- Level 1 -> D2
- Level 2 -> D3
- Level 3 -> D4
- Level 4 -> D5

## Logic
- 0 to 100 -> LED1
- 101 to 400 -> LED2
- 401 to 700 -> LED3
- 701+ -> LED4

## Important Note
Current code sets pinMode for 1,2,3,4 but writes to 2,3,4,5.
Add pinMode(5, OUTPUT) and remove pin 1 for consistent behavior.

## Common Problems
| Problem | Check |
|---|---|
| No LED on | Check water sensor output and GND |
| Wrong level LED | Check threshold values |
| LCD does not update | Check I2C address and wiring |
