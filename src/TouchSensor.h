/**
 * @file TouchSensor.h
 * @brief Capacitive Touch Manager with adaptive baseline | 电容触摸管理器头文件
 * @author LucasYanzy
 */

#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include <Arduino.h>

#define TOUCH_COUNT 4
#define DEBOUNCE_COUNT 3
#define TOUCH_THRESHOLD 10

extern const int DEFAULT_TOUCH_PINS[TOUCH_COUNT];

class TouchSensor {
public:
  TouchSensor(const int *pins = DEFAULT_TOUCH_PINS);
  void begin();
  void update();
  uint8_t getTouchState();
  void calibrate();

private:
  int _pins[TOUCH_COUNT];
  uint16_t _baseline[TOUCH_COUNT];
  bool _currentState[TOUCH_COUNT];
  int _debounceCounter[TOUCH_COUNT];
  void readBaseline();
};

#endif