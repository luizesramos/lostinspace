// Sketch >> Include Library >> Add .ZIP Library >> libs/7SEG-TM1637-HERO.zip
#include <TM1637Display.h>

const int dioPin = 5;
const int clkPin = 6;
TM1637Display *display = new TM1637Display(clkPin, dioPin);

// Segment positions
//   A
// F   B
//   G
// E   C
//   D   DP
const uint8_t allOn[] = { 0xff, 0xff, 0xff, 0xff };
const uint8_t allOff[] = { 0x00, 0x00, 0x00, 0x00 };
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,          // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,  // O
  SEG_C | SEG_E | SEG_G,                          // n
  SEG_A | SEG_F | SEG_G | SEG_E | SEG_D,          // E
};

void setup() {
  display->clear();
  delay(1000);
  display->setBrightness(0);

  display->setSegments(allOn);
  delay(2000);
  display->clear();
  delay(1000);

  for (int i = 0; i < 124; i++) {
    display->showNumberDec(i);
    delay(100);
  }

  delay(2000);
  display->clear();
  delay(1000);
  display->setSegments(done);
}

void loop() {
}
