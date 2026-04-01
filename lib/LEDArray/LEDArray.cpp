#include "LEDArray.h"

LEDArray::LEDArray(uint8_t latch_pin, uint8_t data_pin, uint8_t clock_pin) {
  _latch_pin = latch_pin;
  _data_pin = data_pin;
  _clock_pin = clock_pin;
}

void LEDArray::begin() {
  pinMode(_latch_pin, OUTPUT);
  pinMode(_clock_pin, OUTPUT);
  pinMode(_data_pin, OUTPUT);
}

void LEDArray::write_to_595(int order, byte _data) {
  digitalWrite(_latch_pin, LOW);

  shiftOut(_data_pin, _clock_pin, order, _data);

  digitalWrite(_latch_pin, HIGH);
}

uint8_t LEDArray::map_to_single_bit(int input) {
  int bitIndex = map(input, 0, 100, 0, 10);
  return (1 << (bitIndex));
}

void LEDArray::rotate_lights() {
  byte x = 0x01;
  for (int j = 0; j < 8; j++) {
    write_to_595(MSBFIRST, x);
    x <<= 1;
    delay(50);
  }
  x = 0x80;
  for (int j = 0; j < 8; j++) {
    write_to_595(MSBFIRST, x);
    x >>= 1;
    delay(50);
  }
}
