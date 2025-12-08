import cv2, imutils, socket

cap = cv2.VideoCapture(0)

s_sender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
HOST_IP = "localhost"
PORT_SEND = 5436
#s_sender.bind((HOST_IP,PORT_SEND))

while True:
    _, frame = cap.read()
    frame = imutils.resize(frame, width=400) # arbitrary for right now
    encode, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY,80])
    s_sender.sendto(bytes(buffer), (HOST_IP, PORT_SEND))
    #cv2.imshow("test display", frame)
