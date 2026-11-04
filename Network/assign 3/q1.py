from scapy.all import IP, TCP, ICMP, sr1, conf
import sys

conf.verb = 0

def analyze_tcp_flags(dst_ip, dst_port):
    test_cases = [
        {"name": "1. SYN", "flags": "S"},
        {"name": "2. ACK", "flags": "A"},
        {"name": "3. FIN+ACK", "flags": "FA"},
        {"name": "4. RST", "flags": "R"},
        {"name": "5. SYN+FIN", "flags": "SF"}
    ]

    print(f"\n[*] Starting TCP Flag Analysis on target {dst_ip}:{dst_port}\n")
    print("-" * 65)
    print(f"{'Test Case':<15} | {'Transmitted Flags':<18} | {'Response / Result'}")
    print("-" * 65)

    for test in test_cases:
        case_name = test["name"]
        flags = test["flags"]

        pkt = IP(dst=dst_ip) / TCP(dport=dst_port, sport=45000, flags=flags, seq=1000)

        reply = sr1(pkt, timeout=2, verbose=0)

        result_str = ""

        if reply is None:
            result_str = "Filtered / No Response (Timeout)"
        elif reply.haslayer(ICMP):
            icmp_layer = reply.getlayer(ICMP)
            result_str = f"ICMP Response -> Type: {icmp_layer.type}, Code: {icmp_layer.code}"
        elif reply.haslayer(TCP):
            tcp_reply = reply.getlayer(TCP)
            resp_flags = tcp_reply.sprintf("%TCP.flags%")
            result_str = f"TCP Response Flags: {resp_flags}"
        else:
            result_str = f"Received packet with layer: {reply.summary()}"

        print(f"{case_name:<15} | {flags:<18} | {result_str}")

    print("-" * 65)

if __name__ == "__main__":
    if len(sys.argv) == 3:
        target_ip = sys.argv[1]
        target_port = int(sys.argv[2])
    else:
        target_ip = input("Enter Destination IP Address: ").strip()
        target_port = int(input("Enter Destination TCP Port: ").strip())
    
    analyze_tcp_flags(target_ip, target_port)