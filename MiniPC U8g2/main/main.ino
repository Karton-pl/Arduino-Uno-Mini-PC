#include <Arduino.h>
#include <U8g2lib.h>

// Inicjalizacja ekranu
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R1, /* reset=*/ U8X8_PIN_NONE);

// Definicje pinów
const int buttonUp = 4;
const int buttonDown = 5;
const int buttonSelect = 6;
const int potPin = A0; // nieużywany

// Wczytanie modułów
#include "calculator.h"
#include "game.h"
#include "stopwatch.h"
#include "calendar.h"
#include "eyes.h"

// Menu
int menuIndex = 0;
const int menuLength = 5;
const char *menuItems[] = {
  "Kalkulator",
  "Tetris",
  "Stoper",
  "Kalendarz",
  "Oczy"
};

bool pressOnceMain(int pin) {
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

void drawMenu() {
  u8g2.setDisplayRotation(U8G2_R0); // menu pionowe
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x13_tf);
    u8g2.drawStr(0, 12, "== MENU ==");
    for (int i = 0; i < menuLength; i++) {
      u8g2.setCursor(0, 24 + i * 10);
      if (i == menuIndex) {
        u8g2.print(">");
      } else {
        u8g2.print(" ");
      }
      u8g2.print(menuItems[i]);
    }
  } while (u8g2.nextPage());
}

void splashScreen() {
  u8g2.setDisplayRotation(U8G2_R1); // obrót 90° w lewo
  const int barWidthMax = 100;
  const int barHeight = 10;
  
  for (int w = 0; w <= barWidthMax; w += 5) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_6x13_tf);
      u8g2.drawStr(10, 20, "Ladowanie...");
      u8g2.drawFrame(10, 30, barWidthMax, barHeight);
      u8g2.drawBox(10, 30, w, barHeight);
    } while (u8g2.nextPage());
    delay(150);
  }
}

void setup() {
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonSelect, INPUT_PULLUP);
  u8g2.begin();
  splashScreen();
  randomSeed(analogRead(A5)); // do ruchów oczu
}

void loop() {
  drawMenu();

  if (pressOnceMain(buttonUp)) {
    menuIndex--;
    if (menuIndex < 0) menuIndex = menuLength - 1;
  }
  if (pressOnceMain(buttonDown)) {
    menuIndex++;
    if (menuIndex >= menuLength) menuIndex = 0;
  }

  if (pressOnceMain(buttonSelect)) {
    while (true) {
      switch (menuIndex) {
        case 0: calculator(); break;
        case 1: game(); break;
        case 2: stopwatch(); break;
        case 3: calendar(); break;
        case 4: eyes(); break;
      }
      if (pressOnceMain(buttonSelect)) break;
    }
  }

  delay(150);
}
