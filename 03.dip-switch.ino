int LED_PIN = 12;
int SWITCH_PIN = 8;
int shouldFlash = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  shouldFlash = digitalRead(SWITCH_PIN);
  if(shouldFlash == HIGH) {
    digitalWrite(LED_PIN, LOW);
    delay(1000);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
