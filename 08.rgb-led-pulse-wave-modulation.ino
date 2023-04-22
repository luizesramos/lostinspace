const int rgbCount = 3;
const int rgbPins[rgbCount] = { 11, 10, 9 };

void printColor(int colorComponents[rgbCount]) {
  Serial.print("rgb: ");
  Serial.print(colorComponents[0]);
  Serial.print(", ");
  Serial.print(colorComponents[1]);
  Serial.print(", ");
  Serial.print(colorComponents[2]);
  Serial.println();
}

void writeColor(int colorComponents[rgbCount]) {
  for (int i = 0; i < rgbCount; i++) {
    analogWrite(rgbPins[i], colorComponents[i]);
  }
}

void writeColor(int r, int g, int b) {
  analogWrite(rgbPins[0], r);
  analogWrite(rgbPins[1], g);
  analogWrite(rgbPins[2], b);
}


void setup() {
  Serial.begin(9600);

  for (int i = 0; i < rgbCount; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  writeColor(125, 0, 0);  // red (less intense)
  delay(800);
  writeColor(0, 125, 0);  // green
  delay(800);
  writeColor(0, 0, 125);  // blue
  delay(800);
  writeColor(64, 32, 0);  // yellow
  delay(800);
  writeColor(125, 0, 125);  // purple
  delay(800);
  writeColor(125, 125, 125);  // white (weak)
  delay(800);
  writeColor(255, 255, 255);  // white (strong)
  delay(800);


  // int values[rgbCount] = {
  //   random(255),
  //   random(255),
  //   random(255)
  // };
  // printColor(values);
  // writeColor(values);
  // delay(1000);
}