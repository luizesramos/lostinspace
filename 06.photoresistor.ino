int sensorPin = A0;
int ledPin = 6;
int photoresistorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Max value is 1024
  photoresistorValue = analogRead(sensorPin);
  digitalWrite(ledPin, HIGH);
  delay(photoresistorValue);
  digitalWrite(ledPin, LOW);
  delay(photoresistorValue);
  Serial.println(photoresistorValue);
}
