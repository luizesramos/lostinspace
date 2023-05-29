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
String rotationDirection;

// shortcut
bool shortcutModeEnabled = false;
int buffer[] = { SECRET1, SECRET2, SECRET3 };
int bufferIndex = 0;
unsigned long lastButtonPressMillis = 0;
int lastButtonState;

void setup() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT);
  clk.lastState = digitalRead(ENCODER_CLK);
  lastButtonState = digitalRead(ENCODER_SW);

  Serial.begin(9600);
  display.clear();
  delay(1000);
  display.setBrightness(2);

  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT), updateEncoder, CHANGE);
}

void updateEncoder() {
  clk.currentState = digitalRead(ENCODER_CLK);
  int dtPin = digitalRead(ENCODER_DT);

  // detect transition from LOW to HIGH
  if (clk.currentState == HIGH && clk.currentState != clk.lastState) {
    // detect clockwise rotation
    if (dtPin != clk.currentState) {
      counter++;
      rotationDirection = "CW";

      // counter-clockwise rotation
    } else {
      counter--;
      rotationDirection = "CCW";
    }

    Serial.print("Direction: ");
    Serial.print(rotationDirection);
    Serial.print(" Counter: ");
    Serial.println(counter);
  } else if (clk.currentState == LOW && clk.currentState != clk.lastState) {
    // Serial.print("HIGH -> LOW CLK: DT ");
    // Serial.println(dtPin);

    if (dtPin == clk.currentState) {
      counter--;
      rotationDirection = "CCW";
    } else {
      counter++;
      rotationDirection = "CW";
    }

    Serial.print("Direction: ");
    Serial.print(rotationDirection);
    Serial.print(" Counter: ");
    Serial.println(counter);
  }

  clk.lastState = clk.currentState;
}

bool buttonEventHappening = false;

void loop() {
  // int button = digitalRead(ENCODER_SW);
  // if (button == LOW) {
  //   if (!buttonEventHappening && millis() - lastButtonPressMillis > 70) {
  //     buttonEventHappening = true;
  //     Serial.println(button);
  //   }
  // } else {
  //   buttonEventHappening = false;
  //   lastButtonPressMillis = millis();
  // }
  // lastButtonState = button;


  // display.showNumberDec(counter);
  // delay(50);

  // if (shortcutModeEnabled) {
  //   shortcutMode();
  // }

  // secureMode();
}

void shortcutMode() {
}

void secureMode() {
  if (counter == SECRET1 || counter == SECRET2 || counter == SECRET3) {
    playTone(counter);
    delay(2000);
    display.clear();

    if (counter == SECRET3) {
      showFull();
    }

    counter++;  // so we don't keep playing the tone again
  }
}

void playTone(int toneFrequency) {
  // note: no need to set the buzzer pin as output. tone must do it internally.
  tone(buzzerPin, toneFrequency, 1000);  // play tone for 1 second
  delay(1000);
  noTone(buzzerPin);
}

void showFull() {
  display.setSegments(full);
  delay(3000);
  display.clear();
  delay(1000);
  display.setSegments(full);
  delay(3000);
  display.clear();
}
