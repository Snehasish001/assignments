import socket

BUF_SIZE = 1024
IP_ADDR = '127.0.0.1'
PORT = 20000

server_table = {
    'server1': '192.168.1.10',
    'server2': '192.168.1.20',
    'server3': '192.168.1.30',
    'server4': '192.168.1.40'
}

server = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
server.bind((IP_ADDR, PORT))

while True:
    print('UDP Name Server is listening ... ')

    bytesAddressPair = server.recvfrom(BUF_SIZE)

    hostname = bytesAddressPair[0].decode()
    client_addr = bytesAddressPair[1]

    print(f'Client IP : {client_addr}')
    print(f'Hostname  : {hostname}')

    if hostname in server_table:
        ip_address = server_table[hostname]

        server.sendto(
            ip_address.encode(),
            client_addr
        )

        print(f'IP Address sent : {ip_address}')

    else:
        server.sendto(
            'NOT FOUND'.encode(),
            client_addr
        )

        print('Host not found')