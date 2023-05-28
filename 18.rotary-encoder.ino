#include <TM1637Display.h>

// display setup
#define DISPLAY_CLK 6
#define DISPLAY_DIO 5
TM1637Display display = TM1637Display(DISPLAY_CLK, DISPLAY_DIO);

// rotary encoder: interrupt
#define ENCODER_CLK 2
#define ENCODER_DT 3

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

void setup() {
  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  clk.lastState = digitalRead(ENCODER_CLK);

  Serial.begin(9600);
  display.clear();
  delay(1000);
  display.setBrightness(2);

  attachInterrupt(digitalPinToInterrupt(ENCODER_CLK), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_DT), updateEncoder, CHANGE);
}

void updateEncoder() {
  clk.currentState = digitalRead(ENCODER_CLK);

  // detect transition from LOW to HIGH
  if (clk.currentState == HIGH && clk.currentState != clk.lastState) {
    // detect clockwise rotation
    if (digitalRead(ENCODER_DT) != clk.currentState) {
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
  }

  clk.lastState = clk.currentState;
}

void loop() {
  display.showNumberDec(counter);
  delay(50);

  if (counter == 50 || counter == 75) {
    showData();
  } else if (counter == 100) {
    showFull();
  }
}

void showData() {
  display.setSegments(data);
  delay(2000);
  display.clear();
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
