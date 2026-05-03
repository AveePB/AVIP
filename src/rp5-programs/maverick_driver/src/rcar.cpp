#include "rcar.h"

void mz::sendVelocityCommand(serialib& ser, DataPacket& data) {
    // Create packet
    mz::CmdVelPacket p;
    p.throttle = data.throttle;
    p.steering = data.steering;
    p.checksum = p.header ^ (uint8_t)p.steering ^ (uint8_t)p.throttle;

    // Send packet
    uint8_t buff[4] = {p.header, (uint8_t)p.steering, (uint8_t)p.throttle, p.checksum};
    ser.writeBytes(buff, 4);
}
