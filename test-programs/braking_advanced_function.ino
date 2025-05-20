#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

const int centerX = 160;
const int centerY = 120;
const int maxScale = 40;
int scale = 1;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);            // poziomo
  tft.fillScreen(0x0000);        // czarne tło
}

void loop() {
  braking_advanced();
}

// 🔶 Funkcja: animowany znak ostrzegawczy (rosnące koło i wykrzyknik)
void braking_advanced() {
  drawSymbol(scale, 0x0000);   // wymazanie poprzedniego
  scale++;
  if (scale > maxScale) scale = 1;
  drawSymbol(scale, 0xFA00);   // narysuj aktualny
  delay(250);
}

void drawSymbol(int s, uint16_t color) {
  int r = s * 2; // promień koła rośnie szybciej niż wykrzyknik

  // 🔶 Grube koło
  for (int i = -2; i <= 2; i++) {
    tft.drawCircle(centerX, centerY, r + i, color);
  }

  // ❗ Wykrzyknik – proporcjonalnie umieszczony
  int rectWidth  = s / 2 + 2;
  int rectHeight = s * 1.5;
  int kreskaY    = centerY - rectHeight / 2 - s / 2;

  tft.fillRect(
    centerX - rectWidth / 2,
    kreskaY,
    rectWidth,
    rectHeight,
    color
  );

  // Kropka wykrzyknika
  int dotRadius = s / 5 + 2;
  int kropkaY   = centerY + s;

  tft.fillCi
