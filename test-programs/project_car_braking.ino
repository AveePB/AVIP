#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

  int centerX = 160;
  int centerY = 120;
  int radius = 60;
  uint16_t orange = 0xFA00;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);       // poziomo
  tft.fillScreen(0x0000);   // czarne tło

   // 🔶 Pionowe paski po bokach
  tft.fillRect(0, 0, 10, 240, orange);     // lewy pasek
  tft.fillRect(310, 0, 10, 240, orange);   // prawy pasek

  // 🔶 Grube koło
  for (int r = radius - 3; r <= radius + 3; r++) {
    tft.drawCircle(centerX, centerY, r, orange);
  }

  // ❗ Biały wykrzyknik w środku

  // Pionowa kreska
  tft.fillRect(centerX - 6, centerY - 40, 12, 50, orange);  // x, y, szer, wys

  // Kropka pod spodem
  tft.fillCircle(centerX - 0, centerY + 28, 6, orange);         // x, y, promień
}

void loop() {
  // nic
}