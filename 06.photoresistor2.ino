int sensorPin = A0;
const int nPins = 3;
int currentPin = 0;
int ledPins[nPins] = { 5, 6, 7 };
int photoresistorValue = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < nPins; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Max value is 1024
  photoresistorValue = analogRead(sensorPin);
  digitalWrite(ledPins[currentPin], HIGH);
  delay(photoresistorValue);
  digitalWrite(ledPins[currentPin], LOW);
  delay(photoresistorValue);
  currentPin = (currentPin + 1) % nPins;
  
  Serial.println(photoresistorValue);
}
