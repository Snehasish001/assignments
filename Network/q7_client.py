import socket
import os

SERVER_IP = '127.0.0.1'
SERVER_PORT = 20000
BUFF_SIZE = 1024

client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

filename = input('Enter filename: ')

client.sendto(filename.encode(), (SERVER_IP, SERVER_PORT))

filename = os.path.join('recv', filename)

chunks = {}

while True:
    res = client.recvfrom(BUFF_SIZE)

    data = res[0]

    if data == b'END':
        break

    if data.startswith(b'ERROR'):
        print(data.decode())
        client.close()
        exit()

    seq, data = data.split(b':', 1)
    seq = int(seq.decode())

    chunks[seq] = data

with open(filename, 'wb') as file:
    for seq in sorted(chunks):
        file.write(chunks[seq])

print('File Recieved.')
client.close()