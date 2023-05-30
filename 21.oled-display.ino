// Tools >> Manage Libraries >> U8glib

#include <U8glib.h>

U8GLIB_SH1106_128X64 display(U8G_I2C_OPT_NONE);

void setup() {
  //display.setRot180(); // for flipping the display
  display.setColorIndex(1); // default color for the pixel (monochrome)
}

void loop() {
  display.firstPage();
  do {
    draw();
  } while (display.nextPage());
}

void draw() {
  display.setFont(u8g_font_unifont);
  display.drawStr(20, 22, "Hello World!");
  display.drawCircle(64, 42, 360 * DEG_TO_RAD);
}