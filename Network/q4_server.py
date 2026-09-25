import socket
import subprocess as sp
import multiprocessing as mp


def client_handler(conn, BUFF_SIZE):

    while True:

        command = conn.recv(BUFF_SIZE).decode().strip().lower()

        if not command:
            break

        match command:

            case 'time':
                command = ['date', '+%T']

            case 'date':
                command = ['date', '+%F']

            case 'hostname':
                command = ['hostname']

            case 'quit':
                break

            case _:
                conn.send(b"Invalid command")
                continue

        try:
            res = sp.run(
                command,
                capture_output=True,
                text=True,
                check=True
            )

            conn.send(res.stdout.encode())

            print("Command executed successfully.")
            print("Output sent successfully.")

        except sp.CalledProcessError as e:

            print(
                f"Command execution failed. "
                f"Exit code: {e.returncode}"
            )

            conn.send(
                f"Command failed: {e.stderr}".encode()
            )

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

    server.listen(1)

    while True:

        print("Server is waiting ...")

        conn, addr = server.accept()

        print(f"Connected to {addr}.")

        process = mp.Process(
            target=client_handler,
            args=(conn, BUFF_SIZE)
        )

        process.start()

        conn.close()


if __name__ == "__main__":
    main()