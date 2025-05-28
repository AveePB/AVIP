#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include "avip.h"

// Signal constants
#define NO_SIGNAL -1
#define AV_MODE 0
#define BRAKING 1
#define GIVE_WAY 2

// Pin constants
#define PIN_1 31
#define PIN_2 33

// Global variables
int flag = NO_SIGNAL, prev_flag = NO_SIGNAL;
AVIP avip;

// Setup function
void setup() {
  // Initialize avip
  int ID = avip.readID();
  avip.begin(ID);
  avip.setRotation(1);

  // Initialize pins
  pinMode(PIN_1, INPUT);
  pinMode(PIN_2, INPUT);
}

// Loop function
void loop() {
  // Read digital signals
  int o1 = digitalRead(PIN_1), o2 = digitalRead(PIN_2);

  // Set current flag
  if (o1 == 0 && o2 == 1) flag = AV_MODE; // 01
  else if (o1 == 1 && o2 == 0) flag = BRAKING; // 10
  else if (o1 == 1 && o2 == 1) flag = GIVE_WAY; // 11
  else if (o1 == 0 && o2 == 0) flag = NO_SIGNAL; // 00

  // Update avip display
  if (flag != prev_flag || flag == NO_SIGNAL) {
    // Clear avip display
    avip.clearDisplay();

    // Signal autonomous mode 
    if (flag == AV_MODE) avip.displayAutonomousMode();

    // Signal braking
    if (flag == BRAKING) avip.displayBraking();

    // Signal clear crosswalk to pedestrians
    if (flag == GIVE_WAY) avip.displayGiveWayToPedestrians();
  }

  // Set current flag as previous one
  prev_flag = flag;
}
