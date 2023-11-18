from scipy.spatial import distance as dist
from imutils.video import FileVideoStream
from imutils.video import VideoStream
from imutils import face_utils
import numpy as np
import argparse
import imutils
import time
import dlib
import cv2
import math
import serial


# EAR 함수 정의
def eye_aspect_ratio(eye):
    A = dist.euclidean(eye [1], eye[5])
    B = dist.euclidean(eye [2], eye[4])
    C = dist.euclidean(eye[0], eye[3])
    ear = (A+B) / (2.0 * C)
    return ear

# 눈 감음 기준값 설정
EYE_AR_THRESH = 0.2
EYE_AR_CONSEC_FRAMES = 30
COUNTER = 0
TOTAL = 0

# 안면 인식 기본 설정
print("[INFO] loading facial landmark predictor...")
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")


(lStart, lEnd) = face_utils.FACIAL_LANDMARKS_IDXS["left_eye"]
(rStart, rEnd) = face_utils.FACIAL_LANDMARKS_IDXS["right_eye"]

# 카메라 불러오기
print("[INFO] starting video stream thread...")
vs = VideoStream(src=1).start()
time.sleep(1.0)

ser = serial.Serial('COM5', 9600, timeout=1)
time.sleep(2)

while True:
    get_data = ser.readline()
    if get_data:
        get_data = get_data.decode()
        num = int(get_data)
        print(num)
        if num:
            frame = vs.read()
            frame = imutils.resize(frame, width=450)
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            rects = detector(gray, 0)
            for rect in rects:
                shape = predictor(gray, rect)
                shape = face_utils.shape_to_np(shape)
                leftEye = shape[lStart:lEnd]
                rightEye = shape[rStart:rEnd]
                leftEAR = eye_aspect_ratio(leftEye)
                rightEAR = eye_aspect_ratio(rightEye)
                ear = (leftEAR + rightEAR) / 2.0
                leftEyeHull = cv2.convexHull(leftEye)
                rightEyeHull = cv2.convexHull(rightEye)
                cv2.drawContours (frame, [leftEyeHull], -1, (0, 255, 0), 1) 
                cv2.drawContours (frame, [rightEyeHull], -1, (0, 255, 0), 1)


                if ear < EYE_AR_THRESH:
                    COUNTER += 1
                    if COUNTER >= EYE_AR_CONSEC_FRAMES:
                        TOTAL += 10
                        COUNTER=0
                else:
                    COUNTER = 0

                cv2.putText(frame, "Blinks: {}".format(TOTAL), (10, 30),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                cv2.putText(frame, "EAR: {:.2f}".format(ear), (300, 30),
                            cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)



                        

            cv2.imshow("Frame", frame)
            key = cv2.waitKey(1) & 0xFF

            if key == ord("q"):
                break

cv2.destroyAllWindows()
vs.stop()
