import numpy as np
import cv2

# 이미지 파일을 Read
img = cv2.imread("LetsMars.jpg")

# Crop 300x400 from original image from (100, 50)=(x,y)
cropped = img[50:150, 250:370]

# Resize cropped image from 300x400 to 400x200
resized = cv2.resize(cropped, (750,750))

#90 rotation
rotated = cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)

# Display all
cv2.imshow("Original", img)
cv2.imshow("Cropped image", cropped)
cv2.imshow("Resized image", resized)
cv2.imshow("Rotated image", rotated)

cv2.waitKey(0)
cv2.destroyAllWindows()
