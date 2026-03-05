import cv2
import glob

# INNER corners (your board)
CHESSBOARD_SIZE = (5, 8)
IMG_FOLDER = "./assets/chessboard-laptop-images"

def main():
    # Find images
    filenames = glob.glob(f"{IMG_FOLDER}/*.png")
    print(f"We have {len(filenames)} images")

    # Process each image
    for filename in filenames:
        img = cv2.imread(filename)

        if img is None:
            print("Failed to load image:", filename)
            continue

        # Find and draw corners
        gray_img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        ret, corners = cv2.findChessboardCornersSB(gray_img, CHESSBOARD_SIZE)

        print(f"Corners deteced at {filename}: {ret}")
        if ret: cv2.drawChessboardCorners(img, CHESSBOARD_SIZE, corners, ret)

        # Show result
        cv2.imshow("Detection", img)
        key = cv2.waitKey(20)  # show each image for 0.5s

        # Exit on ESC
        if key == 27: break

    print("Number of processed images:", len(filenames))
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()