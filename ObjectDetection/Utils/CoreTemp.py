import os
import time
import pygame
pygame.mixer.init()

def measure_temp():
        temp = os.popen("vcgencmd measure_temp").readline()
        temp = temp.replace("temp=","")
        temp = temp[:-3]
        return temp

def starttemperaturecheck(out=False):
    alreadyplayed = False
    while True:
        temp = measure_temp()
        if out:
            print(temp)
        
        if float(temp) > 70.0 and not alreadyplayed:
            pygame.mixer.music.load("/home/pi/ObjectDetection/Utils/TemperatureWarning.mp3")
            pygame.mixer.music.play()
            alreadyplayed = True
        
        time.sleep(1)

if __name__ == "__main__":
    starttemperaturecheck(True)
