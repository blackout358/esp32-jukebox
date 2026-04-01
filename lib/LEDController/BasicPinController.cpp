#include "BasicPinController.h"

BasicPinController::BasicPinController(int pin) {
  _pin = pin;
  _lastState = LOW;
}

void BasicPinController::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

void BasicPinController::off() {
  digitalWrite(_pin, LOW);
  _lastState = LOW;
}
void BasicPinController::on() {
  digitalWrite(_pin, HIGH);
  _lastState = HIGH;
}
void BasicPinController::toggle() {
  if (_lastState == HIGH) {
    off();
  } else {
    on();
  }
}
int BasicPinController::get_state() { return _lastState; }
