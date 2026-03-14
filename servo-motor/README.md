# Servo Motor Projects

This folder has simple servo examples.

## Sketches
| Sketch | What it does |
|---|---|
| servo_only_firstRun/sketch_mar10a/sketch_mar10a.ino | Moves to fixed angles |
| servo_secondRun/sketch_mar10b_servo2/sketch_mar10b_servo2.ino | Sweep style movement |
| servoledbuton/servoledbuton.ino | Buttons control servo and LEDs |

## Basic Wiring
- Signal -> D9 (or the pin in your sketch)
- VCC -> 5V
- GND -> GND

Important:
Always share GND.

## Notes
- First sketch: 0, 90, 100 degrees.
- Sweep sketch: reverse loop writes angle, forward loop misses myServo.write(pos).
- Button sketch:
  - D9 open button
  - D8 close button
  - D13 servo signal
  - D4 red LED
  - D5 green LED

Recommended:
Use INPUT_PULLUP for stable buttons.

## Common Problems
| Problem | Check |
|---|---|
| Servo jitter | Use stable power and common GND |
| No movement | Check signal pin and code angle writes |
| Random button reads | Use pull-up or pull-down |
