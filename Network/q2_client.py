import socket

def main():
    TCP_PORT = 7001
    IP_ADDR = '127.0.0.1'
    BUFFER_SIZE = 1024

    k = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    k.connect((IP_ADDR, TCP_PORT))

    req = input("Enter file name : ")
    k.send(req.encode())
    
    path = f"./recv/{req}"
    with open(path, "wb") as file:
        while True:
            data = k.recv(BUFFER_SIZE)

            if data == b"EOF":
                break

            file.write(data)
    print("File received successfully.")
    k.close()



if __name__ == "__main__":
    main()