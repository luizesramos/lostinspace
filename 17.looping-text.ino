#include <TM1637Display.h>

#define CLK 6
#define DIO 5
TM1637Display display = TM1637Display(CLK, DIO);

// XGFEDCBA
const uint8_t asciiMap[] = {
  0b00111111, /* 0 */ 0b00000110, /* 1 */ 0b01011011, /* 2 */ 0b01001111, /* 3 */
  0b01100110, /* 4 */ 0b01101101, /* 5 */ 0b01111101, /* 6 */ 0b00000111, /* 7 */
  0b01111111, /* 8 */ 0b01101111,                                         /* 9 */

  0b01110111,  // A
  0b01111100,  // b
  0b00111001,  // C
  0b01011110,  // d
  0b01111001,  // E
  0b01110001,  // F
  0b01101111,  // G
  0b01110110,  // H
  0b00000110,  // I
  0b00011110,  // J
  0b01110000,  // k
  0b00111000,  // L
  0b01010101,  // M
  0b01010100,  // n
  0b00111111,  // O
  0b01110011,  // P
  0b01100111,  // q
  0b01010000,  // r
  0b01101101,  // s
  0b01111000,  // t
  0b00111110,  // u
  0b00011100,  // v
  0b00011101,  // w
  0b01110110,  // x
  0b01101110,  // y
  0b01011011,  // z
};

// takes an ascii letter or digit and converts to a 7-segment digit
uint8_t ascii(char symbol) {
  if (symbol == '-') {
    return 0b01000000;
  } else if (symbol >= '0' && symbol <= '9') {
    return asciiMap[symbol - '0'];
  } else if (symbol >= 'A' && symbol <= 'Z') {
    return asciiMap[symbol - 'A' + 10];
  } else if (symbol >= 'a' && symbol <= 'z') {
    return asciiMap[symbol - 'a' + 10];
  } else {
    return 0x00;
  }
}

// index is from 0 - 25 (26 letters)
uint8_t make(char letter) {
  return ascii('a' + (letter - 'a') % 26);
}

void showAlphabet() {
  for (char i = 'a'; i <= 'z'; i++) {
    uint8_t data[] = { make(i), make(i+1), make(i+2), make(i+3) };
    display.setSegments(data);
    delay(500);
  }
}

uint8_t wrappedAscii(String text, int index) {  
  return ascii(text.charAt(index % text.length()));
}

void rollText(String text, int rollDelay) {
  for (int i = 0; i < text.length(); i++) {
    uint8_t data[] = { 
      wrappedAscii(text, i),
      wrappedAscii(text, i+1),
      wrappedAscii(text, i+2),
      wrappedAscii(text, i+3),
    };
    display.setSegments(data);
    delay(rollDelay);
  } 
}

void setup() {
  Serial.begin(9600);
  display.setBrightness(7);
}

void loop() {
  rollText("Hello my good friend I missed you - ", 200);
}
