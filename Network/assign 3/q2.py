from scapy.all import IP, TCP, sr1, send, conf
import random
import sys

conf.verb = 0

def tcp_sequence_experiment(dst_ip, dst_port):
    print(f"\n[*] Starting TCP Sequence & Acknowledgment Experiment on target {dst_ip}:{dst_port}\n")

    client_isn = random.randint(1000, 50000)
    src_port = random.randint(40000, 60000)

    syn_pkt = IP(dst=dst_ip) / TCP(dport=dst_port, sport=src_port, flags="S", seq=client_isn)
    
    print(f"[*] Transmitting SYN packet with Seq = {client_isn}...")

    syn_ack_reply = sr1(syn_pkt, timeout=2)

    if syn_ack_reply is None:
        print("[-] Error: No response received (Timeout). Is the server running?")
        return

    if not syn_ack_reply.haslayer(TCP) or syn_ack_reply.getlayer(TCP).flags != "SA":
        print("[-] Error: Received packet is not a valid SYN-ACK segment.")
        return

    tcp_layer = syn_ack_reply.getlayer(TCP)

    server_isn = tcp_layer.seq
    syn_ack_ack = tcp_layer.ack

    expected_client_ack = server_isn + 1
    next_seq = client_isn + 1 

    ack_pkt = IP(dst=dst_ip) / TCP(
        dport=dst_port, 
        sport=src_port, 
        flags="A", 
        seq=next_seq, 
        ack=expected_client_ack
    )

    print("[*] Transmitting final ACK segment to complete handshake...")
    send(ack_pkt)

    print("\n" + "="*50)
    print("               EXPERIMENT 2 SUMMARY")
    print("="*50)
    print(f"Client ISN                   = {client_isn}")
    print(f"Server ISN                   = {server_isn}")
    print(f"SYN+ACK acknowledgment       = {syn_ack_ack}")
    print(f"Expected client acknowledgment = {expected_client_ack}")
    print("="*50 + "\n")

if __name__ == "__main__":
    if len(sys.argv) == 3:
        target_ip = sys.argv[1]
        target_port = int(sys.argv[2])
    else:
        target_ip = input("Enter Destination IP Address (e.g., 127.0.0.1): ").strip()
        target_port = int(input("Enter Destination TCP Port (e.g., 20000): ").strip())
    
    tcp_sequence_experiment(target_ip, target_port)