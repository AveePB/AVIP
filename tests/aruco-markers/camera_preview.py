import secrets 
import string
import cv2

FOLDER_PATH = "./assets/chessboard-laptop-images"

def generate_random_string(size):
    return ''.join([secrets.choice(string.ascii_letters + string.digits) for _ in range(size)])

def main():
    # Configure opencv
    camera = cv2.VideoCapture(0)
    cv2.namedWindow("Camera Preview")

    if camera.isOpened():
        print("Camera is opened!")
        is_read, frame = camera.read()
    else:
        is_read = False
    
    # Show the frame
    while is_read:
        cv2.imshow("Camera Preview", frame)
        is_read, frame = camera.read()

        # Handle key event
        key = cv2.waitKey(20)
        if (key == 27): # Exit on ESC
            break
        elif (key == 9): # Screenshot on TAB
            filename = generate_random_string(12)
            is_saved = cv2.imwrite(f"{FOLDER_PATH}/{filename}.png", frame)
            if is_saved: print(f"Screenshot saved to {filename}.png!")
    
    cv2.destroyAllWindows()
    camera.release()

if __name__ == "__main__":
    main()