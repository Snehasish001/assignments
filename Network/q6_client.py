
import socket

SERVER_IP = '127.0.0.1'
SERVER_PORT = 20000
BUFF_SIZE = 2873

client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

filename = input('Enter filename: ')

client.sendto(filename.encode(), (SERVER_IP, SERVER_PORT))

res = client.recvfrom(BUFF_SIZE)

data = res[0]

if data.decode(errors='ignore').startswith('ERROR'):
    print(f'Response : {data.decode()}')
else:
    print('File content:')
    print(data.decode())

client.close()
