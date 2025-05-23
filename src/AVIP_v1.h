#ifndef AVIP_H
#define AVIP_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>

class AVIP {
public:
    AVIP(MCUFRIEND_kbv &display);

    void autonomous_state_function();
    void X_sign_function();
    void braking_function();
    void arrow_function();

private:
    MCUFRIEND_kbv &tft;

    // wewnętrzne zmienne animacji
    int auto_x, auto_dir;
    int standby_x, standby_y, standby_dir;
    int braking_scale;
};

#endif
