from ObjectDetectorModule import *

cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
#cap.set(10,70)
while True:
    success,img = cap.read()
    result, objectInfo = getObjects(img, 0.45, 0.5, True, ['person', 'cat', 'dog', 'bird'])
    # print(objectInfo)
    cv2.imshow("Output",img)
    cv2.waitKey(1)
