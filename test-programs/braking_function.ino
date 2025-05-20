#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);       // poziomo
  tft.fillScreen(0x0000);   // czarne tło

  braking();                // wywołanie funkcji
}

void loop() {
  // możesz np. wywołać braking(); ponownie po zdarzeniu
}

// 🟠 Funkcja rysująca znak ostrzegawczy hamowania
void braking() {
  int centerX = 160;
  int centerY = 120;
  int radius = 60;
  uint16_t orange = 0xFA00;

  // 🔶 Pionowe paski po bokach
  tft.fillRect(0, 0, 10, 240, orange);     // lewy pasek
  tft.fillRect(310, 0, 10, 240, orange);   // prawy pasek

  // 🔶 Grube koło
  for (int r = radius - 3; r <= radius + 3; r++) {
    tft.drawCircle(centerX, centerY, r, orange);
  }

  // ❗ Wykrzyknik w środku
  // Kreska
  tft.fillRect(centerX - 6, centerY - 40, 12, 50, orange);

  // Kropka
  tft.fillCircle(centerX, centerY + 28, 6, orange);
}
