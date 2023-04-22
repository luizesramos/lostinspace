// On the hero board, ints are 16-bit. Values represented with `unsigned int` go from 0-64k 
typedef unsigned int BatteryLevel;
typedef unsigned int ClockTicks;

BatteryLevel maxLevel = 50000;
BatteryLevel currentLevel = 0;

ClockTicks ticks = 0;
ClockTicks waitMillis = 100;

const int outputPin = LED_BUILTIN;
const int analogInputPin = A0;

double percentFull() {
  return min(100.0, 100.0 * ((double)currentLevel / (double)maxLevel));
}

void printBatteryCharge() {
  Serial.print(ticks);
  Serial.print("ms | Charge: ");
  Serial.print(percentFull());
  Serial.println("%");
}

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(analogInputPin);
  currentLevel += sensorValue;
  ticks += waitMillis;

  delay(waitMillis);

  printBatteryCharge();

  if (currentLevel >= maxLevel) {
    currentLevel = maxLevel;
    ticks = 0;
    delay(20000); // long pause to discharge battery
  }
}
