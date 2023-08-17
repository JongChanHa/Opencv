import numpy as np
import cv2
import sys
# Read from the first camera device
cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)

#최대해상도 지원 300k
w = 320#1280#1920
h = 240#720#1080
fps=30
cap.set(cv2.CAP_PROP_FRAME_WIDTH, w)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, h)


#set video property
video_name = 'out2.mp4'

fourcc = cv2.VideoWriter_fourcc(*'mp4v') #fourcc

out = cv2.VideoWriter(video_name, fourcc, fps, (w,h))

# 성공적으로 video device 가 열렸으면 while 문 반복
while(cap.isOpened()):
    # 한 프레임을 읽어옴
    ret, frame = cap.read()
    if ret is False:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    # Display
    cv2.imshow("Camera",frame)

    # 웹캠으로 찰영한 영상을 저장하기
    # cv2.VideoWriter 객체 생성, 기존에 받아온 속성값 입력
    out.write(frame)




    # 1 ms 동안 대기하며 키 입력을 받고 'q' 입력 시 종료
    key = cv2.waitKey(1)
    if key & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
