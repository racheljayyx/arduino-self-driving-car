import cv2
import numpy as np
import math

def linesDetected(image_path):
    # Declare variables
    theta = 0

    # Load the image
    lineImage = cv2.imread(image_path)

    # Convert the image to grayscale
    lineImageGrey = cv2.cvtColor(lineImage, cv2.COLOR_BGR2GRAY)

    # Apply the Canny algorithm to detect edges
    lineImageEdges = cv2.Canny(lineImageGrey, 20, 110)

    # Detect points that form a line using the Hough Transform
    linesFormed = cv2.HoughLinesP(lineImageEdges, 1, np.pi/180, threshold=10, minLineLength=5, maxLineGap=30)

    # Ensure lines were detected
    if linesFormed is not None:
        # Draw the detected lines on the image
        for x in range(0, len(linesFormed)):
            for x1, y1, x2, y2 in linesFormed[x]:
                cv2.line(lineImage, (x1, y1), (x2, y2), (255, 0, 0), 3)
                theta += math.atan2((y2 - y1), (x2 - x1))
                print(theta)
    else:
        print("No lines were detected.")

    # Display the final image with detected lines
    cv2.imshow("Line Detection", lineImage)

    # Wait for a key press and close the image window
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def main():
    # Path to the image file
    image_path = 'assets/line2.png'

    # Call the function to detect lines
    linesDetected(image_path)

if __name__ == "__main__":
    main()
