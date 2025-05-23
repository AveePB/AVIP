#ifndef AVIP_H
#define AVIP_H

#define ORANGE 0xFA60
#define YELLOW 0xFFE0  
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREEN 0x07E0
#define BLUE 0x001F
#define RED 0xF800

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

namespace AVIP {
  void displayAutonomousMode(MCUFRIEND_kbv& tft);
  void displayBraking(MCUFRIEND_kbv& tft);
  void displayGiveWayToPedestrians(MCUFRIEND_kbv& tft);
  void clearDisplay(MCUFRIEND_kbv& tft);
};

#endif