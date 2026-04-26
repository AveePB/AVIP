#ifndef RCAR_H
#define RCAR_H

#include <stdint.h>
#include "serialib.h"
#include "rcar.h"

namespace mz {

    inline const char* CMD_VEL_PIPE_PATH = "/tmp/cmd_vel_pipe";
    inline const char* DEVICE_NAME = "/dev/ttyACM0";
    const int BAUD_RATE = 115200;

    struct CmdVelPacket {
        uint8_t header = 0xAA;
        int8_t throttle = 0;
        int8_t steering = 0;
        uint8_t checksum = 0;
    };

    struct DataPacket {
        int8_t throttle;
        int8_t steering;
    };

    void sendVelocityCommand(serialib& ser, DataPacket& data);

}

#endif