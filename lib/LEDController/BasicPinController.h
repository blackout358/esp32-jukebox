#ifndef BASIC_PIN_CONTROLLER_H
#define BASIC_PIN_CONTROLLER_H

#include <Arduino.h>

class BasicPinController {
private:
  int _pin;
  int _lastState;

public:
  BasicPinController(int pin);
  void begin();
  void off();
  void on();
  void toggle();
  int get_state();
};

#endif
