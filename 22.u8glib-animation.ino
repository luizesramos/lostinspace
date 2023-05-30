// Tools >> Manage Libraries >> U8glib

#include <U8glib.h>

U8GLIB_SH1106_128X64 scr(U8G_I2C_OPT_NONE);

// State
uint8_t drawState = 0;
const int pages = 9;
const int pageStates = pages * 8;  // 8 demo routines

void setup() {
  //scr.setRot180(); // for flipping the display
  scr.setColorIndex(1);  // default color for the pixel (monochrome)
#if defined(ARDUINO)
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
#endif
}

void loop() {
  scr.firstPage();
  do {
    draw();
  } while (scr.nextPage());

  drawState = (drawState + 1) % pageStates;  // 9 pages x 8 states

  delay(200);
}

#define DIV_BY_8(x) (x >> 3)
#define LSB3(x) (x & 7)

void draw() {
  prepareDisplay();
  switch (DIV_BY_8(drawState)) {
    case 0:
      drawBox(LSB3(drawState));
      break;

    case 1:
      drawCircle(LSB3(drawState));
      break;

    case 2:
      drawFrame(LSB3(drawState));
      break;

    case 3:
      drawString(LSB3(drawState));
      break;

    case 4:
      drawLine(LSB3(drawState));
      break;

    case 5:
      drawTriangle(LSB3(drawState));
      break;

    case 6:
      drawAsciiTable("ASCII page 1", 32);
      break;

    case 7:
      drawAsciiTable("ASCII page 2", 160);
      break;

    case 8:
      drawExtraPage(LSB3(drawState));
      break;
  }
}

void prepareDisplay() {
  scr.setFont(u8g_font_6x10);
  scr.setFontRefHeightExtendedText();
  scr.setDefaultForegroundColor();
  scr.setFontPosTop();
}

void drawBox(uint8_t a) {
  scr.drawStr(0, 0, "drawBox");
  scr.drawBox(5, 10, 20, 10);
  scr.drawBox(10 + a, 15, 30, 7);
  scr.drawStr(0, 30, "drawFrame");
  scr.drawFrame(5, 10 + 30, 20, 10);
  scr.drawFrame(10 + a, 15 + 30, 30, 7);
}

void drawCircle(uint8_t a) {
  scr.drawStr(0, 0, "drawDisc");
  scr.drawDisc(10, 18, 9);
  scr.drawDisc(24 + a, 16, 7);
  scr.drawStr(0, 30, "drawCircle");
  scr.drawCircle(10, 18 + 30, a + 1);
  scr.drawCircle(24 + a, 16 + 30, 7);
}

void drawFrame(uint8_t a) {
  scr.drawStr(0, 0, "drawRFrame");
  scr.drawRFrame(5, 10, 40, 30, a + 1);
  scr.drawRBox(50, 10, 25, 40, a + 1);
}

void drawString(uint8_t a) {
  scr.drawStr(30 + a, 31, " 0");
  scr.drawStr90(30, 31 + a, " 90");
  scr.drawStr180(30 - a, 31, " 180");
  scr.drawStr270(30, 31 - a, " 270");
}

void drawLine(uint8_t a) {
  scr.drawStr(0, 0, "drawLine");
  scr.drawLine(7 + a, 10, 40, 55);
  scr.drawLine(7 + a * 2, 10, 60, 55);
  scr.drawLine(7 + a * 3, 10, 80, 55);
  scr.drawLine(7 + a * 4, 10, 100, 55);
}

void drawTriangle(uint16_t b) {
  scr.drawStr(0, 0, "drawTriangle");
  scr.drawTriangle(14, 7, 45, 30, 10, 40);
  scr.drawTriangle(14 + b, 7 - b, 45 + b, 30 - b, 57 + b, 10 - b);
  scr.drawTriangle(57 + b * 2, 10, 45 + b * 2, 30, 86 + b * 2, 53);
  scr.drawTriangle(10 + b, 40 + b, 45 + b, 30 + b, 86 + b, 53 + b);
}

void drawAsciiTable(const char *label, int asciiTableOffset) {
  char s[2] = " ";
  uint8_t x, y;
  scr.drawStr(0, 0, label);
  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 16; x++) {
      s[0] = y * 16 + x + asciiTableOffset;
      scr.drawStr(x * 7, y * 10 + 10, s);
    }
  }
}

void drawExtraPage(uint8_t a) {
  if (scr.getMode() == U8G_MODE_HICOLOR || scr.getMode() == U8G_MODE_R3G3B2) {
    drawRGB(a);
  } else if (scr.getMode() == U8G_MODE_GRAY2BIT) {
    drawGrayScale(a);
  } else {
    scr.drawStr(0, 12, "setScale2x2");
    scr.setScale2x2();
    scr.drawStr(0, 6 + a, "setScale2x2");
    scr.undoScale();
  }
}

void drawRGB(uint8_t a) {
  u8g_uint_t r, g, b;
  b = a << 5;
  for (g = 0; g < 64; g++) {
    for (r = 0; r < 64; r++) {
      scr.setRGB(r << 2, g << 2, b);
      scr.drawPixel(g, r);
    }
  }
  scr.setRGB(255, 255, 255);
  scr.drawStr(66, 0, "Color Page");
}

void drawGrayScale(uint8_t a) {
  scr.drawStr(66, 0, "Gray Level");
  for (int i = 1; i < 4; i++) {
    scr.setColorIndex(i);
    scr.drawBox((i - 1) * a, 4 + (i - 1) * a, 64 - ((i - 1) << 1) * a, 32 - ((i - 1) << 1) * a);
    scr.drawBox(70, 20, 4, 12);
  }
}