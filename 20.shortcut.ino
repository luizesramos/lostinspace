// Same as day 19, but the shortcut is activated when we push the rotary encoder's button

#include <TM1637Display.h>

// Codes obtained from day 17
#define SECRET1 23
#define SECRET2 353
#define SECRET3 1688

// buzzer
const int buzzerPin = 7;

// display setup
#define DISPLAY_CLK 6
#define DISPLAY_DIO 5
TM1637Display display = TM1637Display(DISPLAY_CLK, DISPLAY_DIO);

// rotary encoder: interrupts only happen in pins 2 and 3
#define ENCODER_CLK 2
#define ENCODER_DT 3
#define ENCODER_SW 4  // button

typedef struct clock_t {
  int currentState;
  int lastState;
} Clock;

// state
int counter = 0;
Clock clk;

// data
const uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
const uint8_t full[] = { 0b01110001, 0b00111110, 0b00111000, 0b00111000 };

// shortcut
bool shortcutMode = false;
int buffer[] = { 666, SECRET1, SECRET2, SECRET3 };
int n = sizeof(buffer) / sizeof(int);
int bufferIndex = 0;
int lastCounter;

void setup() {
  Serial.begin(9600);
  display.clear();
  delay(1000);
  display.setBrightness(2);

  setupRotaryEncoder();
}

// Rotary encoder with button

void setupRotaryEncoder() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT);
  clk.lastState = digitalRead(ENCODER_CLK);
  digitalWrite(ENCODER_SW, HIGH);  // remove noise from the button pin
  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), updateEncoder, CHANGE);
}

void updateEncoder() {
  clk.currentState = digitalRead(ENCODER_CLK);

  // detect transition from LOW to HIGH or from HIGH to LOW
  if ((clk.currentState == HIGH && clk.currentState != clk.lastState) || (clk.currentState == LOW && clk.currentState != clk.lastState)) {
    if (digitalRead(ENCODER_DT) != clk.currentState) {
      onClockwiseRotation();
    } else {
      onCounterClockwiseRotation();
    }
  }

  clk.lastState = clk.currentState;
}

void onClockwiseRotation() {
  if (shortcutMode) {
    bufferIndex = (bufferIndex + 1) % n;
    counter = buffer[bufferIndex];

    Serial.print("BUFFER ");
    Serial.println(bufferIndex);
  } else {
    counter++;
  }
}

void onCounterClockwiseRotation() {
  if (shortcutMode) {
    if (bufferIndex > 0) {
      bufferIndex = (bufferIndex - 1);
    } else {
      bufferIndex = n - 1;
    }
    counter = buffer[bufferIndex];
    Serial.print("BUFFER ");
    Serial.println(bufferIndex);

  } else {
    counter--;
  }
}

bool buttonPress() {
  if (digitalRead(ENCODER_SW) == LOW) {
    delay(20);  // debounce time ms
    unsigned long t1 = millis();
    while (digitalRead(ENCODER_SW) == LOW) {}
    unsigned long diff = millis() - t1;

    if (diff > 50) {
      //Serial.println("Key Press");
      return true;
    }
  }
  return false;
}

void loop() {
  display.showNumberDec(counter);

  if (buttonPress()) {
    shortcutMode = !shortcutMode;
    if (shortcutMode) {
      lastCounter = counter;
      bufferIndex = 0;
      counter = buffer[bufferIndex];
    } else {
      counter = lastCounter;
    }
    Serial.print("SHORTCUT MODE ");
    Serial.println(shortcutMode ? "ON" : "OFF");
  }

  if (counter == SECRET1 || counter == SECRET2 || counter == SECRET3) {
    playTone(counter);
    delay(1000);
    display.clear();
  }
}

void playTone(int toneFrequency) {
  // note: no need to set the buzzer pin as output. tone must do it internally.
  tone(buzzerPin, toneFrequency, 500);  // play tone for 1 second
  delay(500);
  noTone(buzzerPin);
}
