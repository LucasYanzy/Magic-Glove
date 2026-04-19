# Gesture Mouse Glove
A wearable Bluetooth mouse glove based on Seeed Studio XIAO ESP32-S3. Transform your hand into a wireless mouse using touch sensors on your fingers.

## Features
- Bluetooth Low Energy (BLE) HID mouse, works with Windows, macOS, Linux, iOS, Android
- Touch-based gesture control using copper pads on fingers
- Left click, Right click, Scroll up/down out of the box
- Extensible architecture for custom gestures and actions
- Battery level reporting
- Low power consumption for battery operation

## Hardware Requirements
- 1x Seeed Studio XIAO ESP32-S3
- 1x Cotton glove (or any flexible glove)
- 6x Copper tape/pads (for touch sensors)
- Flexible wires (to connect pads to the board)
- 1x 3.7V Li-ion battery (for wireless operation)

## Wiring
Please refer to [docs/wiring.md](docs/wiring.md) for detailed connection instructions.

## Software Setup
### Using PlatformIO (Recommended)
1. Clone this repository:
   ```bash
   git clone https://github.com/your-username/GestureMouseGlove.git
   cd GestureMouseGlove
   ```
2. Open the project in PlatformIO IDE
3. Build and upload to your XIAO ESP32-S3

### Using Arduino IDE
1. Install the [ESP32 Arduino Core](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)
2. Install required libraries via Library Manager:
   - `ESP32-s3-BLE-Mouse` by mayermakes
   - `NimBLE-Arduino` by h2zero
3. Open `GestureMouseGlove.ino`
4. Select "Seeed Studio XIAO ESP32S3" as your board
5. Upload the sketch

## Calibration
On first boot, the device will automatically calibrate the touch sensors.
1. Power on the device
2. The on-board LED will blink rapidly
3. **Do NOT touch any of the finger pads during calibration**
4. After 2 seconds, calibration is complete, the LED will stay solid.

## Default Gesture Mapping
| Finger Touch | Action |
|--------------|--------|
| Index Finger alone | Left Click |
| Middle Finger alone | Right Click |
| Ring Finger alone | Scroll Down |
| Pinky Finger alone | Scroll Up |
| Index + Middle | Middle Click |
| *Other combinations* | Reserved for custom actions |

## Extending the Project
This project is built with a modular architecture to easily add new features:
- Add new touch sensors: Extend the `TouchSensor` class
- Add new gestures: Modify the action map in `ActionMapper.cpp`
- Add cursor movement: Integrate an IMU sensor and use `BLEManager::move()`
- Add keyboard shortcuts: Extend the BLE manager to support keyboard HID

## License
MIT License - see [LICENSE](LICENSE) for details.
