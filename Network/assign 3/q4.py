from scapy.all import IP, UDP, ICMP, sr1, conf
import sys

conf.verb = 0

def udp_port_analysis(dst_ip, start_port, end_port):
    print(f"\n[*] Starting UDP Response & ICMP Port-Unreachable Analysis on {dst_ip}")
    print(f"[*] Scanning UDP ports from {start_port} to {end_port}\n")
    print("-" * 75)
    print(f"{'Port':<8} | {'Status / Response Type':<35} | {'ICMP Details'}")
    print("-" * 75)

    for port in range(start_port, end_port + 1):
        pkt = IP(dst=dst_ip) / UDP(dport=port, sport=55555) / b"HelloUDP"

        reply = sr1(pkt, timeout=1.5, verbose=0)

        status_str = ""
        icmp_details = "-"

        if reply is None:
            status_str = "No Response (Open / Filtered / Dropped)"
        elif reply.haslayer(ICMP):
            icmp_layer = reply.getlayer(ICMP)
            icmp_type = icmp_layer.type
            icmp_code = icmp_layer.code
            
            if icmp_type == 3 and icmp_code == 3:
                status_str = "ICMP Port Unreachable (Closed)"
            else:
                status_str = f"ICMP Error Received"
            icmp_details = f"Type: {icmp_type}, Code: {icmp_code} (Port {port})"
        elif reply.haslayer(UDP):
            status_str = "UDP Response Received (Open)"
            icmp_details = f"Responding Source Port: {reply.getlayer(UDP).sport}"
        else:
            status_str = f"Other Packet Layer Received"

        print(f"{port:<8} | {status_str:<35} | {icmp_details}")

    print("-" * 75)

if __name__ == "__main__":
    if len(sys.argv) == 4:
        target_ip = sys.argv[1]
        start_p = int(sys.argv[2])
        end_p = int(sys.argv[3])
    else:
        target_ip = input("Enter Destination IP Address (e.g., 127.0.0.1): ").strip()
        start_p = int(input("Enter Start UDP Port: ").strip())
        end_p = int(input("Enter End UDP Port: ").strip())
    
    udp_port_analysis(target_ip, start_p, end_p)