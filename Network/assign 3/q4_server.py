import socket

# Bind to localhost and UDP port 53 (requires root/sudo for ports under 1024)
HOST = '127.0.0.1'
PORT = 53

# Create a datagram socket (UDP)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_socket.bind((HOST, PORT))

print(f"[*] UDP Server listening on {HOST}:{PORT}...")

while True:
    # Receive data from client
    data, addr = server_socket.recvfrom(1024)
    print(f"[+] Received message from {addr}: {data.decode('utf-8', errors='ignore')}")
    
    # Optionally, send a response back to the client
    response = b"Hello from UDP Server!"
    server_socket.sendto(response, addr)
    print(f"[+] Sent response back to {addr}\n")