#ifndef CALCULATOR_H
#define CALCULATOR_H

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

void calculator() {
  u8g2.setDisplayRotation(U8G2_R1);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(0, 12, "Kalkulator (demo)");
    u8g2.drawStr(0, 32, "Tu dodaj kod");
    u8g2.drawStr(0, 52, "Sterowanie: TBD");
  } while (u8g2.nextPage());

  delay(200);
}

#endif
