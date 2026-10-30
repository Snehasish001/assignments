import socket
from datetime import datetime

BUF_SIZE = 1024
IP_ADDR = '127.0.0.1'
PORT = 20000

server = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
server.bind((IP_ADDR, PORT))


while True:
    print('UDP server is listening ... ')
    bytesAddressPair = server.recvfrom(BUF_SIZE)

    print(F'Client IP  : {bytesAddressPair[1]}')
    print(F'Client msg : {bytesAddressPair[0].decode()}')

    command = bytesAddressPair[0].decode().upper()

    if command == 'DATE':
        data = datetime.now().strftime("%Y-%m-%d")

    elif command == 'TIME':
        data = datetime.now().strftime("%H:%M:%S")

    elif command == 'DATETIME':
        data = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    else:
        data = "Invalid request. Use DATE, TIME or DATETIME."

    server.sendto(data.encode(), bytesAddressPair[1])
    print('Message sent successfully')