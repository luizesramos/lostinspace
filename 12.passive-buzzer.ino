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

const int buzzerPin = 10;
unsigned int tones[NROWS][NCOLS] = {
    {31, 93, 147, 208},
    {247, 311, 370, 440},
    {523, 587, 698, 880},
    {1397, 2637, 3729, 4978}
};

Keypad *keypad = new Keypad(makeKeymap(keyMap), rowPins, colPins, NROWS, NCOLS);

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  char symbol = keypad->getKey();
  if (symbol != NULL) {
    Serial.println(symbol);
    playSoundForKeymapSymbol(symbol);
    delay(500);
    noTone(buzzerPin);
  }
}

void playSoundForKeymapSymbol(char symbol) {
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++) {
      if (symbol == keyMap[i][j]) {
        tone(buzzerPin, tones[i][j], 500);
      }
    }
  }
}