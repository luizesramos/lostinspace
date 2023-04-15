// Hero board is Arduin Uno compatible and connects via serial port
const int min = 10;
const int max = 900;
int i = max;
int delta = 10;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (i + delta >= max) {
    i = max;
    delta = -delta;
  } else if (i - delta <= min) {
    i = min;
    delta = abs(delta);
  } else {
    i += delta;
  }

  onOff(i, 500);
}

void onOff(int onDelayMillis, int offDelayMillis) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(onDelayMillis);
  digitalWrite(LED_BUILTIN, LOW);
  delay(offDelayMillis);
}
  