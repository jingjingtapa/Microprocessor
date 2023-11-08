import serial #시리얼 모듈 설치/시리얼 통신 설정
import time #time 모듈 설치 / 시간 설정

# 'COM3' 부분에 환경에 맞는 포트 입력
py_serial = serial.Serial('COM3', 9600) #보드의 포트 번호와 보드레이트 설정

##while True:
##    if ser.readable():
##        val = ser.readline()
##        print(val.decode()[:len(val)-1])  # 넘어온 데이터 중 마지막 개행문자 제외

while True: #참이면 실행, 에디터 자체 초기값이 참이므로 계속 실행.
      
    commend = input('아두이노에게 내릴 명령:') #input을 commend 변수에 저장
    
    py_serial.write(commend.encode()) #.encode():문자열 인코딩 함수, 미지정 시 UTF-8 사용
                                      # write() : 시리얼 통신을 통해 아두이노로 전송  
    
    time.sleep(0.1)  #0.1초 동안 지연
    
    if py_serial.readable():
        
        # 들어온 값이 있으면 값을 한 줄 읽음 (BYTE 단위로 받은 상태)
        # BYTE 단위로 받은 response 모습 : b'\xec\x97\x86\xec\x9d\x8c\r\n'
        response = py_serial.readline()
        
        # 디코딩 후, 출력 (가장 끝의 \n을 없애주기위해 슬라이싱 사용)
        print(response[:len(response)-1].decode())
