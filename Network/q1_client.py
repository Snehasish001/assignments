import socket

IP_ADDRESS = '127.0.0.1'
TCP_PORT = 5000
BUFFER_SIZE = 1024

flag = True
while flag:
    k = socket.socket(family=socket.AF_INET, type= socket.SOCK_STREAM)
    k.connect((IP_ADDRESS, TCP_PORT))
    print("\n\nClient has sent connection request.")

    msg = input("MESSAGE : ")
    k.send(msg.encode())
    print("Messege sent successfully.")

    data = k.recv(BUFFER_SIZE)
    print("RECEIVED : ",data.decode())

    k.close()

    flag = False if input("Enter x for exit : ").lower() == 'x' else True


