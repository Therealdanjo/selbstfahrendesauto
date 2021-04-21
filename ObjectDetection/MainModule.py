from ObjectDetectorModule import *
from pygame import mixer

cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
#cap.set(10,70)

#intialize audio mixer and load audio
mixer.init()
channel = mixer.Channel(5)
sound = mixer.Sound("CarAlarm.wav")

while True:
    success,img = cap.read()
    result, objectInfo = getObjects(img, 0.45, 0.2, True, ['person', 'cat', 'dog', 'bird'])
    for found in objectInfo:
        if found[1] == 'person' or found[1] == 'cat' or found[1] == 'dog' or found[1] == 'bird':
            if not channel.get_busy():
                channel.play(sound)

    cv2.imshow("Output", img)
    cv2.waitKey(1)
