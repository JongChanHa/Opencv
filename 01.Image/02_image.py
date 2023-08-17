import numpy as np
import cv2

# 이미지 파일을 Read 하고 Color space 정보 출력
color = cv2.imread("strawberry.jpg", cv2.IMREAD_COLOR)
#color = cv2.imread("strawberry_dark.jpg", cv2.IMREAD_COLOR)
print(color.shape)
height,width,channels = color.shape
cv2.imshow("Original Image",color)

# Color channel 을 B,G,R 로 분할하여 출력
b,g,r = cv2.split(color)
rgb_split = np.concatenate((b,g,r),axis=1)
cv2.imshow("BGR Channels",rgb_split)



# 색공간을 BGR 에서 HSV 로 변환
hsv = cv2.cvtColor(color, cv2.COLOR_BGR2HSV)

#bgr to rgb
im_rgb = cv2.cvtColor(hsv, cv2.COLOR_BGR2RGB)
cv2.imshow("RGB Channels",im_rgb)

#grey
im_grey=cv2.cvtColor(im_rgb, cv2.COLOR_BGR2GRAY)
cv2.imshow("grey Channels", im_grey)

# Channel 을 H,S,V 로 분할하여 출력
h,s,v = cv2.split(hsv)
hsv_split = np.concatenate((h,s,v),axis=1)
cv2.imshow("Split HSV",hsv_split)

cv2.waitKey(0)
cv2.destroyAllWindows()