#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

MCUFRIEND_kbv tft;
int i, j;
int x1, x2, x3;
int arrowDiff = 80;

String x1_str, x2_str, x3_str, t_str;

void setup() {
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);      // poziomy ekran
  tft.fillScreen(0x0000);  // czarne tło
  tft.setTextColor(0xFFE0);         // 🟡 żółty
  tft.setTextSize(2);
}

void loop() {
  int liczba = 42;
float temp = 23.7;
String tekst = "Cześć";

/*Serial.print("Liczba: ");
Serial.println(liczba);

Serial.print("Temperatura: ");
Serial.println(temp);

Serial.print("Tekst: ");
Serial.println(tekst);*/



  // 🟢 Zielona strzałka w prawo
  // Grot strzałki (trójkąt)
  for (j = 0; j < 27; j++) {
    tft.fillScreen(0x0000);
    for (i = 0; i <= 2; i++) {
      x1 = -60 - i * arrowDiff + 20 * j;
      x2 = -60 - i * arrowDiff + 20 * j;
      x3 = 0 - i * arrowDiff + 20 * j;
      tft.fillTriangle(
        x1, 80,   // wierzchołek górny
        x2, 160,  // wierzchołek dolny
        x3, 120,  // czubek strzałki (prawo)
        0x07E0                              // kolor zielony
      );
      delay(10);
    }
    /*tft.setCursor(10, 220);
    //t_str =  String(i);
    x1_str = String(x1);
    x2_str = String(x2);
    x3_str = String(x3);
    //tft.print(" T: " + t_str);
    tft.print(" G: " + x1_str);
    tft.print(" D: " + x2_str);
    tft.print(" C: " + x3_str);
    delay(100);*/
  }
}