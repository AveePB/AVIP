#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;

const int size = 16;               // rozmiar kwadratu
int x = 0;                         // pozycja pozioma
int y = 240 - size;                // dolna krawędź
int direction = 1;                 // kierunek: 1 = prawo, -1 = lewo
uint16_t lime = 0x7FF0;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);
  tft.fillScreen(0x0000);
}

void loop() {
  autonomous_state();  // wywołanie funkcji animacji
}

// 🟩 Funkcja: kwadrat przesuwający się lewo-prawo na dole ekranu
void autonomous_state() {
  // wyczyść poprzedni
  tft.fillRect(x, y, size, size, 0x0000);

  // aktualizuj pozycję
  x += direction * 2;

  // zmiana kierunku na końcu
  if (x <= 0 || x >= 320 - size) {
    direction *= -1;
  }

  // narysuj nowy
  tft.fillRect(x, y, size, size, lime);

  delay(10);  // tempo animacji
}

