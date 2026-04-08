from picamera2 import Picamera2
import secrets 
import string
import cv2

FOLDER_PATH = "./assets/chessboard-imgs"
CHESSBOARD_SIZE = (5, 8) # INNER corners (your board)
CAM_RESOLUTION = (640, 480)

def generate_random_string(size):
  return ''.join([secrets.choice(string.ascii_letters + string.digits) for _ in range(size)])

def main():
  # Configure camera
  picam2 = Picamera2()
  config = picam2.create_preview_configuration(main={"size": CAM_RESOLUTION})
  picam2.configure(config)
  picam2.start()
    
  # Show the frame
  while True:
    frame = picam2.capture_array()
    gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    # Handle key event
    key = cv2.waitKey(20)

    # Exit on Q
    if (key == ord("q")): break
        
    elif (key == 9 and cv2.findChessboardCornersSB(gray_frame, CHESSBOARD_SIZE)[0]): # Screenshot on TAB
      filename = generate_random_string(12)
      is_saved = cv2.imwrite(f"{FOLDER_PATH}/{filename}.png", gray_frame)
      if is_saved: print(f"Screenshot saved to {filename}.png!")
    
    cv2.imshow("Camera Preview", gray_frame)
    
  picam2.stop()
    
if __name__ == "__main__":
  main()
