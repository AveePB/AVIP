from picamera2 import Picamera2
import cv2
import cv2.aruco as aruco
import numpy as np

CAM_MAT_FILENAME = "./assets/cam-matrix.npz"
DIST_COEFF_FILENAME = "./assets/dist-coeff.npz"

ARUCO_TYPE = aruco.DICT_4X4_1000
MARKER_SIZE = 0.018 # 18mm
CAM_RESOLUTION = (640, 480)

def main():
  # Configure camera
  picam2 = Picamera2()
  config = picam2.create_preview_configuration(main={"size": CAM_RESOLUTION})
  picam2.configure(config)
  picam2.start()
    
  # Configure aruco
  detector = aruco.ArucoDetector(aruco.getPredefinedDictionary(ARUCO_TYPE))
  K = np.load(CAM_MAT_FILENAME)['arr_0']; print("K:", K)
  D = np.load(DIST_COEFF_FILENAME)['arr_0']; print("D:", D)

  while True:
    # Show the frame
    frame = picam2.capture_array()
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
    
    # Detect tags
    corners, ids, _ = detector.detectMarkers(frame)

    if len(corners) > 0:
      #aruco.drawDetectedMarkers(frame, corners, ids)

      # Estimate position of each marker
      rvecs, tvecs, _ = aruco.estimatePoseSingleMarkers(corners, MARKER_SIZE, K, D)
      for rvec, tvec, aruco_id in zip(rvecs, tvecs, ids):
        #cv2.drawFrameAxes(frame, K, D, rvec, tvec, MARKER_SIZE, 3)
        dist = np.sqrt(tvec[0][2] ** 2 + tvec[0][0] ** 2 + tvec[0][1] ** 2)
        print("Marker distance", dist, aruco_id)

      # Handle key event
      key = cv2.waitKey(20)
      
      # Exit on ESC
      if (key == ord("q")): break
    
    # Show frame
    #cv2.imshow("ArUco Easy Detection", frame)

  picam2.stop()

if __name__ == "__main__":
  main()
