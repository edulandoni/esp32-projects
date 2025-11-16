# 01 - LED Blink (ESP32-S3, GPIO 4)

Basic ESP32-S3 LED blink example using ESP-IDF and FreeRTOS.

## Summary

This project:

- Blinks an external LED connected to **GPIO 4** every 500 ms.
- Uses `vTaskDelay(pdMS_TO_TICKS(500))` instead of busy-wait loops.
- Prints `LED ON` / `LED OFF` messages on the serial monitor.

It is a minimal “Hello World” for ESP32-S3 + ESP-IDF.

## Hardware

- ESP32-S3 dev board
- 1× LED (red, yellow, etc.)
- 1× resistor: 100–220 Ω
- Breadboard + jumper wires

## Wiring

- `GPIO 4` → resistor → LED anode (long leg)
- LED cathode (short leg / flat side) → GND

If the LED is very dim, you can use a smaller resistor (e.g. 100 Ω) to increase current.

![Wiring diagram](docs/wiring.jpg)

## Build and flash (
