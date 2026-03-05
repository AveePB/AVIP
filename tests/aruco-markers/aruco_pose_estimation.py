import cv2
import cv2.aruco as aruco
import numpy as np

CAM_MAT_FILENAME = "./assets/calibration-data/laptop-cam-mat.npz"
DIST_COEFF_FILENAME = "./assets/calibration-data/laptop-dist-coeff.npz"

ARUCO_TYPE = aruco.DICT_4X4_1000
MARKER_SIZE = 0.018

def main():
    # Configure opencv
    camera = cv2.VideoCapture(0)
    cv2.namedWindow("ArUco Easy Detection")

    if camera.isOpened():
        print("Camera is opened!")
        is_read, frame = camera.read()
    else:
        is_read = False
    
    # Configure aruco
    detector = aruco.ArucoDetector(aruco.getPredefinedDictionary(ARUCO_TYPE))
    K = np.load(CAM_MAT_FILENAME)['arr_0']; print("K:", K)
    D = np.load(DIST_COEFF_FILENAME)['arr_0']; print("D:", D)

    while is_read:
        # Show the frame
        cv2.imshow("ArUco Easy Detection", frame)
        is_read, frame = camera.read()

        # Detect tags
        corners, ids, _ = detector.detectMarkers(frame)

        if len(corners) > 0:
            aruco.drawDetectedMarkers(frame, corners, ids)

            # Estimate positon of each marker
            rvecs, tvecs, _ = aruco.estimatePoseSingleMarkers(corners, MARKER_SIZE, K, D)
            for rvec, tvec in zip(rvecs, tvecs):
                point = cv2.drawFrameAxes(frame, K, D, rvec, tvec, MARKER_SIZE, 3)
                dist = np.sqrt(tvec[0][2] ** 2 + tvec[0][0] ** 2 + tvec[0][1] ** 2)
                print(dist)

        # Handle key event
        key = cv2.waitKey(20)
        if (key == 27): # Exit on ESC
            break

    cv2.destroyAllWindows()
    camera.release()

if __name__ == "__main__":
    main()