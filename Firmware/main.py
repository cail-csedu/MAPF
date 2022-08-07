# -*- coding: utf-8 -*-
import cv2


def readQRcode():
    cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    # initialize the cv2 QRCode detector
    detector = cv2.QRCodeDetector()
    
    while True:
        _, img = cap.read()
        data, bbox, _ = detector.detectAndDecode(img)
        # check if there is a QRCode in the image
        if data:
            a=data
            print(a)
            break
        
        cv2.imshow("QRCODEscanner", img)
        if cv2.waitKey(1) == ord("q"):
            break
    
    
    cap.release()
    cv2.destroyAllWindows()
    
    return a