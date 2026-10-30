import socket
from datetime import datetime
import multiprocessing as mp


def client_handler(conn, BUFF_SIZE):

    while True:

        command = conn.recv(BUFF_SIZE).decode().strip().lower()

        if not command:
            break

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
                conn.sendall(b"Invalid command")
                continue

        conn.sendall(res.encode())

        print("Command executed successfully.")
        print("Output sent successfully.")

    conn.close()
    print("Connection closed.")


def main():

    IP_ADDR = '127.0.0.1'
    TCP_PORT = 30000
    BUFF_SIZE = 1024

    server = socket.socket(
        family=socket.AF_INET,
        type=socket.SOCK_STREAM
    )

    server.bind((IP_ADDR, TCP_PORT))

    print("Server is bound successfully.")

    server.listen(10)

    while True:

        print("Server is waiting ...")

        conn, addr = server.accept()

        print(
            f"Connected to IP : {addr[0]}, "
            f"Port : {addr[1]}."
        )

        process = mp.Process(
            target=client_handler,
            args=(conn, BUFF_SIZE)
        )

        process.start()

        conn.close()


if __name__ == "__main__":
    main()