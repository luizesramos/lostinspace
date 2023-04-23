const int NROWS = 4;
const int NCOLS = 4;
const int rowPins[NROWS] = { 5, 4, 3, 2 }; // decreasing to match keypad's key layout
const int colPins[NCOLS] = { 6, 7, 8, 9 };
const char keyMap[NROWS][NCOLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
const unsigned long DEBOUNCE_TIME_MS = 20;

void setupPins(const int *rowPins, const int *colPins) {
  // Row pins are input. We write HIGH to them to turn on the pullup resistors of the keyboard.
  // When the row is not selected, we will read HIGH.
  for (int i = 0; i < NROWS; i++) {
    pinMode(rowPins[i], INPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  // Col pins are output because we will only use them to control the read process.
  // For each col, we try to read their rows and see if any row transitioned to LOW (key down).
  // We can wait a 'debounce time' to reduce the keyboard sensitivity.
  // If the row remains in LOW, we wait for it to transition to HIGH (key up) to flag a key press.
  for (int i = 0; i < NCOLS; i++) {
    pinMode(colPins[i], OUTPUT);
  }
}

char readKey(const char keyMap[NROWS][NCOLS], const int *rowPins, const int *colPins) {
  char key = NULL;

  for (char c = 0; c < NCOLS; c++) {
    digitalWrite(colPins[c], LOW);

    for (char r = 0; r < NROWS; r++) {
      if (digitalRead(rowPins[r]) == LOW) { // key down event     
        delay(DEBOUNCE_TIME_MS); // wait 'debouce time' reduce keyboard sensitivity
        // wait for key up event
        while (digitalRead(rowPins[r]) == LOW); 
        // we detected a key press
        key = keyMap[r][c];
      }
    }

    digitalWrite(colPins[c], HIGH);
  }

  return key;
}

void setup() {
  Serial.begin(9600);
  setupPins(rowPins, colPins);
}

void loop() {
  char symbol = readKey(keyMap, rowPins, colPins);
  if (symbol != NULL) {
    Serial.println(symbol);
  }
}