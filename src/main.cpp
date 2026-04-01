#include "BasicButton.h"
#include "Jukebox.h"
#include "LEDArray.h"

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <pins.h>

int potValue = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
BasicButton basic_button = BasicButton(BUTTON_PIN, 10);
Jukebox jukebox = Jukebox(JUKEBOX_PIN, CHN);
LEDArray ledarray = LEDArray(LATCH_PIN, DATA_PIN, CLOCK_PIN);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.cursor_on();
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);

  basic_button.begin();
  ledarray.begin();

  ledarray.rotate_lights();
  jukebox.begin();
  jukebox.setLCD(&lcd);

  jukebox.play_intro();
}

void loop() {
  potValue = analogRead(POTENTIOMETER);

  int mapped_range = map(potValue, 0, 4095, 0, 100);
  int selection = (mapped_range / 10) % songCount;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(mapped_range);
  lcd.print(" ");
  uint8_t mapped_led_range = ledarray.map_to_single_bit(mapped_range);
  lcd.printf("Hex: 0x%02X", mapped_led_range);
  ledarray.write_to_595(MSBFIRST, mapped_led_range);
  lcd.setBacklight(mapped_range);
  basic_button.update();

  lcd.setCursor(0, 1);
  lcd.print(playlist[selection].name);

  if (basic_button.is_on()) {
    playlist[selection].play();
  } else {
    ledcWriteTone(CHN, 0);
  }

  delay(100);
}
