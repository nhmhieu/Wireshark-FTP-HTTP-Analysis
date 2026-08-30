

1. Was a DNS query made before the connection? If so, what name was requested and what IP address(es) did the DNS response return?

Có. Client đã thực hiện truy vấn DNS cho `www.google.com` trước khi thiết lập kết nối TCP. DNS response trả về nhiều địa chỉ IPv4, bao gồm `142.251.153.119`, `142.251.154.119`, `142.251.155.119` và `142.251.152.119`.

* **Packet number nếu có:** Packet #1 (DNS Query), Packet #2 và Packet #4 (DNS Responses).
* **Screenshot evidence nếu cần:** `dns_query_response.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Dòng được khoanh đỏ hiển thị các DNS packet. Oval màu vàng khoanh vùng `Name: www.google.com` và các trường `Address`, bao gồm `142.251.153.119`.
---

2. What is the destination IP address your client actually connected to? What is your own (source) IP address?

Địa chỉ IP đích (destination IP) mà client kết nối đến là `142.251.153.119`. Địa chỉ IP nguồn (source IP) của client là `192.168.1.181`.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `HTTP_GET_Request.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Hình oval đỏ (khoanh vùng danh sách gói tin) cột Source hiển thị `192.168.1.181` và Destination hiển thị `142.251.153.119`.

---

7. What HTTP method and version did your request use? Copy the exact request line.

Phương thức HTTP được sử dụng là `GET` và phiên bản HTTP là `HTTP/1.1`. Request line chính xác là: `GET / HTTP/1.1\r\n`.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `HTTP_GET_Request.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Hình oval màu vàng ở khung chi tiết gói tin, dòng được bôi nền đỏ ghi `Request Method: GET`.

---

8. List every HTTP header your client sent. Why is the Host header required in HTTP/1.1?

Các HTTP headers mà client đã gửi bao gồm:
Host: www.google.com
User-Agent: SocketLab/1.0
Connection: close


*Giải thích:* Header `Host` là bắt buộc trong HTTP/1.1 vì nó cho phép một địa chỉ IP vật lý lưu trữ nhiều tên miền (Virtual Hosting). Server cần header này để biết chính xác client đang muốn truy cập vào tên miền nào để trả về đúng trang web đó.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `HTTP_GET_Request.png` (hiển thị phần Request) hoặc `HTTP_Response.png` (phần chữ màu đỏ đại diện cho client request).
* **Highlight/circle đúng field đang dùng để trả lời:** Nằm trong hình oval màu vàng phần Hypertext Transfer Protocol (`HTTP_GET_Request.png`).

---

9. Roughly how many bytes was your request? Was it carried in one TCP segment or more?

Dữ liệu của HTTP request có kích thước khoảng 86 bytes và được truyền đi trong một TCP segment duy nhất (gói tin số 7). Toàn bộ khung Ethernet (Ethernet frame) bắt được có kích thước là 140 bytes.

---

10. What HTTP status code and reason phrase did the server return? What does that code mean?

 Mã trạng thái (status code) trả về là `200` và reason phrase là `OK`. Mã này biểu thị rằng yêu cầu (request) đã thành công, server đã xử lý và đang trả về dữ liệu được yêu cầu.
* **Packet number nếu có:** N/A (được quan sát trực tiếp trong TCP Stream)
* **Screenshot evidence nếu cần:** `HTTP_Response.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Phần gạch dưới màu đỏ dòng `HTTP/1.1 200 OK`.

---

11. If you received a redirect, what URL is given in the Location header? Where is the server trying to send you?

Không có sự chuyển hướng (redirect) nào xảy ra. Do máy chủ phản hồi thẳng với mã `200 OK`, gói tin không chứa header `Location`.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `HTTP_Response.png`
* **Highlight/circle đúng field đang dùng để trả lời:** N/A (quan sát dòng gạch đỏ `200 OK`).

---

12. Identify three response headers (e.g. Server, Content-Type, Content-Length or Transfer-Encoding, Date) and explain what each one tells the client.

Dựa vào TCP Stream, ta có thể xác định 3 response headers sau:
1. `Content-Type: text/html; charset=ISO-8859-1`: Báo cho client biết nội dung trả về là mã HTML, sử dụng bảng mã ISO-8859-1.
2. `Server: gws`: Cho biết tên phần mềm của máy chủ web (Google Web Server).
3. `Date: Sat, 15 Aug 2026 07:04:22 GMT`: Thời điểm cụ thể (theo múi giờ GMT) mà máy chủ tạo ra phản hồi này.


* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `HTTP_Response.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Dữ liệu text ngay bên dưới dòng `HTTP/1.1 200 OK` đã được gạch dưới đỏ.

---

13. Did the response include a message body? If so, what was in it (roughly)?

Có, phản hồi có bao gồm message body. Dựa vào header Content-Type: text/html, nội dung của body chứa mã nguồn HTML của trang chủ Google.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `HTTP_Response.png`
Highlight/circle đúng field đang dùng để trả lời: Phần dữ liệu sau các HTTP response headers trong TCP Stream là message body; header Content-Type: text/html cũng cho biết nội dung phản hồi là HTML.

---

**Câu hỏi / Số câu:** 14. How does the response signal where the body ends: a Content-Length header, Transfer-Encoding: chunked, or by closing the connection? If it is chunked, note that there is no Content-Length — explain how the client knows the body is finished instead.

Response không sử dụng header Content-Length và cũng không sử dụng Transfer-Encoding: chunked. Phần message body được xác định kết thúc bằng cách đóng kết nối TCP. Điều này phù hợp với header Connection: close. Sau dữ liệu HTTP cuối cùng ở Packet 75, kết nối TCP được đóng thông qua quá trình trao đổi các gói FIN/ACK.

---

**Câu hỏi / Số câu:** 23. Wireshark could read your entire HTTP request and response as plain text. What does this tell you about the security of port-80 HTTP, and how does HTTPS (port 443) change what an eavesdropper can see?

* **Câu trả lời dựa trên capture:** Điều này cho thấy giao thức HTTP (cổng 80) hoàn toàn không có tính bảo mật; toàn bộ dữ liệu truyền đi (bao gồm cả các thông tin nhạy cảm) dưới dạng văn bản thô (plain text) nên bất kì ai bắt được gói tin cũng có thể đọc hiểu nội dung. Trong khi đó, HTTPS (cổng 443) dùng TLS/SSL để mã hoá kết nối. Kẻ nghe lén bắt được gói tin HTTPS sẽ chỉ thấy chuỗi dữ liệu mã hoá mà không đọc được request hay response thực tế.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `HTTP_Response.png`
* **Highlight/circle đúng field đang dùng để trả lời:** Toàn bộ nội dung của TCP Stream trong ảnh có thể đọc được một cách dễ dàng dưới định dạng ASCII.

---

**Câu hỏi / Số câu:** 24. In one short paragraph, describe the complete lifecycle of your request in order: DNS → handshake → request → response → close.

Vòng đời của kết nối bắt đầu bằng truy vấn DNS để phân giải tên miền www.google.com thành địa chỉ IP 142.251.153.119. Tiếp theo, client và server thiết lập kết nối thông qua quá trình bắt tay 3 bước TCP (handshake). Sau khi kết nối hoàn tất, client gửi HTTP GET request và máy chủ xử lý, phản hồi lại dữ liệu bằng một HTTP 200 OK response. Cuối cùng, kết nối TCP được đóng lại (close) hoàn toàn thông qua quá trình trao đổi các gói tin TCP FIN/ACK giữa hai bên.