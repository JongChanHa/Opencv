import numpy as np
import cv2
# Read from the first camera device
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

topLeft = (50, 50)
bold = 0

# Callback function for the trackbar
def on_bold_trackbar(value):
    #print("Trackbar value:", value)
    global bold
    bold = value

cv2.namedWindow("Camera")
cv2.createTrackbar("bold", "Camera", bold, 100, on_bold_trackbar)

# 성공적으로 video device 가 열렸으면 while 문 반복
while(cap.isOpened()):
    # 한 프레임을 읽어옴
    ret, frame = cap.read()
    if ret is False:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    # Text 
    cv2.putText(frame, "TEXT",
        topLeft, cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 255, 255), 1 + bold/5)


    # Display
    cv2.imshow("Camera",frame)

    # 1 ms 동안 대기하며 키 입력을 받고 'q' 입력 시 종료
    key = cv2.waitKey(1)
    if key & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
