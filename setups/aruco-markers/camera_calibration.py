import cv2
import glob
import numpy as np

IMG_FOLDER = "./assets/chessboard-imgs"
OUTPUT_CAM_MAT_FILENAME = "./assets/cam-matrix.npz"
OUTPUT_DIST_COEFF_FILENAME = "./assets/dist-coeff.npz"

CHESSBOARD_SIZE = (5, 8) # INNER corners (your board)
CAMERA_RESOLUTION = (640, 480)

def main():
    # Find images
    filenames = glob.glob(f"{IMG_FOLDER}/*.png")
    print(f"We have {len(filenames)} images")

    # Real world coordinates of chessboard corners.
    objp = np.zeros((CHESSBOARD_SIZE[0]*CHESSBOARD_SIZE[1], 3), np.float32)
    objp[:, :2] = np.mgrid[0:CHESSBOARD_SIZE[0], 0:CHESSBOARD_SIZE[1]].T.reshape(-1, 2)

    objpoints = [] # 3D points in real world space
    imgpoints = [] # 2D points in image plane

    # Take half of images
    for i in range(0, len(filenames), 1):
        # Find chessboard corners
        img = cv2.imread(filenames[i], cv2.IMREAD_GRAYSCALE)
        ret, corners = cv2.findChessboardCornersSB(img, CHESSBOARD_SIZE)

        # Add corners to lists
        if ret:
            # Refine corner positions
            criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
            corners2 = cv2.cornerSubPix(img, corners, (11, 11), (-1, -1), criteria)
            objpoints.append(objp)
            imgpoints.append(corners2)

    # Calibrate camera
    ret, mat, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, CAMERA_RESOLUTION, None, None)

    print("Reprojection error:", ret)
    print("Camera matrix:", mat)
    print("Distortion coefficients:", dist)

    # Save data
    mat = np.array(mat)
    np.savez(OUTPUT_CAM_MAT_FILENAME, mat)
    np.savez(OUTPUT_DIST_COEFF_FILENAME, dist)

if __name__ == "__main__":
    main()
