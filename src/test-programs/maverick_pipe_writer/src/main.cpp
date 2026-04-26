#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <cstdint>
#include <thread>
#include <chrono>

inline const char* CMD_VEL_PIPE_PATH = "/tmp/cmd_vel_pipe";
const int8_t THROTTLE = 0;
const int DELAY_MS = 10;

struct DataPacket {
    int8_t throttle;
    int8_t steering;
};

void clearPipe(const char* pipePath) {
    // Pipe doesn't exist
    int fd = open(pipePath, O_RDONLY | O_NONBLOCK);
    if (fd == -1) return;

    // Clear the pipe
    uint8_t buffer[64];
    while (true) {
        ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead > 0) continue; // Data found and consumed
        else if (bytesRead == -1 && errno == EAGAIN) break; // Pipe is empty
        else break; // Pipe closed or pipe error
    }
    close(fd);
}

int main() {
    // Create named pipe
    clearPipe(CMD_VEL_PIPE_PATH);
    mkfifo(CMD_VEL_PIPE_PATH, 0666);
    int fd = open(CMD_VEL_PIPE_PATH, O_WRONLY);
    DataPacket data;
    std::cout << "Initialized the pipe!\n";

    // Update car state
    for (int8_t s = -100; s <= 100; s++) {
        data.steering = s;
        data.throttle = THROTTLE;
        write(fd, &data, sizeof(data));
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));
    }

    // Reset position
    data.steering = 0;
    data.throttle = 0;
    write(fd, &data, sizeof(data));
    std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_MS));

    close(fd);
    std::cout << "Test completed!\n";

    return 0;
}
