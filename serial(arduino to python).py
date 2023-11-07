import serial
import time

# 'COM3' 부분에 환경에 맞는 포트 입력
ser = serial.Serial('COM3', 9600)

while True:
    if ser.readable():
        val = ser.readline()
        print(val.decode()[:len(val)-1])  # 넘어온 데이터 중 마지막 개행문자 제외
