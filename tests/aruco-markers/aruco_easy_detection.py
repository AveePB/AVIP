import cv2
import cv2.aruco as aruco

ARUCO_TYPE = aruco.DICT_4X4_1000

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

    while is_read:
        # Show the frame
        cv2.imshow("ArUco Easy Detection", frame)
        is_read, frame = camera.read()

        # Detect tags
        corners, ids, _ = detector.detectMarkers(frame)
        if len(corners) > 0:
            aruco.drawDetectedMarkers(frame, corners, ids) 

        # Handle key event
        key = cv2.waitKey(20)
        if (key == 27): # Exit on ESC
            break

    cv2.destroyAllWindows()
    camera.release()

if __name__ == "__main__":
    main()