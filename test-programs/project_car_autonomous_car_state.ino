#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

const int size = 16;               // rozmiar kwadratu
int x = 0;                         // początkowa pozycja
int y = 240 - size;                // dolna krawędź ekranu
int direction = 1;                 // 1 = prawo, -1 = lewo
uint16_t lime = 0x7FF0;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);              // poziomy ekran
  tft.fillScreen(0x0000);          // czarne tło
}

void loop() {
  // 🧹 Wymazanie poprzedniego kwadratu
  tft.fillRect(x, y, size, size, 0x0000);

  // ➡️ lub ⬅️ Aktualizacja pozycji
  x += direction * 2;              // krok: 2 piksele

  // 🔁 Zmiana kierunku na końcach ekranu
  if (x <= 0 || x >= 320 - size) {
    direction *= -1;              // odbij w przeciwną stronę
  }

  // 🟩 Rysuj nowy kwadrat
  tft.fillRect(x, y, size, size, lime);

  delay(10);                      // tempo animacji
}
