// Tools >> Manage Libraries >> Search for "Keypad"
#include <Keypad.h>

const byte NROWS = 4;
const byte NCOLS = 4;
const byte rowPins[NROWS] = { 5, 4, 3, 2 };  // decreasing to match keypad's key layout
const byte colPins[NCOLS] = { 6, 7, 12, 13 };
const char keyMap[NROWS][NCOLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const int buzzerPin = 8;
const int NRGB = 3;
const int rgbPins[NRGB] = { 11, 10, 9 };  // need the PWM pins for RGB control

const byte PASSWORD_LENGTH = 4;
char password[PASSWORD_LENGTH] = { '0', '0', '0', '0' };

Keypad *keypad = new Keypad(makeKeymap(keyMap), rowPins, colPins, NROWS, NCOLS);

void setup() {
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < NRGB; i++) {
    pinMode(rgbPins, OUTPUT);
  }

  Serial.begin(9600);

  setColor(200, 125, 125);
  delay(2000);
  feedbackOff();
  Serial.println("\nHit * to change the password OR # to unlock the system");
}

void loop() {
  char option = nextKeyPress();
  switch (option) {
    case'1':
      feedbackForPasswordChanged();
      break;
    case '*':
      changePassword();
      break;
    case '#':
      signIn();
      break;
    default:
      Serial.print("🤷");
      Serial.println(option);
      break;
  }
}

void changePassword() {
  feedbackEnterOptionMode();
  Serial.println("\n> CHANGE PASSWORD");
  delay(500);
  int access = promptForPassword();
  feedbackForAccess(access);
  if (access >= 0) {
    setNewPassword();
  }
}

void signIn() {
  feedbackEnterOptionMode();
  Serial.println("\n> SIGN IN");
  delay(500);
  int access = promptForPassword();
  feedbackForAccess(access);
}

// return < 0 if denied and >= 0 if granted
int promptForPassword() {
  feedbackOff();
  Serial.println("Type your current password: ");
  int result = 1;
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    if (password[i] != nextKeyPress()) {
      result = -1;  // don't return here or one could reverse engineer the password
    }
    feedbackForInput();
  }
  return result;
}

void setNewPassword() {
  Serial.print("Enter new password: ");
  int result = 1;
  for (int i = 0; i < PASSWORD_LENGTH; i++) {
    password[i] = nextKeyPress();
    feedbackForInput();
  }
  feedbackForPasswordChanged();
}

char nextKeyPress() {
  char symbol = 0;
  while (!symbol) {
    symbol = keypad->getKey();
  }
  return symbol;
}

// Feedback

void feedbackOff() {
  setColor(0, 0, 0);
  noTone(buzzerPin);
}

void feedbackEnterOptionMode() {
  setColor(255, 0, 0);
  noTone(buzzerPin);
}

void feedbackForInput() {
  Serial.print("*");
  tone(buzzerPin, 880, 200);
  setColor(0, 0, 128);
  delay(500);
  feedbackOff();
}

void feedbackForAccess(int accessStatus) {
  if (accessStatus < 0) {
    setColor(255, 0, 0);
    tone(buzzerPin, 147, 200);
    delay(100);
    Serial.println("\nBAD PASSWORD");
  } else {
    setColor(0, 128, 0);
    tone(buzzerPin, 1000, 200);
    delay(200);
    tone(buzzerPin, 2700, 1000);
    delay(1000);
    Serial.println("\nAccess granted");
  }
  feedbackOff();
}

void feedbackForPasswordChanged() {
  setColor(0, 128, 0);
  tone(buzzerPin, 1000, 200);
  delay(200);
  tone(buzzerPin, 1500, 200);
  delay(200);
  tone(buzzerPin, 2100, 200);
  delay(200);
  Serial.println("\nPassword updated!");
  feedbackOff();
}

void setColor(int r, int g, int b) {
  analogWrite(rgbPins[0], r);
  analogWrite(rgbPins[1], g);
  analogWrite(rgbPins[2], b);
}