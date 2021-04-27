from ObjectDetectorModule import *
from pygame import mixer
import sys
import time
import threading
import RPi.GPIO as GPIO

# Setup LEDs
pin1 = 26
pin2 = 16
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(pin1, GPIO.OUT)
GPIO.setup(pin2, GPIO.OUT)

#Initialize Camera -> 640x480p to have decent fps on RPi
cap = cv2.VideoCapture(0)
cap.set(3, 640)
cap.set(4, 480)

# intialize audio mixer and load audio
mixer.init()
channel = mixer.Channel(5)
sound = mixer.Sound("CarAlarm.wav")


def leds(limit):
    print("Thread called!")
    for i in range(limit):
        GPIO.output(pin1, GPIO.HIGH)
        GPIO.output(pin2, GPIO.LOW)
        time.sleep(0.2)
        GPIO.output(pin1, GPIO.LOW)
        GPIO.output(pin2, GPIO.HIGH)
        time.sleep(0.2)

    #Set LEDs to ON
    GPIO.output(pin1, GPIO.HIGH)
    GPIO.output(pin2, GPIO.HIGH)


if '-per' in sys.argv:
    per = float(sys.argv[sys.argv.index("-per")+1])
    print("Set minimum percent of recognition to:" + str(per))
else:
    per = 0.45
    print("Proceding with default value for minimum percent of recognition:" + str(per))

if '-nms' in sys.argv:
    nms = float(sys.argv[sys.argv.index("-nms")+1])
    print("Set nms Threshold to:" + str(nms))
else:
    nms = 0.2
    print("Proceding with default nms value:" + str(nms))

if '-nogui' in sys.argv:
    while True:
        success, img = cap.read()
        result, objectInfo = getObjects(img, per, nms, True, ['person', 'cat', 'dog', 'bird'])
        for found in objectInfo:
            if found[1] == 'person' or found[1] == 'cat' or found[1] == 'dog' or found[1] == 'bird':
                if not channel.get_busy():
                    channel.play(sound)
                    t = threading.Thread(target=leds, args=(20,))
                    t.start()
        cv2.waitKey(1)

else:
    while True:
        success, img = cap.read()
        result, objectInfo = getObjects(img, per, nms, True, ['person', 'cat', 'dog', 'bird'])
        for found in objectInfo:
            if found[1] == 'person' or found[1] == 'cat' or found[1] == 'dog' or found[1] == 'bird':
                if not channel.get_busy():
                    channel.play(sound)
                    t = threading.Thread(target=leds, args=(20,))
                    t.start()
        cv2.imshow("Output", img)
        cv2.waitKey(1)
