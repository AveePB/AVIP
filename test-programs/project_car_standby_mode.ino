#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

const int size = 16;
int x = 0;
int y = 0;
int direction = 0;  // 0=right, 1=down, 2=left, 3=up
uint16_t lime = 0x7FF0;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);  // poziomo
  tft.fillScreen(0x0000);
}

void loop() {
  // 1. Wymaż poprzedni kwadrat
  tft.fillRect(x, y, size, size, 0x0000);

  // 2. Zaktualizuj pozycję
  switch (direction) {
    case 0: // ➡️ w prawo
      x += 2;
      if (x >= 320 - size) {
        x = 320 - size;
        direction = 1;
      }
      break;

    case 1: // ⬇️ w dół
      y += 2;
      if (y >= 240 - size) {
        y = 240 - size;
        direction = 2;
      }
      break;

    case 2: // ⬅️ w lewo
      x -= 2;
      if (x <= 0) {
        x = 0;
        direction = 3;
      }
      break;

    case 3: // ⬆️ w górę
      y -= 2;
      if (y <= 0) {
        y = 0;
        direction = 0;
      }
      break;
  }

  // 3. Narysuj nowy kwadrat
  tft.fillRect(x, y, size, size, lime);

  delay(20); // tempo ruchu
}
