#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "avip.h"

MCUFRIEND_kbv tft;

void setup() {
  int ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(3);
}

void loop() {
  AVIP::clearDisplay(tft);
  AVIP::displayAutonomousMode(tft);
  delay(1000);

  AVIP::clearDisplay(tft);
  AVIP::displayBraking(tft);
  delay(1000);

  AVIP::clearDisplay(tft);
  AVIP::displayGiveWayToPedestrians(tft);
  delay(1000);
}
