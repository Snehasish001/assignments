import socket
import os

SERVER_IP = '127.0.0.1'
SERVER_PORT = 20000
BUFF_SIZE = 1024

client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

filename = input('Enter filename: ')

client.sendto(filename.encode(), (SERVER_IP, SERVER_PORT))

filename = os.path.join('recv', filename)

with open(filename, 'wb+') as file:
    while True:
        res = client.recvfrom(BUFF_SIZE)

        data = res[0]

        if not data.decode(errors='ignore').startswith('END') :
            file.write(data)
        else:
            break

print('File Recieved.')
client.close()
