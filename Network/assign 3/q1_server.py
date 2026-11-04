import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(("127.0.0.1", 20000))
server.listen(5)

print("Server listening on 127.0.0.1:20000")

while True:
    conn, addr = server.accept()
    print("Connection from:", addr)
    conn.close()