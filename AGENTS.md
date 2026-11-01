# Repository Guidelines

## Project Structure

- `led_demo.ino` is the ESP32 Arduino sketch. It controls a 5×5 WS2812B LED matrix and contains the demo animations.
- `wiring_diaqgram.md` documents the ESP32, SN74AHCT125D, power, and matrix connections. Keep hardware instructions aligned with the pin values in the sketch.
- `POC.md` lists planned proof-of-concept work.
- `README.md` is currently a minimal project marker. There is no separate source, test, or asset directory.

## Build, Run, and Test

This repository has no build scripts or automated tests. To build and run the demo:

1. Open `led_demo.ino` in Arduino IDE.
2. Install the `FastLED` library and select the correct ESP32 board and serial port.
3. Compile, upload, and open Serial Monitor at `115200` baud. The sketch prints each animation state.

Check wiring against `wiring_diaqgram.md` before powering the LED matrix. The sketch expects data on GPIO 18 and 25 LEDs in a 5×5 serpentine layout. Test changes on the hardware and check each animation and the serial output.

## Coding Style

Use the existing Arduino C++ style: two spaces for indentation, braces on the same line, and descriptive `camelCase` function names. Keep hardware constants near the top of the sketch. Use named constants for pin numbers and matrix dimensions. Update the wiring guide when a pin or connection changes.

## Testing Guidelines

There is no test framework or coverage target. For changes to animation logic, compile the sketch and verify the affected animation on the matrix. For pin, power, or layout changes, check the wiring guide and confirm the LED order and colors on the device.

## Commits and Pull Requests

The Git history is small and has no established commit format. Use short, clear commit subjects, such as `Add alert animation` or `Document matrix wiring`. A pull request should explain the change, list hardware or library requirements, and include photos or a short recording when LED behavior changes. Link a related issue when one exists.

## Hardware and Configuration

Use a shared ground between the ESP32, level shifter, and external LED supply. Keep the ESP32 powered by USB during upload and testing. Do not connect the external 5 V supply to ESP32 5V/VIN while USB is connected. See the wiring guide for level-shifter and capacitor details.
