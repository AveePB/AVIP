#include "AVIP.h"
#include <Adafruit_GFX.h>

AVIP::AVIP(MCUFRIEND_kbv &display) : tft(display) {
    auto_x = 0;
    auto_dir = 1;

    standby_x = 0;
    standby_y = 0;
    standby_dir = 0;

    braking_scale = 1;
}

void AVIP::autonomous_state_function() {
    int size = 16;
    int y = 240 - size;
    uint16_t lime = 0x7FF0;

    tft.fillRect(auto_x, y, size, size, 0x0000);
    auto_x += auto_dir * 2;
    if (auto_x <= 0 || auto_x >= 320 - size) auto_dir *= -1;
    tft.fillRect(auto_x, y, size, size, lime);

    delay(10);
}

void AVIP::X_sign_function() {
    tft.fillRect(0, 0, 20, 240, 0xF800);
    tft.fillRect(300, 0, 20, 240, 0xF800);

    int x1 = 100, y1 = 40;
    int x2 = 220, y2 = 200;

    for (int i = -15; i <= 15; i++) {
        tft.drawLine(x1 + i, y1, x2 + i, y2, 0xF800);
        tft.drawLine(x2 + i, y1, x1 + i, y2, 0xF800);
    }
}

void AVIP::braking_function() {
    int centerX = 160;
    int centerY = 120;
    int radius = 60;
    uint16_t orange = 0xFA00;

    tft.fillRect(0, 0, 10, 240, orange);
    tft.fillRect(310, 0, 10, 240, orange);

    for (int r = radius - 3; r <= radius + 3; r++) {
        tft.drawCircle(centerX, centerY, r, orange);
    }

    tft.fillRect(centerX - 6, centerY - 40, 12, 50, orange);
    tft.fillCircle(centerX, centerY + 28, 6, orange);
}

void AVIP::arrow_function() {
    int arrowDiff = 80;
    for (int j = 0; j < 27; j++) {
        tft.fillScreen(0x0000);
        for (int i = 0; i <= 2; i++) {
            int x1 = -60 - i * arrowDiff + 20 * j;
            int x2 = x1;
            int x3 = 0 - i * arrowDiff + 20 * j;
            tft.fillTriangle(x1, 80, x2, 160, x3, 120, 0x07E0);
        }
        delay(100);
    }
}
