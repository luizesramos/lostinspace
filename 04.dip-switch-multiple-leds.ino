const int nPins = 3;
const int switchPin[nPins] = { 2, 3, 4};
const int ledPin[nPins] = { 5, 6, 7 };
int switchState[nPins] = { LOW, LOW, LOW };

void setup() {
  for(int i = 0; i < nPins; i++) {
    pinMode(switchPin[i], INPUT);
    digitalWrite(ledPin[i], LOW);
  }
}

void loop() {
  for(int i=0; i<nPins; i++) {
    switchState[i] = digitalRead(switchPin[i]);
    digitalWrite(ledPin[i], switchState[i]);
  }
}
