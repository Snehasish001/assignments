import socket
import os

BUF_SIZE = 1024
IP_ADDR = '127.0.0.1'
PORT = 20000

server = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
server.bind((IP_ADDR, PORT))

while True:
    print('UDP server is listening ... ')

    bytesAddressPair = server.recvfrom(BUF_SIZE)

    filename = bytesAddressPair[0].decode()
    client_addr = bytesAddressPair[1]

    print(f'Client IP   : {client_addr}')
    print(f'Client file : {filename}')

    filepath = os.path.join('send', filename)

    if os.path.exists(filepath):

        if os.path.getsize(filepath) > BUF_SIZE:
            server.sendto(
                "ERROR : FILE SIZE IS GREATER THAN BUFFER SIZE".encode(),
                client_addr
            )
            print('File size is greater than buffer size')

        else:
            with open(filepath, 'rb') as file:
                data = file.read(BUF_SIZE)

            server.sendto(data, client_addr)
            print('File sent successfully')

    else:
        server.sendto(
            "ERROR : FILE NOT FOUND".encode(),
            client_addr
        )
        print('File Not Found')