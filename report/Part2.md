# Part 2: HTTP & DNS Packet Analysis Report

**Họ và tên:** Nghiêm Đình Thuận  
**Môn học:** Mạng máy tính / Computer Networks  
**Nhiệm vụ:** Part 2 - HTTP & DNS Analysis with Wireshark  

---

## Part C: Detailed Packet Analysis Answers

### A. Name Resolution & Addressing

#### 1. Was a DNS query made before the connection? If so, what name was requested and what IP address(es) did the DNS response return?
* **Có**, client đã gửi một truy vấn DNS (UDP port 53) trước khi thiết lập kết nối TCP.
* **Tên miền yêu cầu (Requested Name):** `www.google.com` (Packet #1).
* **Địa chỉ IP trả về (Returned IPs):** IP chính là `142.251.153.119`, đi kèm các IP dự phòng: `142.251.154.119`, `142.251.155.119`, và `142.251.152.119` (Packet #2).

![DNS Query and Response](dns.png)

#### 2. What is the destination IP address your client actually connected to? What is your own (source) IP address?
* **Destination IP (IP đích của Server Google):** `142.251.153.119`
* **Source IP (IP nguồn của Client):** `192.168.1.181`

---

### B. The TCP Connection

#### 3. Find the three-way handshake. Give the packet numbers of the SYN, SYN-ACK, and ACK packets.
* **SYN (Client -> Server):** Packet #3
* **SYN-ACK (Server -> Client):** Packet #5
* **ACK (Client -> Server):** Packet #6

#### 4. What source (client) TCP port did your program use? Which range does this fall into, and why is it not a fixed number like 80?
* **Source TCP Port:** `52647`
* **Phạm vi dải port:** Dải Port động/tạm thời (**Ephemeral / Dynamic Port Range**: 49152 – 65535).
* **Giải thích:** Các port cố định (như Port 80 cho HTTP) chỉ dùng cho phía Server để lắng nghe kết nối. Phía Client được hệ điều hành cấp phát ngẫu nhiên một port động nhằm đảm bảo không bị trùng lặp khi mở nhiều kết nối mạng đồng thời.

#### 5. Look at the SYN and SYN-ACK packets. What Maximum Segment Size (MSS) and initial Window Size were advertised by each side?
* **Phía Client (Gói SYN #3):**
  * **Initial Window Size:** `65535` bytes
  * **Advertised MSS:** `1460` bytes (theo chuẩn Ethernet MTU 1500 bytes)
* **Phía Server (Gói SYN-ACK #5):**
  * **Initial Window Size:** `65535` bytes
  * **Advertised MSS:** `1420` bytes (do cấu hình đường truyền của Google)

#### 6. Using the timestamps, estimate the round-trip time (RTT): how long between your SYN and the server's SYN-ACK?
* **Timestamp của gói SYN (Packet #3):** `0.029095500` s
* **Timestamp của gói SYN-ACK (Packet #5):** `0.155089900` s
* **Ước tính RTT:** 0.155089900 - 0.029095500 = 0.1259944 s (khoảng 125.99 ms)

---

### C. The HTTP Request

#### 7. What HTTP method and version did your request use? Copy the exact request line.
* **HTTP Method:** `GET`
* **HTTP Version:** `HTTP/1.1`
* **Exact Request Line:** `GET / HTTP/1.1`

#### 8. List every HTTP header your client sent. Why is the Host header required in HTTP/1.1?
* **Các Request Headers đã gửi:**
  ```http
  Host: [www.google.com](https://www.google.com)
  User-Agent: SocketLab/1.0
  Connection: close