import socket

def main():
    TCP_PORT = 30000
    IP_ADDR = '127.0.0.1'
    BUF_SIZE = 1024

    client = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    client.connect((IP_ADDR, TCP_PORT))
    print("Client has sent connection request.")

    flag = True
    while flag:
        command = input("Enter :\n1. time\n2. date\n3. hostname\n4. quit\n >>> ")
        command = command.lower()

        if command == 'quit':
            flag = False

        client.send(command.encode())
        print("Command sent succefully.")

        res = client.recv(BUF_SIZE)
        print(res.decode())
    
    client.close()
    print("Client closed.")

if __name__ == "__main__":
    main()
