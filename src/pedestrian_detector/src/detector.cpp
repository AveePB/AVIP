#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "detector.h"

cv::VideoCapture mz::createCSICameraVideoCapture() {
    // Set up camera and GSTREAMER pipeline
    std::string pipeline = "libcamerasrc camera-name=/base/axi/pcie@1000120000/rp1/i2c@80000/imx708@1a ! "
    "video/x-raw,format=YUY2,width=640,height=480,framerate=60/1 ! "
    "videoconvert ! video/x-raw,format=GRAY8 ! appsink drop=true sync=false";
    return cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);
}

cv::aruco::ArucoDetector mz::createArucoDetector() {
    return cv::aruco::ArucoDetector(cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_1000));
}

bool mz::isPedestrianDetected(cv::Mat& frame, cv::aruco::ArucoDetector& det) {
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    std::vector<int> markerIds;

    // No marker detected
    det.detectMarkers(frame, markerCorners, markerIds, rejectedCandidates);
    if (markerIds.size() == 0) return false;

    // Compute distance to pedestrian
    cv::Mat rvec, tvec;
    cv::solvePnP(mz::OBJ_POINTS, markerCorners[0], mz::CAM_MATRIX, mz::DIST_COEFFS, rvec, tvec);
    double dist = cv::norm(tvec);

    return dist < mz::BRAKING_TRIG_DIST;
}

void mz::clearPipe(const char* pipePath) {
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