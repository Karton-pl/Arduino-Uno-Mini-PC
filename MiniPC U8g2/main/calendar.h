#ifndef CALENDAR_H
#define CALENDAR_H

#include <Arduino.h>

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern const int buttonUp;
extern const int buttonDown;
extern const int buttonSelect;

int calDay = 1;
int calMonth = 1;
int calYear = 2024;

enum DateField { FIELD_DAY, FIELD_MONTH, FIELD_YEAR };
DateField currentField = FIELD_DAY;

bool pressOnceCal(int pin) {
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

int daysInMonth(int m, int y) {
  if (m == 2) return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 29 : 28;
  if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
  return 31;
}

void calendar() {
  if (pressOnceCal(buttonUp)) {
    switch (currentField) {
      case FIELD_DAY:
        calDay++;
        if (calDay > daysInMonth(calMonth, calYear)) calDay = 1;
        break;
      case FIELD_MONTH:
        calMonth++;
        if (calMonth > 12) calMonth = 1;
        if (calDay > daysInMonth(calMonth, calYear)) calDay = daysInMonth(calMonth, calYear);
        break;
      case FIELD_YEAR:
        calYear++;
        if (calYear > 2099) calYear = 2000;
        break;
    }
  }

  if (pressOnceCal(buttonDown)) {
    switch (currentField) {
      case FIELD_DAY:
        calDay--;
        if (calDay < 1) calDay = daysInMonth(calMonth, calYear);
        break;
      case FIELD_MONTH:
        calMonth--;
        if (calMonth < 1) calMonth = 12;
        if (calDay > daysInMonth(calMonth, calYear)) calDay = daysInMonth(calMonth, calYear);
        break;
      case FIELD_YEAR:
        calYear--;
        if (calYear < 2000) calYear = 2099;
        break;
    }
  }

  if (pressOnceCal(buttonSelect)) {
    currentField = static_cast<DateField>((static_cast<int>(currentField) + 1) % 3);
  }

  char buf[32];
  sprintf(buf, "Data: %02d/%02d/%04d", calDay, calMonth, calYear);

  u8g2.setDisplayRotation(U8G2_R1);
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(0, 12, "Kalendarz");
    u8g2.drawStr(0, 32, buf);

    switch (currentField) {
      case FIELD_DAY:
        u8g2.drawStr(0, 52, "Edytuj: Dzien");
        break;
      case FIELD_MONTH:
        u8g2.drawStr(0, 52, "Edytuj: Miesiac");
        break;
      case FIELD_YEAR:
        u8g2.drawStr(0, 52, "Edytuj: Rok");
        break;
    }
    u8g2.drawStr(0, 64, "Select = zmien pole");
  } while (u8g2.nextPage());

  delay(150);
}

#endif

