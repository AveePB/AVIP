import cv2
import cv2.aruco as aruco
import matplotlib.pyplot as plt
import random

FOLDER_ARUCO_PATH = "./assets/markers"
ARUCO_TYPE = aruco.DICT_4X4_1000
MARKER_ID = random.randint(0, 999)
MARKER_SIZE = 200 # mm

def main():
  # Generate aruco tag
  aruco_dict = aruco.getPredefinedDictionary(ARUCO_TYPE)
  aruco_img = aruco.generateImageMarker(aruco_dict, MARKER_ID, MARKER_SIZE)

  # Show image
  cv2.imwrite(f"{FOLDER_ARUCO_PATH}/{MARKER_ID}.png", aruco_img)
  plt.imshow(aruco_img, cmap='gray', interpolation='nearest')
  plt.axis('off')  
  plt.title(f'ArUco Marker {MARKER_ID}')
  plt.show()

if __name__ == "__main__":
  main()
