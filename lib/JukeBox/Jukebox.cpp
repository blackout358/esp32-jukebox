#include "Jukebox.h"

uint8_t Jukebox::_pin = 0;
uint8_t Jukebox::_channel = 0;
LiquidCrystal_I2C *Jukebox::lcd = nullptr;

const Song playlist[] PROGMEM = {
    {"Fur Elise", Jukebox::play_fur_elise},
    {"Mario Theme", Jukebox::play_mario_theme},
    {"Tetris", Jukebox::play_tetris},
    {"Zelda Main", Jukebox::play_zelda},
    {"Song Of Storms", Jukebox::play_song_of_storms},
    {"Happy Birthday", Jukebox::play_happy_birthday},
    {"Imperial March", Jukebox::play_imperial_march},
    {"Star Wars Theme", Jukebox::play_star_wars_theme},

    {"Test", Jukebox::buzzer_test},
    {"Siren", Jukebox::play_siren}};

const int songCount = sizeof(playlist) / sizeof(Song);

Jukebox::Jukebox(uint8_t pin, uint8_t channel) {
  _pin = pin;
  _channel = channel;
}
void Jukebox::setLCD(LiquidCrystal_I2C *_lcd) { lcd = _lcd; }

void Jukebox::begin() {
  ledcSetup(_channel, 5000, 8);
  ledcAttachPin(_pin, _channel);
}

void Jukebox::buzzer_test() {
  for (int freq = 100; freq < 3000; freq += 100) {
    if (lcd != nullptr) {
      lcd->clear();
      lcd->print(freq);
    }
    ledcWriteTone(0, freq);
    delay(300);
  }
  ledcWriteTone(0, 0);
}

void Jukebox::play_tone(int frequency, int duration) {

  if (frequency == NOTE_REST) {
    ledcWriteTone(_channel, 0);
  } else {
    ledcWriteTone(_channel, frequency);
  }

  delay(duration * 0.95);
  ledcWriteTone(_channel, 0);
  delay(duration * 0.05);
}

void Jukebox::play_array(const int melody[], const int duration[], int len) {
  for (int i = 0; i < len; i++) {
    int noteDuration = 1000 / duration[i];
    if (lcd != nullptr) {
      lcd->clear();
      lcd->print(melody[i]);
      lcd->print("  ");
      lcd->print(noteDuration);
      lcd->setCursor(0, 1);
      lcd->print(i);
    }
    play_tone(melody[i], noteDuration);
  }
}

void Jukebox::play_intro() {
  static const int melody[] PROGMEM = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};
  static const int beats[] PROGMEM = {200, 200, 200, 400};

  int length = sizeof(melody) / sizeof(int);

  for (int i = 0; i < length; i++) {
    play_tone(melody[i], beats[i]);
  }
}

void Jukebox::play_siren() {
  for (int x = 0; x < 360; x += 10) {
    float sinVal = sin(x * (PI / 180));
    int toneVal = 2000 + (int)(sinVal * 500);
    ledcWriteTone(_channel, toneVal);
    delay(10);
  }
}
void Jukebox::play_mario_theme() {
  static const int melody[] PROGMEM = {
      NOTE_E5, NOTE_E5,   NOTE_REST, NOTE_E5,   NOTE_REST, NOTE_C5,
      NOTE_E5, NOTE_REST, NOTE_G5,   NOTE_REST, NOTE_G4,   NOTE_REST,
      NOTE_C5, NOTE_G4,   NOTE_E4,   NOTE_A4,   NOTE_B4,   NOTE_AS4,
      NOTE_A4, NOTE_G4,   NOTE_E5,   NOTE_G5,   NOTE_A5,   NOTE_F5,
      NOTE_G5, NOTE_E5,   NOTE_C5,   NOTE_D5,   NOTE_B4};
  static const int durations[] PROGMEM = {8, 8, 8, 8, 8, 8, 8, 8, 4, 4,
                                          4, 4, 4, 4, 4, 8, 8, 8, 4, 4,
                                          8, 8, 8, 4, 8, 8, 4, 8, 4};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}

void Jukebox::play_zelda() {
  static const int melody[] PROGMEM = {
      NOTE_AS4, NOTE_F4,  NOTE_AS4, NOTE_AS4, NOTE_C5,  NOTE_D5,
      NOTE_DS5, NOTE_F5,  0,        NOTE_F5,  NOTE_F5,  NOTE_FS5,
      NOTE_GS5, NOTE_AS5, 0,        NOTE_AS5, NOTE_AS5, NOTE_GS5,
      NOTE_FS5, NOTE_GS5, NOTE_FS5, NOTE_F5,

      NOTE_F5,  NOTE_DS5, NOTE_DS5, NOTE_F5,  NOTE_FS5, NOTE_F5,
      NOTE_DS5, NOTE_CS5, NOTE_DS5, NOTE_CS5, NOTE_C5,  NOTE_AS4,
      NOTE_C5,  NOTE_D5,  NOTE_F5,  NOTE_G5,  NOTE_A5,  NOTE_AS5};

  static const int durations[] PROGMEM = {
      1, 2, 4, 8, 8, 8, 8, 1, 8, 4, 8, 8, 8, 1, 8, 4, 8, 8, 8, 4, 8, 1,

      2, 4, 8, 8, 1, 2, 4, 8, 8, 4, 4, 2, 2, 2, 2, 4, 4, 1};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}
