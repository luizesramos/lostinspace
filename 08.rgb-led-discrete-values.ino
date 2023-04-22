const int rgbCount = 3;
const int rgbPins[rgbCount] = { 11, 10, 9 };

// With 3 bits we have 2^3 = 8 states
const int maxColors = 1 << 3;
int color = 0;

void printColor(int color, int colorComponents[rgbCount]) {
    Serial.print(color);
    Serial.print(" / ");
    Serial.print(maxColors);
    Serial.print(" rgb: ");
    Serial.print(colorComponents[0]);
    Serial.print(colorComponents[1]);
    Serial.print(colorComponents[2]);
    Serial.println();
}

void setup() {
    Serial.begin(9600);

    for (int i=0; i<rgbCount; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {
    color = (color + 1) % maxColors;

    int values[rgbCount] = {
      (color & 0x4) > 0 ? HIGH : LOW,
      (color & 0x2) > 0 ? HIGH : LOW,
      (color & 0x1) > 0 ? HIGH : LOW
    };

    printColor(color, values);

    for (int i=0; i < rgbCount; i++) {
      digitalWrite(rgbPins[i], values[i]);
    }

    delay(1000);
}