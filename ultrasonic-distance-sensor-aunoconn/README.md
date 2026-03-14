# Ultrasonic Distance Sensor (HC-SR04)

This project measures distance and prints cm value.

## File
- ultrasonic-distance-sensor-aunoconn.ino

## Wiring
- VCC -> 5V
- GND -> GND
- TRIG -> D9
- ECHO -> D10

## Formula
- distance_cm = time_us * 0.034 / 2

Why divide by 2:
The sound goes to object and comes back.

## Serial Monitor
- Baud: 9600
- Example output: Distance: 21 cm

## If it does not work
- Check TRIG and ECHO pins
- Match Serial Monitor baud to 9600
