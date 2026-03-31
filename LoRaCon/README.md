# LoRa Communication Projects — Week 7

Sketches built during Week 7 after the instructor provided LoRa (E32) modules.
LoRa (Long Range) is a wireless protocol designed for low-power, long-distance data
transmission — commonly used in IoT and sensor networks.

## Hardware Used

| Component | Connection |
|---|---|
| LoRa E32 Module | TX → D10 (Arduino RX) / RX → D11 (Arduino TX) via SoftwareSerial |
| UV Sensor (analog) | Analog Pin A0 |
| MQ Gas Sensor (analog) | Analog Pin A0 |

> The image `loratransmitter.jpeg` shows the physical wiring of the transmitter setup.

## Packet Structure

All sketches share the same `Payload` struct sent over LoRa:

```cpp
struct Payload {
  char router[4];   // Router ID (e.g. "105", "106")
  char sensor[5];   // Sensor ID (e.g. "1005", "1006")
  char dataKey[4];  // Data label (e.g. "UV", "GAS", "CON")
  float dataValue;  // Measured value
};
```

Destination address: **ADDH=0, ADDL=52, Channel=23**
Send interval: **10 seconds** (non-blocking, uses `millis()`)

---

## Projects

### `LoRaCon.ino` — Basic LoRa Transmitter
Sends a fixed hardcoded data packet every 5 seconds. Used as the first working test.

- Packet: type `"Router 59"`, value `19.2` (simulated temperature)
- Good starting point to verify the LoRa module and wiring work

### `LoRa_UVSensor/` — LoRa + UV Sensor Transmitter
Reads a UV sensor on **A0** and transmits the raw ADC value over LoRa every 10 seconds.

- **Router ID:** `106` | **Sensor ID:** `1006`
- Data key sent: `"UV"`, value: raw analogRead (0–1023)
- Serial Monitor prints: Router ID, Sensor ID, key, value, and send status

**Wiring:**

| UV Sensor Pin | Arduino |
|---|---|
| OUT / SIG | A0 |
| VCC | 5V |
| GND | GND |

### `LoRa_MHMQGasSensor/` — LoRa + MQ Gas Sensor Transmitter
Reads an MQ-series gas sensor on **A0** and sends two packets every 10 seconds:
1. Raw ADC reading → key `"GAS"`
2. Mapped concentration (0–1000 ppm scale) → key `"CON"`

- **Router ID:** `105` | **Sensor ID:** `1005`
- Concentration formula: `map(gasValue, 0, 1023, 0, 1000)`

**Wiring:**

| MQ Sensor Pin | Arduino |
|---|---|
| AOUT / A0 | A0 |
| VCC | 5V |
| GND | GND |

> ⚠️ MQ sensors require a **warm-up time of ~60–120 seconds** after power-on for accurate readings.

### `efenincalisankodu/` — Efe's Working Reference Code
A verified working version of the LoRa transmitter. Use this as the reference implementation.

---

## Library Required
- `LoRa_E32` — EByte E32 library (must be installed manually)
- `SoftwareSerial` — built into Arduino IDE

## Key Concepts

| Term | Meaning |
|---|---|
| LoRa | Long Range — spread-spectrum wireless at 433 / 868 / 915 MHz |
| E32 | EByte E32 UART LoRa module used in this project |
| SoftwareSerial | Emulates a UART port on digital pins D10 / D11 |
| Fixed message | Sends to a specific address + channel, not broadcast |
| millis() | Non-blocking timer — keeps loop() running while waiting |
| map() | Scales a range: `map(x, 0, 1023, 0, 1000)` |

## Common Problems

| Problem | Fix |
|---|---|
| No Serial output | Double-check SoftwareSerial pin order (RX/TX may be swapped) |
| Send always fails | Check module power — E32 needs a stable supply (3.3 V or 5 V depending on model) |
| Garbage data received | Baud rates on both transmitter and receiver must match |
| MQ sensor reads near 0 | Allow 60–120 s warm-up time before reading |
| UV sensor always 0 | Ensure sensor is exposed to UV light and output is connected to A0 |

