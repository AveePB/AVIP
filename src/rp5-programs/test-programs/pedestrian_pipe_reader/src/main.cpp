#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <csignal>
#include <errno.h>

inline const char* PIPE_PATH = "/tmp/pedestrian_pipe";    

int main() {
    std::signal(SIGPIPE, SIG_IGN);
    uint8_t pedestrian_detected = 0;
    int fd = -1;

    while (true) {
        if (fd == -1) {
            fd = open(PIPE_PATH, O_RDONLY);
            if (fd == -1) continue;
        }

        ssize_t bytesRead = read(fd, &pedestrian_detected, sizeof(uint8_t));
        if (bytesRead == sizeof(uint8_t)) {
            std::cout << "Message received: " << (int)pedestrian_detected << '\n';
        }
        else if (bytesRead == 0) {
            close(fd);
            fd = -1;
        }
    }

    return 0;
}
