const int rgbCount = 3;
const int rgbPins[rgbCount] = { 11, 10, 9 };

const int sensorPin = A0;  // no need to set pinMode
int sensorValue = 0;

unsigned int batteryMax = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < rgbCount; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);

  if (batteryLevel > batteryMax) {
    ticks = 0;
    delay(20000);
  }  else {
    batteryLevel += sensorValue;
    double percentage = batteryPercentage();
    printBatteryPercentage(percentage);
    showBatteryIndicator(percentage);
    ticks += wait;
    delay(wait);
  }
}

double batteryPercentage() {
  return min(100.0, 100.0 * ((double)batteryLevel / (double)batteryMax));
}

void printBatteryPercentage(double percentage) {
  Serial.print(ticks);
  Serial.print("ms charge: ");
  Serial.print(percentage);
  Serial.println("%");
}

void showBatteryIndicator(double percentage) {
  if (percentage < 0) {
    writeColor(0, 0, 0);
  } else if (isBetween(percentage, 0, 25.0)) {
    writeColor(125, 0, 0); // red
  } else if (isBetween(percentage, 25.0, 50.0)) {
    writeColor(125, 80, 0); // yellow
  } else if (isBetween(percentage, 50.0, 75.0)) {
    writeColor(0, 125, 125);
  } else if (isBetween(percentage, 75.0, 99.0)) {
    writeColor(125, 125, 125);
  } else {
    writeColor(0, 125, 0);
  }
}

bool isBetween(double value, double min, double max) {
  return value > min && value <= max;
}

void writeColor(int r, int g, int b) {
  analogWrite(rgbPins[0], r);
  analogWrite(rgbPins[1], g);
  analogWrite(rgbPins[2], b);
}
