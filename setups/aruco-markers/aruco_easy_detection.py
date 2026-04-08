import cv2
import cv2.aruco as aruco
from picamera2 import Picamera2

CAM_RESOLUTION = (640, 480)
ARUCO_TYPE = aruco.DICT_4X4_1000

def main():    
  # Configure camera
  picam2 = Picamera2()
  config = picam2.create_preview_configuration(main={"size": CAM_RESOLUTION})
  picam2.configure(config)
  picam2.start()
    
  # Configure aruco
  detector = aruco.ArucoDetector(aruco.getPredefinedDictionary(ARUCO_TYPE))

  while True:
    # Show the frame
    frame = picam2.capture_array()
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    # Detect tags
    corners, ids, _ = detector.detectMarkers(frame)
    if len(corners) > 0:
      aruco.drawDetectedMarkers(frame, corners, ids) 

    # Handle key event
    key = cv2.waitKey(20)

    # Exit on Q
    if (key == ord("q")): break

    cv2.imshow("ArUco Easy Detection", frame)

if __name__ == "__main__":
    main()
