#ifndef LEDARRAY_H
#define LEDARRAY_H

#include <Arduino.h>
#include <cstdint>

class LEDArray {

public:
  LEDArray(uint8_t latch_pin, uint8_t data_pin, uint8_t clock_pin);
  void begin();
  void write_to_595(int order, byte _data);
  uint8_t map_to_single_bit(int input);
  void rotate_lights();

private:
  uint8_t _latch_pin;
  uint8_t _data_pin;
  uint8_t _clock_pin;
};

#endif
