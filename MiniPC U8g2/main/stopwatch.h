#ifndef STOPWATCH_H
#define STOPWATCH_H

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern const int buttonUp;
extern const int buttonSelect;

unsigned long elapsedTime = 0;
unsigned long lastStartTime = 0;
bool running = false;

bool pressOnce(int pin) {
  static bool lastState[10] = {false};
  bool state = !digitalRead(pin);
  if (state && !lastState[pin]) {
    lastState[pin] = true;
    return true;
  } else if (!state) {
    lastState[pin] = false;
  }
  return false;
}

void stopwatch() {
  if (pressOnce(buttonSelect)) {
    if (running) {
      elapsedTime += millis() - lastStartTime;
      running = false;
    } else {
      lastStartTime = millis();
      running = true;
    }
  }

  if (pressOnce(buttonUp)) {
    running = false;
    elapsedTime = 0;
    lastStartTime = 0;
  }

  unsigned long currentTime = elapsedTime;
  if (running) {
    currentTime += millis() - lastStartTime;
  }

  unsigned long seconds = currentTime / 1000;
  unsigned long millisecs = currentTime % 1000;

  char buffer[32];
  sprintf(buffer, "%03lu.%03lu s", seconds, millisecs);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(0, 12, "Stoper:");
    u8g2.setCursor(0, 32);
    u8g2.print(buffer);
    u8g2.setCursor(0, 52);
    u8g2.print("Select=Start/Stop");
    u8g2.setCursor(0, 64);
    u8g2.print("Gora=Reset");
  } while (u8g2.nextPage());

  delay(100);
}

#endif