void Jukebox::play_song_of_storms() {
  static const int melody[] PROGMEM = {
      NOTE_D4, NOTE_F4, NOTE_D5, NOTE_D4, NOTE_F4, NOTE_D5, NOTE_E5,
      NOTE_F5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,

      NOTE_A4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4,
      NOTE_D4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4,

      NOTE_D4, NOTE_F4, NOTE_D5, NOTE_D4, NOTE_F4, NOTE_D5, NOTE_E5,
      NOTE_F5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4,

      NOTE_A4, NOTE_D4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_D4};

  static const int durations[] PROGMEM = {
      8, 8, 2, 8, 8, 2, 4, 8, 8, 8, 8, 8, 4, 4,

      // Part 2:
      4, 4, 8, 8, 2, 4, 4, 4, 8, 8, 2, 4,

      // Part 3:
      8, 8, 2, 8, 8, 2, 4, 8, 8, 8, 8, 8, 4, 4,

      // Part 4:
      4, 4, 8, 8, 2, 4, 2};

  play_array(melody, durations, sizeof(melody) / sizeof(int));
}

void Jukebox::play_happy_birthday() {
  static const int melody[] PROGMEM = {
      NOTE_C4,  NOTE_C4,  NOTE_D4, NOTE_C4,
      NOTE_F4,  NOTE_E4, // Happy Birthday to you
      NOTE_C4,  NOTE_C4,  NOTE_D4, NOTE_C4,
      NOTE_G4,  NOTE_F4, // Happy Birthday to you
      NOTE_C4,  NOTE_C4,  NOTE_C5, NOTE_A4,
      NOTE_F4,  NOTE_E4,  NOTE_D4, // Happy Birthday dear [Name]
      NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4,
      NOTE_G4,  NOTE_F4 // Happy Birthday to you
  };

  static const int durations[] PROGMEM = {8, 8, 4, 4, 4, 2, 8, 8, 4, 4, 4, 2, 8,
                                          8, 4, 4, 4, 4, 4, 8, 8, 4, 4, 4, 2};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}

void Jukebox::play_imperial_march() {
  static const int melody[] PROGMEM = {
      NOTE_G4,  NOTE_G4,  NOTE_G4,  NOTE_DS4, NOTE_AS4, NOTE_G4,
      NOTE_DS4, NOTE_AS4, NOTE_G4,  NOTE_D5,  NOTE_D5,  NOTE_D5,
      NOTE_DS5, NOTE_AS4, NOTE_FS4, NOTE_DS4, NOTE_AS4, NOTE_G4};

  static const int durations[] PROGMEM = {4, 4, 4, 6, 16, 4, 6, 16, 2,
                                          4, 4, 4, 6, 16, 4, 6, 16, 2};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}
void Jukebox::play_star_wars_theme() {
  static const int melody[] PROGMEM = {
      NOTE_G4, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_G5, NOTE_F5, NOTE_E5,
      NOTE_D5, NOTE_C6, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C6,
      NOTE_G5, NOTE_F5, NOTE_E5, NOTE_F5, NOTE_D5};

  static const int durations[] PROGMEM = {8, 8, 8, 2, 2, 8, 8, 8, 2, 4,
                                          8, 8, 8, 2, 4, 8, 8, 8, 2};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}

void Jukebox::play_tetris() {
  static const int melody[] PROGMEM = {
      NOTE_E5, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_C5, NOTE_B4,  NOTE_A4,
      NOTE_A4, NOTE_C5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,  NOTE_C5,
      NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_A4, NOTE_REST};
  static const int durations[] PROGMEM = {4, 8, 8, 4, 8, 8, 4, 8, 8, 4,
                                          8, 8, 4, 4, 4, 4, 4, 4, 4, 4};
  play_array(melody, durations, sizeof(melody) / sizeof(int));
}

void Jukebox::play_fur_elise() {

  static const int melody[] PROGMEM = {

      NOTE_E5,   NOTE_DS5, NOTE_E5,   NOTE_DS5, NOTE_E5, NOTE_B4,   NOTE_D5,
      NOTE_C5,   NOTE_A4,  NOTE_REST, NOTE_C4,  NOTE_E4, NOTE_A4,   NOTE_B4,
      NOTE_REST, NOTE_E4,  NOTE_GS4,  NOTE_B4,  NOTE_C5, NOTE_REST, NOTE_E4,
      NOTE_E5,   NOTE_DS5, NOTE_E5,   NOTE_DS5, NOTE_E5, NOTE_B4,   NOTE_D5,
      NOTE_C5,   NOTE_A4,  NOTE_REST, NOTE_C4,  NOTE_E4, NOTE_A4,   NOTE_B4,
      NOTE_REST, NOTE_E4,  NOTE_C5,   NOTE_B4,  NOTE_A4

  };

  static const int durations[] PROGMEM = {

      8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8, 8, 4, 8,
      8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8, 8, 4};

  play_array(melody, durations, sizeof(melody) / sizeof(int));
}
void Jukebox::stop() { ledcWriteTone(_channel, 0); }
