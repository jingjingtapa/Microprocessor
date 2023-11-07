import serial
import time

# 'COM3' 부분에 환경에 맞는 포트 입력
ser = serial.Serial('COM3', 9600)

while True:
    if ser.readable():
        val = input()

        if val == '1':
            val = val.encode('utf-8')
            ser.write(val)
            print("LED TURNED ON")
            time.sleep(0.5)

        elif val == '0':
            val = val.encode('utf-8')
            ser.write(val)
            print("LED TURNED OFF")
            time.sleep(0.5)
