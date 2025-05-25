/**
 * @file avip.h
 * @brief AVIP Display Interface for TFT screen on Arduino-based robots.
 * 
 * Provides symbolic display functions for autonomous mode, braking alerts, and pedestrian warnings
 * using geometric drawing on a TFT screen.
 */

#ifndef AVIP_H
#define AVIP_H

// Color constants in RGB565 format
#define ORANGE 0xFA60  ///< Orange color
#define YELLOW 0xFFE0  ///< Yellow color
#define BLACK  0x0000  ///< Black color
#define WHITE  0xFFFF  ///< White color
#define GREEN  0x07E0  ///< Green color
#define BLUE   0x001F  ///< Blue color
#define RED    0xF800  ///< Red color

#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>

/**
 * @class AVIP
 * @brief A custom TFT screen interface for robot signaling using MCUFRIEND_kbv.
 * 
 * Inherits from the MCUFRIEND_kbv class and adds high-level display functions
 * for intuitive road signal icons and alerts (Autonomous Mode, Braking, and Pedestrian Crosswalk).
 */
class AVIP : public MCUFRIEND_kbv {
  public:

    /**
     * @brief Display the Autonomous Mode visual sign on the TFT.
     */
    void displayAutonomousMode();

    /**
     * @brief Display a Braking alert sign on the TFT.
     */
    void displayBraking();

    /**
     * @brief Display the "Give Way to Pedestrians" or "Crosswalk Clear" sign on the TFT.
     */
    void displayGiveWayToPedestrians();

    /**
     * @brief Clear the TFT screen.
     */
    void clearDisplay();
};

#endif
