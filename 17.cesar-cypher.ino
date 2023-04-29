// A CRYPTIC MESSAGE
#include <Arduino.h>
#include <TM1637Display.h>

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9

// MODULE CONNECTION PINS (DIGITAL PINS)
#define CLK 6
#define DIO 5

// THE AMOUNT OF TIME (IN MILLISECONDS) BETWEEN TESTS
#define TEST_DELAY 2000

TM1637Display display = TM1637Display(CLK, DIO);

void setup() {
}

void loop() {
  display.setBrightness(0);
  uint8_t data[] = { 0x00, 0x00, 0x00, 0x00 };  // ALL SEGMENTS OFF
  display.setSegments(data);

  int code1 = TWO * 10 + THREE;
  display.showNumberDec(code1, false, 3, 1);  // first code

  // FALSE DOESN'T SHOW LEADING ZEROS, 3 MEANS SHOW THREE DIGITS,
  // 1 MEANS START IN POSITION ONE (WHERE THE FIRST POSITION IS ZERO)
  delay(TEST_DELAY);
  display.setSegments(data);

  int code2 = THREE * 100 + FIVE * 10 + THREE;
  display.showNumberDec(code2, true, 3, 1);  //second code
  delay(TEST_DELAY);
  display.setSegments(data);

  int code3 = 1000 + SIX * 100 + EIGHT * 10 + EIGHT;
  display.showNumberDec(code3, true, 4, 0);  //third code
  delay(TEST_DELAY);
}

// Codes
// 23
// 353
// 1688