import socket
from pathlib import Path

def main():
    IP_ADDR = '127.0.0.1'
    TCP_PORT = 7001
    BUFFER_SIZE = 1024

    k = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    k.bind((IP_ADDR, TCP_PORT))
    print("Server is Bounded successfully.")

    
    k.listen(1)
    print("Server is listening ... ")
    conn, addr = k.accept()
    print("Connection address : ",addr)

    req = conn.recv(BUFFER_SIZE)

    path = Path(f"./send/{req.decode()}")
    if path.is_file():
        with open(path, "rb") as file:
            while True:
                data = file.read(BUFFER_SIZE)
                if not data:
                    break

                conn.sendall(data)
        conn.sendall(b"EOF")
        print("File sent successfully")
    else:
        conn.send(b"404 FILE NOT FOUND.")
        print("FILE NOT FOUND")
    conn.close()
    k.close()



if __name__ == "__main__":
    main()