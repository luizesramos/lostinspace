// Tools >> Manage Libraries >> Search for "Keypad"
#include <Keypad.h>

const byte NROWS = 4;
const byte NCOLS = 4;
const byte rowPins[NROWS] = { 5, 4, 3, 2 };  // decreasing to match keypad's key layout
const byte colPins[NCOLS] = { 6, 7, 8, 9 };
const char keyMap[NROWS][NCOLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

Keypad *keypad = new Keypad(makeKeymap(keyMap), rowPins, colPins, NROWS, NCOLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char symbol = keypad->getKey();
  if (symbol != NULL) {
    Serial.println(symbol);
  }
}