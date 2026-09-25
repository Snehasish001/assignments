import socket
import subprocess

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

    data = (subprocess.run(['date'], capture_output=True, text=True)).stdout
    server.sendto(data.encode(), bytesAddressPair[1])
    print('Message sent successfully')

