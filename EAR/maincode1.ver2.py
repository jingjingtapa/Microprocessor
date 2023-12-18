# 눈을 30프레임 동안 감고 있으면 TOTAL +10
# TOTAL이 10 이상일 때(눈을 감고 있다고 판단된 때,
# 센서로 측정한 값을 logistic 회귀 방법으로 졸음 판단  
# 졸음이라 판단되면 OUTPUT 아두이노에 1을 송신
# 졸음이 아니라 판단되면 OUTPUT 아두이노에 0을 송신하고, TOTAL 값을 0으로 리셋

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
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression


# EAR 함수 정의
def eye_aspect_ratio(eye):
    A = dist.euclidean(eye [1], eye[5])
    B = dist.euclidean(eye [2], eye[4])
    C = dist.euclidean(eye[0], eye[3])
    ear = (A+B) / (2.0 * C)
    return ear

# 눈 감음 기준값 설정
EYE_AR_THRESH = 0.18
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
vs = VideoStream(src=0).start()
time.sleep(1.0)

# 카메라로 받은 영상에서 EAR 값 게산 함수

def VSread(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)
    op = len(rects)
    if op: #눈이 감지 될때
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
    else: #눈이 감지 안될때
        ear = -1
    return ear

# 시리얼 통신 기본 설정
inputCOM = 'COM7'
inputbaudrate = 115200

outputCOM = 'COM8'
outputbaudrate = 115200

ard = serial.Serial(outputCOM, outputbaudrate)
ser = serial.Serial(inputCOM, inputbaudrate, timeout=1)
time.sleep(2.0)


# logistic 회귀 방법

drivers = pd.read_csv('./drivertrain.csv')

def decision(Distance, Force, drivers):
    features = drivers[['Distance', 'Force']]
    sleep = drivers['Sleep']  # Sleep 열 선택
    train_features, test_features, train_labels, test_labels = train_test_split(features, sleep, test_size=0.2, random_state=42)
    train_features = train_features.values
    test_features = test_features.values    
    scaler = StandardScaler()   
    train_features = scaler.fit_transform(train_features)   
    test_features = scaler.transform(test_features)
    model = LogisticRegression()   
    model.fit(train_features, train_labels)
    sample_driver = np.array([[Distance, Force]])  # 샘플 데이터를 2차원 배열로 변환  
    sample_driver = scaler.transform(sample_driver)
    predict = model.predict(sample_driver)  
    return predict[0]  # 결과값 반환

# 실행 코드

while True:
    get_data = ser.readline()
    if get_data:
        get_data = get_data.decode()
        list = get_data.split('/')
        distance = int(list[0])
        force = int(list[1])
        CO2 = int(list[2])
        brightness = int(list[3])
        print('distnace:',distance,'force:',force,'CO2:',CO2,'밝기:',brightness)
        if (brightness < 1000):
            frame = vs.read()
            frame = imutils.resize(frame, width=450)
            ear = VSread(frame)
            if ear > 0 and ear < EYE_AR_THRESH:
                COUNTER += 1
                if COUNTER >= EYE_AR_CONSEC_FRAMES:
                    TOTAL += 10
                    COUNTER=0
            else:
                COUNTER = 0
                TOTAL = 0



            cv2.putText(frame, "Blinks: {}".format(TOTAL), (10, 30),
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            cv2.putText(frame, "EAR: {:.2f}".format(ear), (300, 30),
                       cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
            cv2.imshow("Frame", frame)
            key = cv2.waitKey(1) & 0xFF
            


            if TOTAL >= 10:
                result = decision(distance, force, drivers)
                if result == 1:
                    ard.write(b'1')
                    print('sleep warning')
                    
                else:
                    TOTAL = 0
                    ard.write(b'0')
                    print('not sleep')

            else:
                ard.write(b'o')
            
            if key == ord("q"):
                break

cv2.destroyAllWindows()
vs.stop()



        