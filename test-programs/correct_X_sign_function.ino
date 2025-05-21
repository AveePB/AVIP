#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

bool pokazX = true;

void setup() {
  uint16_t ID = tft.readID();     // 320x240
  tft.begin(ID);
  tft.setRotation(3);             // poziomo
  tft.fillScreen(0x0000);         // czarne tło

  X_sign();                       // wywołanie funkcji rysującej znak X
}

void loop() {
  // Możesz np. wywołać X_sign(); ponownie w reakcji na zdarzenie
}

// 🟥❌ Funkcja rysująca znak ostrzegawczy z czerwonym X
void X_sign() {
  // 🟥 Pionowe paski po bokach
  tft.fillRect(0, 0, 20, 240, 0xF800);      // lewy pasek
  tft.fillRect(300, 0, 20, 240, 0xF800);    // prawy pasek

  // ❌ Środkowy X – dwie ukośne linie
  int x1 = 100, y1 = 40;
  int x2 = 220, y2 = 200;

  for (int i = -15; i <= 15; i++) {
    tft.drawLine(x1 + i, y1, x2 + i, y2, 0xF800);
    tft.drawLine(x2 + i, y1, x1 + i, y2, 0xF800);
  }

  pokazX = !pokazX;
  delay (100);
}