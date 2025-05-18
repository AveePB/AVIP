#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

bool pokazX = true;

void setup() {
  uint16_t ID = tft.readID();     // 320x240
  tft.begin(ID);
  tft.setRotation(3);             // poziomo
  tft.fillScreen(0x0000);         // czarne tło


  // 🟥 Pionowe kreski
    tft.fillRect(0, 0, 20, 240, 0xF800);      // lewy pasek
    tft.fillRect(300, 0, 20, 240, 0xF800);    // prawy pasek (320 - 20)

  // ❌ Środkowy X – dwie ukośne linie
  // Zaczynamy X w obszarze centralnym (np. 120x60 do 200x180)
  int x1 = 100, y1 = 40;
  int x2 = 220, y2 = 200;

  for (int i = -15; i <= 15; i++) {
    tft.drawLine(x1 + i, y1, x2 + i, y2, 0xF800);
    tft.drawLine(x2 + i, y1, x1 + i, y2, 0xF800); 
  }
}

void loop() {
  /*int x1 = 100, y1 = 40;
  int x2 = 220, y2 = 200;

  // Kolor X lub czarne wymazywanie
  uint16_t kolor = pokazX ? 0xF800 : 0x0000;

  // Rysuj lub ukryj X
  for (int i = -15; i <= 15; i++) {
    tft.drawLine(x1 + i, y1, x2 + i, y2, kolor);
    tft.drawLine(x2 + i, y1, x1 + i, y2, kolor);
  }

  pokazX = !pokazX;  // Przełącz widoczność X
  delay(500);        // Czas mrugnięcia*/
}