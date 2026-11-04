from scapy.all import IP, ICMP, sr1, conf
import sys


conf.verb = 0

def icmp_ttl_investigation(dst_ip, max_ttl=30):
    print(f"\n[*] Starting ICMP TTL & Hop-Limit Investigation on target: {dst_ip}\n")
    print("-" * 50)
    print(f"{'TTL':<5} | {'Responding IP':<18} | {'ICMP Type':<10} | {'ICMP Code'}")
    print("-" * 50)


    for ttl in range(1, max_ttl + 1):
        pkt = IP(dst=dst_ip, ttl=ttl) / ICMP()

        reply = sr1(pkt, timeout=2, verbose=0)

        if reply is None:
            print(f"{ttl:<5} | {'* (Timeout / No Response)':<18} | {'-':<10} | {'-'}")
            continue

        responding_ip = reply.src
        icmp_type = reply.getlayer(ICMP).type
        icmp_code = reply.getlayer(ICMP).code

        print(f"{ttl:<5} | {responding_ip:<18} | {icmp_type:<10} | {icmp_code}")

        if icmp_type == 0:
            print("-" * 50)
            print(f"[+] Reached destination {dst_ip} at TTL = {ttl}")
            break
    else:
        print("-" * 50)
        print("[-] Reached maximum TTL limit without hitting destination.")

if __name__ == "__main__":
    if len(sys.argv) == 2:
        target_ip = sys.argv[1]
    else:
        target_ip = input("Enter Destination IP Address (e.g., 8.8.8.8 or 127.0.0.1): ").strip()
    
    icmp_ttl_investigation(target_ip)