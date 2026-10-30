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

    if os.path.isfile(filepath):
        with open(filepath, 'rb') as file:
            seq = 0

            while True:
                data = file.read(BUF_SIZE - 20)

                if not data:
                    break

                packet = str(seq).encode() + b':' + data
                server.sendto(packet, client_addr)

                seq += 1

        server.sendto(b'END', client_addr)
        print('File sent successfully')

    else:
        server.sendto(
            b"ERROR : FILE NOT FOUND",
            client_addr
        )
        print('File Not Found')