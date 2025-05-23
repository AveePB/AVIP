#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "avip.h"

void AVIP::displayAutonomousMode(MCUFRIEND_kbv& tft) {
  int centerX = 160;
  int centerY = 100;
  int radius = 60;

  // Draw thicker white border (outer ring)
  tft.fillCircle(centerX, centerY, 64, WHITE); // Outer white ring
  tft.fillCircle(centerX, centerY, 60, GREEN); // Inner green circle

  // Draw the letters "AV" centered inside the circle
  const char* letters = "AV";
  int lettersTextSize = 6;  // Large size for inside circle

  // Measure text width to center it
  int16_t x1, y1;
  uint16_t w, h;
  tft.setTextSize(lettersTextSize);
  tft.getTextBounds(letters, 0, 0, &x1, &y1, &w, &h);

  // Position letters so they're centered at (centerX, centerY)
  int lettersX = centerX - w / 2;
  int lettersY = centerY - h / 2;

  tft.setTextColor(WHITE);
  tft.setCursor(lettersX, lettersY);
  tft.print(letters);

  // Draw text below the circle: "Autonomous Mode"
  const char* msg = "Autonomous Mode";
  int textSize = 2;
  int charWidth = 6;
  int textWidth = strlen(msg) * textSize * charWidth;

  tft.setTextSize(textSize);
  tft.setTextColor(WHITE);
  tft.setCursor(centerX - textWidth / 2, centerY + 80);
  tft.print(msg);
}

void AVIP::displayBraking(MCUFRIEND_kbv& tft) {
  int centerX = 160;
  int centerY = 100;
  int radius = 60;

  // Thicker white border (drawn first)
  tft.fillCircle(centerX, centerY, 64, WHITE); // Outer ring
  tft.fillCircle(centerX, centerY, 60, ORANGE);  // Inner orange

  // Vertical bar of the exclamation mark
  tft.fillRect(centerX - 6, centerY - 40, 12, 50, WHITE);  // x, y, width, height

  // Dot below the bar
  tft.fillCircle(centerX, centerY + 28, 6, WHITE);         // x, y, radius

  // Label text (centered)
  const char* msg = "Braking!!!";
  int textSize = 2;
  int charWidth = 6;
  int textWidth = strlen(msg) * textSize * charWidth;

  tft.setTextSize(textSize);
  tft.setTextColor(WHITE);
  tft.setCursor(centerX - textWidth / 2, centerY + 80);
  tft.print(msg);
}

void AVIP::displayGiveWayToPedestrians(MCUFRIEND_kbv& tft) {
  int centerX = 160;
  int centerY = 100;

  // Thicker white border (drawn first)
  tft.fillCircle(centerX, centerY, 64, WHITE); // Outer ring
  tft.fillCircle(centerX, centerY, 60, BLUE);  // Inner blue

  // Walking stick figure
  int px = centerX;
  int py = centerY - 10; // Slightly above center

  tft.fillCircle(px, py - 20, 5, WHITE);             // Head
  tft.drawLine(px, py - 15, px, py + 10, WHITE);     // Body
  tft.drawLine(px, py - 5, px - 10, py + 5, WHITE);  // Left arm
  tft.drawLine(px, py - 5, px + 10, py + 5, WHITE);  // Right arm
  tft.drawLine(px, py + 10, px - 8, py + 22, WHITE); // Left leg
  tft.drawLine(px, py + 10, px + 8, py + 22, WHITE); // Right leg

  // Centered zebra crossing
  int numBars = 4;
  int barWidth = 6;
  int barSpacing = 10;
  int totalWidth = (numBars - 1) * barSpacing + barWidth;
  int startX = centerX - totalWidth / 2;
  int barY = py + 28;

  for (int i = 0; i < numBars; i++)
    tft.fillRect(startX + i * barSpacing, barY, barWidth, 8, WHITE);

  // Label text (centered)
  const char* msg = "Crosswalk Clear";
  int textSize = 2;
  int charWidth = 6;
  int textWidth = strlen(msg) * textSize * charWidth;

  tft.setTextSize(textSize);
  tft.setTextColor(WHITE);
  tft.setCursor(centerX - textWidth / 2, centerY + 80);
  tft.print(msg);
}

void AVIP::clearDisplay(MCUFRIEND_kbv& tft) {
  tft.fillScreen(BLACK);
}
