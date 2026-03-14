# Wiring Guide for Beginners

Use this file while wiring.
Follow one rule first: all modules must share GND with Arduino.

## 1) Common GND
If GND is not shared, signals will not work correctly.

```mermaid
flowchart LR
  Arduino[Arduino UNO]
  Module[Sensor or Module]
  Arduino -->|5V| Module
  Arduino -->|GND| Module
  Arduino -->|Signal| Module
```

## 2) LED Wiring
- Arduino pin -> 220R resistor -> LED anode (+)
- LED cathode (-) -> GND

```mermaid
flowchart LR
  D5[Arduino D5] --> R[220R]
  R --> A[LED +]
  C[LED -] --> GND[GND]
```

## 3) I2C LCD Wiring (UNO)
- VCC -> 5V
- GND -> GND
- SDA -> A4
- SCL -> A5

```mermaid
flowchart LR
  V5[5V] --> LVCC[LCD VCC]
  G[GND] --> LGND[LCD GND]
  A4[A4 SDA] --> LSDA[LCD SDA]
  A5[A5 SCL] --> LSCL[LCD SCL]
```

## 4) HC-SR04 Wiring
- VCC -> 5V
- GND -> GND
- TRIG -> D9
- ECHO -> D10

## 5) LM35 Wiring
(Flat face of LM35 looks at you)
- Left pin -> 5V
- Middle pin -> A0
- Right pin -> GND

## 6) Servo Wiring
- Signal -> D9 (or sketch pin)
- VCC -> 5V
- GND -> GND

For stronger servos, use external 5V and connect its GND to Arduino GND.

## 7) Water Sensor Wiring
- VCC -> 5V
- GND -> GND
- AOUT -> A0

## 8) Quick Terms
| Term | Easy meaning |
|---|---|
| VCC | Positive power |
| GND | Ground, 0V |
| Analog | Smooth changing voltage |
| Digital | Only LOW or HIGH |
| Pull-up | Holds input HIGH when not pressed |
| Pull-down | Holds input LOW when not pressed |
