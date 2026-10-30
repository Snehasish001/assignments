import socket

def total_vowels_const(data: str) -> list[int]:
    count = 0
    data = "".join(c for c in data if c.isalpha() and c.isascii())
    vowels = ('a', 'e', 'i', 'o', 'u')
    for ch in data:
        if ch.lower() in vowels:
            count += 1
    
    return [count, len(data) - count]

def count_digit(data: str) -> int:
    count = 0
    for c in data:
        if c.isdigit() and c.isascii():
            count += 1
    return count

def data_process(data: str) -> dict:
    res = dict()
    count = total_vowels_const(data)
    res.update({'len' : len(data), 'vowels' : count[0], 'consonants' : count[1], 'digit' : count_digit(data)})
    
    return res


def main():
    TCP_PORT = 5000
    IP_ADDRESS = '127.0.0.1'
    BUFFER_SIZE = 1024

    k = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
    print("Server has created socket.")

    k.bind((IP_ADDRESS, TCP_PORT))
    print("Server has bounded successfully.")

    k.listen(1)

    while True:
        print("\n\nServer is waiting for client connection ...")
        conn, addr = k.accept()

        print("Connection Address is : ", addr)

        data = conn.recv(BUFFER_SIZE)
        res = data_process(data.decode())

        res = str(res).encode()

        conn.sendall(res)
        conn.close()

if __name__ == '__main__':
    main()