import serial
import cv2
import time

board = serial.Serial('COM3', 115200)

while True:
    
    dis = board.readline().decode()    
    force = board.readline().decode()
    
    try:

        print(float(dis))
        
        print(float(force))
        
        if float(dis) >= 150:

            print(float(dis), 'awake')

            print(float(force), 'awake')

        
        else:

            print(float(dis))
        
    except ValueError:
        
        print("Invalid data")
    
##    key = cv2.waitKey(1) & 0xFF
##
##    if key == ord('q'):
##        break

board.close()

cv2.destroyAllWindows()
