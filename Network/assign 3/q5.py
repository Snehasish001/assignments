
from scapy.all import sniff, IP, TCP, UDP
from collections import defaultdict
from datetime import datetime
import time


CAPTURE_DURATION = 15 * 60  


flows = defaultdict(lambda: {
    "packets": 0,
    "bytes": 0,
    "first_time": None,
    "last_time": None
})

ip_stats = defaultdict(lambda: {
    "packets": 0,
    "bytes": 0
})



def packet_analysis(pkt):

    if not pkt.haslayer(IP):
        return

    ip = pkt[IP]


    if pkt.haslayer(TCP):
        protocol = "TCP"
        sport = pkt[TCP].sport
        dport = pkt[TCP].dport

    elif pkt.haslayer(UDP):
        protocol = "UDP"
        sport = pkt[UDP].sport
        dport = pkt[UDP].dport

    else:
        return

    src_ip = ip.src
    dst_ip = ip.dst


    flow_key = (
        src_ip,
        sport,
        dst_ip,
        dport,
        protocol
    )

    packet_size = len(pkt)
    timestamp = float(pkt.time)


    flow = flows[flow_key]

    flow["packets"] += 1
    flow["bytes"] += packet_size

    if flow["first_time"] is None:
        flow["first_time"] = timestamp

    flow["last_time"] = timestamp


    ip_stats[src_ip]["packets"] += 1
    ip_stats[src_ip]["bytes"] += packet_size



print("Starting network capture...")
print("Duration: 15 minutes")

start = time.time()

sniff(
    filter="tcp or udp",
    prn=packet_analysis,
    store=False,
    timeout=CAPTURE_DURATION
)

end = time.time()

print("\nCapture completed!")
print("Actual capture time:", round(end - start, 2), "seconds")



print("\n========== NETWORK FLOWS ==========")

for key, data in flows.items():

    duration = data["last_time"] - data["first_time"]

    print("\nFlow:", key)
    print("Packets:", data["packets"])
    print("Bytes:", data["bytes"])
    print("Duration:", round(duration, 6), "seconds")




print("\n========== TOP 10 FLOWS BY BYTES ==========")

top_bytes = sorted(
    flows.items(),
    key=lambda x: x[1]["bytes"],
    reverse=True
)[:10]

for key, data in top_bytes:
    print(key, "Bytes:", data["bytes"])



print("\n========== TOP 10 FLOWS BY PACKETS ==========")

top_packets = sorted(
    flows.items(),
    key=lambda x: x[1]["packets"],
    reverse=True
)[:10]

for key, data in top_packets:
    print(key, "Packets:", data["packets"])


print("\n========== TOP IPs BY PACKETS ==========")

top_ip_packets = sorted(
    ip_stats.items(),
    key=lambda x: x[1]["packets"],
    reverse=True
)

for ip, data in top_ip_packets[:10]:
    print(ip, "Packets:", data["packets"])



print("\n========== TOP IPs BY BYTES ==========")

top_ip_bytes = sorted(
    ip_stats.items(),
    key=lambda x: x[1]["bytes"],
    reverse=True
)

for ip, data in top_ip_bytes[:10]:
    print(ip, "Bytes:", data["bytes"])



print("\n========== SUMMARY ==========")

print("Total flows:", len(flows))

print(
    "Total packets:",
    sum(data["packets"] for data in flows.values())
)

print(
    "Total bytes:",
    sum(data["bytes"] for data in flows.values())
)
