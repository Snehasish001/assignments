import socket


def main():

    TCP_PORT = 30000
    IP_ADDR = '127.0.0.1'
    BUF_SIZE = 1024

    client = socket.socket(
        family=socket.AF_INET,
        type=socket.SOCK_STREAM
    )

    client.connect((IP_ADDR, TCP_PORT))

    print("Client has sent connection request.")

    while True:

        command = input(
            "Enter:\n"
            "1. time\n"
            "2. date\n"
            "3. hostname\n"
            "4. quit\n"
            ">>> "
        ).lower().strip()

        client.send(command.encode())

        print("Command sent successfully.")

        if command == 'quit':
            break

        res = client.recv(BUF_SIZE)

        print("Server:", res.decode())

    client.close()

    print("Client closed.")


if __name__ == "__main__":
    main()