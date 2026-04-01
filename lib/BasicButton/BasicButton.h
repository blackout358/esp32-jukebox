#ifndef BASIC_BUTTON_H
#define BASIC_BUTTON

#include <Arduino.h>

class BasicButton {
private:
  int _pin;
  int _count;
  int _last_state;
  unsigned long _last_debounce_time;
  unsigned long _debounce_delay;

public:
  BasicButton(int pin, unsigned long debounce = 50);
  void begin();
  void update();
  int get_count();
  int get_state();
  bool is_on();
  void reset();
};

#endif
