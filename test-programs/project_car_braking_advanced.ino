#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

int scale = 1;
const int maxScale = 40;
const int centerX = 160;
const int centerY = 120;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);            // poziomy ekran
  tft.fillScreen(0x0000);        // czarne tło
}

void loop() {
  drawSymbol(scale, 0x0000);   // wymazanie (czarne)
  scale++;
  if (scale > maxScale) scale = 1;
  drawSymbol(scale, 0xFA00);   // rysowanie (pomarańcz/czerwony)
  delay(250);
}

void drawSymbol(int s, uint16_t color) {
  int r = s * 2; // koło 2x większe niż wykrzyknik

  // 🟠 Koło – gruby kontur
  for (int i = -2; i <= 2; i++) {
    tft.drawCircle(centerX, centerY, r + i, color);
  }

  // ❗ Wykrzyknik – przesunięcie kreski lekko do góry, kropki lekko w dół

  // Kreska
  int rectWidth  = s / 2 + 2;
  int rectHeight = s * 1.5;
  int kreskaY = centerY - rectHeight / 2 - s / 2; // lekko wyżej względem środka

  tft.fillRect(
    centerX - rectWidth / 2,
    kreskaY,
    rectWidth,
    rectHeight,
    color
  );

  // Kropka
  int dotRadius = s / 5 + 2;
  int kropkaY = centerY + s; // trochę niżej względem środka

  tft.fillCircle(centerX, kropkaY, dotRadius, color);
}