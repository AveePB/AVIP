#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include "detector.h"

int main() {
    // Create camera 
    cv::VideoCapture cap = mz::createCSICameraVideoCapture();

    if(!cap.isOpened()) {
        std::cerr << "Error: Could not open pipeline!\n";
        return -1;
    }
    std::cout << "Initialized the csi camera!\n";

    // Create aruco detector and other variables
    cv::aruco::ArucoDetector det =  mz::createArucoDetector();
    std::cout << "Initialized the aruco detector!\n";
    cv::Mat frame;

    // Create named pipe
    mz::clearPipe(mz::PIPE_PATH);
    mkfifo(mz::PIPE_PATH, 0666);
    int fd = open(mz::PIPE_PATH, O_WRONLY);
    uint8_t signal = 0;
    std::cout << "Initialized the pipe!\n";

    while(true) {
        // Read frame
        if (!cap.read(frame)) break;

        if (mz::isPedestrianDetected(frame, det))
            signal = 1;
        else
            signal = 0;
        
        // Send info through pipe
        write(fd, &signal, sizeof(signal));
    }

    cap.release();
    close(fd);
    return 0;
}