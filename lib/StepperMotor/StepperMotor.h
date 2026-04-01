#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor {
public:
  StepperMotor(uint8_t output_pins[4]);
  void begin();
  void moveAround(bool dir, int turns, byte ms);
  void moveAngle(bool dir, int angle, byte ms);
  void moveSteps(bool dir, int steps, byte ms);

private:
  uint8_t _output_pins[4];
  void moveOneStep(bool dir);
};

#endif
