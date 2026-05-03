#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <csignal>
#include <errno.h>
#include "serialib.h"
#include "rcar.h"

int main() {
    // Open serial port
    serialib my_serial;
    if (my_serial.openDevice(mz::DEVICE_NAME, mz::BAUD_RATE) != 1) {
        std::cerr << "Error: Unable to open port " << mz::DEVICE_NAME << "!\n";
        return -1;
    }
    std::cout << "Port opened successfully!\n";

    // Access command velocity pipe
    int fd = -1;
    mz::DataPacket data;

    while (true) {
        // Try to open pipe
        if (fd == -1) {
            fd = open(mz::CMD_VEL_PIPE_PATH, O_RDONLY);
            
            // Pipe doesn't exist yet
            if (fd == 1) continue;
        }

        // Read data from FIFO
        ssize_t bytesRead = read(fd, &data, sizeof(mz::DataPacket));
        if (bytesRead == sizeof(mz::DataPacket)) { // New command
            std::cout << "Received new command!\n";
            mz::sendVelocityCommand(my_serial, data);
        }
        else if (bytesRead == 0) { // No bytes read
            close(fd);
            fd = -1;
        }
    }

    // Close serial
    mz::DataPacket stop_packet = {0, 0};
    mz::sendVelocityCommand(my_serial, stop_packet);
    my_serial.closeDevice();
    std::cout << "Maverick driver exited!\n";

    return 0;
}
