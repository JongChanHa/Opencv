import numpy as np
import cv2
import time

# Read from the recorded video file
cap = cv2.VideoCapture("lol.mp4")

# 동영상 파일이 성공적으로 열렸으면 while 문 반복
while(cap.isOpened()):
	# 한 프레임을 읽어옴
    ret, frame = cap.read()

    
    #if ret is False:
     #   ret, frame = cap.read()
      #  print("Can't receive frame (stream end?). Exiting ...")

    if(cap.get(cv2.CAP_PROP_POS_FRAMES) == cap.get(cv2.CAP_PROP_FRAME_COUNT)):
        cap.open('lol.mp4')        

    # Resize image 
    resized = cv2.resize(frame, (640,360))

    # Display
    cv2.imshow("Video Out",resized)

    # Get frame rate 
    #fps = cap.get(cv2.cv.C)

    # 1 ms 동안 대기하며 키 입력을 받고 'q' 입력 시 종료
    key = cv2.waitKey(40)

    # c 누르면 동영상 이미지 저장
    if key & 0xFF == ord('c'):
        cv2.imwrite("output.png", frame)

    if key & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()