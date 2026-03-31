# LoRa Communication Projects — Week 7

Sketches built during Week 7 after the instructor provided LoRa (E32) modules.
LoRa (Long Range) is a wireless communication protocol designed for low-power,
long-distance data transmission — commonly used in IoT and sensor networks.

## Hardware Used

| Component | Connection |
|---|---|
| LoRa E32 Module | TX→D10 (Arduino RX), RX→D11 (Arduino TX) via SoftwareSerial |
| Arduino UNO | — |

> The image `loratransmitter.jpeg` shows the physical wiring of the transmitter setup.

## Projects

### `LoRaCon.ino` — LoRa Transmitter
Sends a fixed data packet every 5 seconds using the E32 LoRa module.

- Packet type: `"Router 59"` (string label)
- Packet data: `19.2` (simulated temperature as float)
- Destination: fixed address — channel 23, address 0x0034
- Status of each send is printed to Serial Monitor

```
Gonderim durumu: Success
```

### `efenincalisankodu/` — Efe's Working Code
A verified working version of the LoRa sketch provided by Efe.
Use this as the reference implementation.

## Library Required
- `LoRa_E32` — must be installed manually from the EByte E32 library

## Key Concepts

| Term | Meaning |
|---|---|
| LoRa | Long Range — spread-spectrum wireless at 433/868/915 MHz |
| E32 | EByte E32 UART LoRa module (used in this project) |
| SoftwareSerial | Emulates a serial port on any digital pins |
| Fixed message | Sends to a specific address and channel, not broadcast |
| sendInterval | Time between packets — 5000 ms (5 seconds) |

## Common Problems

| Problem | Fix |
|---|---|
| No output on Serial Monitor | Check SoftwareSerial pin order (RX/TX may be swapped) |
| Send always fails | Check module power — E32 needs stable 3.3V or 5V (check your module version) |
| Garbage data received | Baud rates on both ends must match |
