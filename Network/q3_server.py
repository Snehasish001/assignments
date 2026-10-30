import socket
from datetime import datetime

def main():
    IP_ADDR = '127.0.0.1'
    TCP_PORT = 30000
    BUFF_SIZE = 1024

    k = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    k.bind((IP_ADDR, TCP_PORT))
    print("Server is bounded successfully.")

    k.listen(1)

    while True:
        print("Server is waiting ...")
        conn, addr = k.accept()

        print(f"Connected to IP : {addr[0]}, Port : {addr[1]}.")

        while True:
            command = conn.recv(BUFF_SIZE)

            if not command:
                break

            command = command.decode()

            match command:
                case 'time':
                    res = datetime.now().strftime("%H:%M:%S")
                case 'date':
                    res = datetime.now().strftime("%Y-%m-%d")
                case 'hostname':
                    res = socket.gethostname()
                case 'quit':
                    conn.sendall(b"Connection terminated.")
                    break
                case _ if command.startswith('echo '):
                    res = command[5:]
                case _:
                    res = "Invalid command."

            print("Command executed successfully.")
            conn.sendall(res.encode())
            print("Output sent successfully.")

        conn.close()


if __name__ == "__main__":
    main()