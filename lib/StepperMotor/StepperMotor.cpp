#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t output_pins[4]) {

  for (int i = 0; i < 4; i++) {
    _output_pins[i] = output_pins[i];
  }
  // memcpy(_output_pins, output_pins, 4);
}

void StepperMotor::begin() {
  for (int i = 0; i < 4; i++) {
    pinMode(_output_pins[i], OUTPUT);
    digitalWrite(_output_pins[i], LOW);
  }
}

void StepperMotor::moveOneStep(bool dir) {
  static int stepIndex = 0;

  // 8-step Half-Step sequence for maximum stability and torque
  // BITS: [IN4][IN3][IN2][IN1]
  static const byte halfStepTable[] = {
      0b0001, // A
      0b0011, // AB
      0b0010, // B
      0b0110, // BC
      0b0100, // C
      0b1100, // CD
      0b1000, // D
      0b1001  // DA
  };

  if (dir) {
    stepIndex++;
  } else {
    stepIndex--;
  }

  // Proper wrap-around for 8 steps
  stepIndex = (stepIndex + 8) % 8;

  for (int i = 0; i < 4; i++) {
    digitalWrite(_output_pins[i],
                 (halfStepTable[stepIndex] & (1 << i)) ? HIGH : LOW);
  }
}
void StepperMotor::moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); // Rotate a step
    delay(constrain(ms, 3, 20));
    // Control the speed
  }
}

void StepperMotor::moveAround(bool dir, int turns, byte ms) {
  for (int i = 0; i < turns; i++)
    moveSteps(dir, 32 * 64, ms);
}

void StepperMotor::moveAngle(bool dir, int angle, byte ms) {
  moveSteps(dir, (angle * 32 * 64 / 360), ms);
}
