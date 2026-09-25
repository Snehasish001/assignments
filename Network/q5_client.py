import socket

SERVER_IP = '127.0.0.1'
SERVER_PORT = 20000
BUFF_SIZE = 1024

client = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

client.sendto("Hello UDP server".encode(), (SERVER_IP, SERVER_PORT))

res = client.recvfrom(BUFF_SIZE)
print(f"Response : {res[0].decode()}")