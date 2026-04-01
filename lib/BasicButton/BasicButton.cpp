#include "BasicButton.h"

BasicButton::BasicButton(int pin, unsigned long debounce) {
  _pin = pin;
  _count = 0;
  _last_state = HIGH;
  _last_debounce_time = 0;
  _debounce_delay = debounce;
}

void BasicButton::begin() { pinMode(_pin, INPUT_PULLUP); }

void BasicButton::update() {
  int currentState = digitalRead(_pin);
  if (currentState != _last_state) {
    if ((millis() - _last_debounce_time) > _debounce_delay) {
      if (currentState == LOW) {
        _count++;
      }
      _last_debounce_time = millis();
    }
  }
  _last_state = currentState;
}

int BasicButton::get_count() { return _count; }

int BasicButton::get_state() { return _last_state; }

void BasicButton::reset() { _count = 0; }

bool BasicButton::is_on() { return _last_state == LOW; }
