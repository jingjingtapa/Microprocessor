import serial #시리얼 모듈 설치/시리얼 통신 설정

board = serial.Serial('COM3',9600)
y = float(arduino.readline().decode()[:-2]) #byte단위로 들어온 데이터를 변환,
                                            #뒤에 항상 /r/n이 붙기 때문에 -2번째까지만 읽기
                                            #float로 정수형 처리
