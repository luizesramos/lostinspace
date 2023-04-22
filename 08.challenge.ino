// The circuit has 5v into the common lead of the RGB LED
// Red color = (0, 255, 255)
// Red weak = (0, 128, 128)

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

// Notice if the RGB LED supports the reverse current, we subtract 255 from the color components
// In that circuit, Red would be RGB:(0, 255, 255) instead of the usual RGB:(255, 0, 0)
void writeColor(int colorComponents[rgbCount]) {
  for (int i = 0; i < rgbCount; i++) {
    analogWrite(rgbPins[i], 255 - colorComponents[i]);
  }
}

void writeColor(int r, int g, int b) {
  analogWrite(rgbPins[0], 255 - r);
  analogWrite(rgbPins[1], 255 - g);
  analogWrite(rgbPins[2], 255 - b);
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