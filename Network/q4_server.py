import socket
import subprocess as sp
import multiprocessing as mp

def client_handler(conn, BUFF_SIZE):
    while True:
        command = conn.recv(BUFF_SIZE)
        command = command.decode()
        match command:
            case 'time':
                command = ['date', "+'%F'"]
            case 'date':
                command = ['date', "+'%F'"]
            case 'hostname':
                command = ['hostname']
            case 'quit':
                break
        try:
            res = sp.run(command, capture_output=True, text=True, check=True)
            res = res.stdout
            print("Command executed successfully.")
            conn.send(str(res).encode())
            print("Output sent succefully.")
        except sp.CalledProcessError as e:
            print(F"Command execution faild. Exit code : {e.returncode}")
            print(F"Error message : {e.stderr}")
        conn.close()

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

        print(F"Connected to {addr}.")

        client = mp.Process(target=client_handler, args=(conn, BUFF_SIZE))
        client.start()

        conn.close()

    k.close()


if __name__ == "__main__":
    main()

        


