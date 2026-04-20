/**
 * @file ActionMapper.cpp
 * @brief Maps touch sensor states to HID actions across different modes | 手势映射控制器实现
 * @author LucasYanzy
 */

#include "ActionMapper.h"

ActionMapper::ActionMapper(BLEManager* ble) 
    : _ble(ble), _lastTouchState(0) {}

void ActionMapper::processAction(uint8_t touchState, uint8_t mode) {
    if (touchState == _lastTouchState) return;

    // Release all keys/buttons before mapping a new action to prevent sticking | 动作切换前彻底释放以防粘连
    _ble->releaseAll();

    if (touchState == 0) { 
        _lastTouchState = 0; 
        return; 
    }

    switch (mode) {
        case 0: // ---- WASD + Space Mode (游戏模式) ----
            switch(touchState) {
                case 0b0001: execute('w'); break; // Index/食指 -> W
                case 0b0010: execute('s'); break; // Middle/中指 -> S
                case 0b0100: execute('a'); break; // Ring/无名指 -> A
                case 0b1000: execute('d'); break; // Pinky/小指 -> D
                case 0b1111: execute(' '); break; // All 4/四指 -> Space/空格
                case 0b0011: clickMouse(1); break; // Index+Middle/食指+中指 -> Left Click/左键
                case 0b1100: clickMouse(2); break; // Ring+Pinky/无名指+小指 -> Right Click/右键
                default: break;
            }
            break;

        case 1: // ---- KL Mode (音游模式) ----
            switch(touchState) {
                case 0b0001: execute('k'); break; // Index/食指 -> K
                case 0b0010: execute('l'); break; // Middle/中指 -> L
                case 0b1111: execute(' '); break; // All 4/四指 -> Space/空格
                case 0b0011: clickMouse(1); break; // Index+Middle/食指+中指 -> Left Click/左键
                case 0b1100: clickMouse(2); break; // Ring+Pinky/无名指+小指 -> Right Click/右键
                default: break;
            }
            break;

        case 2: // ---- Gyro Air-Mouse Mode (纯陀螺仪空中鼠标，仅映射点击) ----
            switch(touchState) {
                case 0b0001: clickMouse(1); break; // Index/食指 -> Left Click/左键
                case 0b0010: clickMouse(2); break; // Middle/中指 -> Right Click/右键
                case 0b0011: clickMouse(1); break; // Index+Middle/食指+中指 -> Left Click/左键
                case 0b1100: clickMouse(2); break; // Ring+Pinky/无名指+小指 -> Right Click/右键
                default: break;
            }
            break;
    }

    _lastTouchState = touchState;
}

void ActionMapper::execute(char k) {
    _ble->pressKey(k);
}

void ActionMapper::clickMouse(int button) {
    if (button == 1) _ble->leftClick();
    else _ble->rightClick();
}