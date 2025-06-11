#ifndef EYES_H
#define EYES_H

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;

int eyeX = 40, eyeY = 25;
int eyeRadius = 10;
int pupilRadius = 5;

void eyes() {
  u8g2.setDisplayRotation(U8G2_R0);
  
  // Prosty ruch gałek
  static unsigned long lastMove = 0;
  static int dx = 1;
  static int dy = 1;
  unsigned long now = millis();

  if (now - lastMove > 50) {
    eyeX += dx;
    eyeY += dy;

    if (eyeX < 30 || eyeX > 50) dx = -dx;
    if (eyeY < 20 || eyeY > 40) dy = -dy;

    lastMove = now;
  }

  u8g2.firstPage();
  do {
    u8g2.drawCircle(30, 32, eyeRadius); // lewe oko
    u8g2.drawCircle(50, 32, eyeRadius); // prawe oko

    u8g2.drawDisc(eyeX, eyeY, pupilRadius); // lewa źrenica
    u8g2.drawDisc(eyeX + 20, eyeY, pupilRadius); // prawa źrenica
  } while (u8g2.nextPage());

  delay(50);
}

#endif
