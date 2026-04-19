#include "ActionMapper.h"

ActionMapper::ActionMapper(BLEManager* ble) 
    : _ble(ble), _lastTouchState(0) {}

void ActionMapper::processAction(uint8_t touchState, uint8_t mode) {
    if (touchState == _lastTouchState) return;

    // 动作切换前彻底释放以防粘连
    _ble->releaseAll();

    if (touchState == 0) { 
        _lastTouchState = 0; 
        return; 
    }

    switch (mode) {
        case 0: // ---- WASD + 空格 模式 ----
            switch(touchState) {
                case 0b0001: execute('w'); break; // 食指 -> W
                case 0b0010: execute('s'); break; // 中指 -> S
                case 0b0100: execute('a'); break; // 无名指 -> A
                case 0b1000: execute('d'); break; // 小指 -> D
                case 0b1111: execute(' '); break; // 四指 -> 空格
                case 0b0011: clickMouse(1); break; // 食指+中指 -> 左键
                case 0b1100: clickMouse(2); break; // 无名指+小指 -> 右键
                default: break;
            }
            break;

        case 1: // ---- KL 模式 ----
            switch(touchState) {
                case 0b0001: execute('k'); break; // 食指 -> K
                case 0b0010: execute('l'); break; // 中指 -> L
                case 0b1111: execute(' '); break; // 四指 -> 空格
                case 0b0011: clickMouse(1); break; // 食指+中指 -> 左键
                case 0b1100: clickMouse(2); break; // 无名指+小指 -> 右键
                default: break;
            }
            break;

        case 2: // ---- 纯陀螺仪模式 (仅鼠标点击) ----
            switch(touchState) {
                case 0b0001: clickMouse(1); break; // 食指 -> 左键
                case 0b0010: clickMouse(2); break; // 中指 -> 右键
                case 0b0011: clickMouse(1); break; // 食指+中指 -> 左键
                case 0b1100: clickMouse(2); break; // 无名指+小指 -> 右键
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