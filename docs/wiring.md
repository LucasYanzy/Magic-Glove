# Wiring Guide
This document describes how to connect the touch pads and battery to the XIAO ESP32-S3 board.

## Pin Connections
| XIAO ESP32-S3 Pin | Function | Connected to |
|-------------------|----------|--------------|
| D0 (GPIO1) | Touch Sensor 1 | Index Finger Copper Pad |
| D1 (GPIO2) | Touch Sensor 2 | Middle Finger Copper Pad |
| D2 (GPIO3) | Touch Sensor 3 | Ring Finger Copper Pad |
| D3 (GPIO4) | Touch Sensor 4 | Pinky Finger Copper Pad |
| GND | Ground | Thumb Copper Pad |
| GND | Ground | Palm Copper Pad |
| 5V (VIN) | Power Input | Li-ion Battery Positive (+) |
| GND | Power Input | Li-ion Battery Negative (-) |

## Assembly Tips
1. Stick the copper pads on the tip of each finger (Index, Middle, Ring, Pinky)
2. Stick one copper pad on the tip of your thumb
3. Stick another copper pad on the palm of your hand
4. Run flexible wires from each pad to the XIAO board, secure them to the glove with tape
5. Connect the battery to the power pins, you can add a switch between them for easy power control
6. Secure the XIAO board and battery to the back of the glove
