Dựa trên hướng dẫn từ ảnh `image_54f0fd.png`, dưới đây là phần trả lời cho các câu hỏi dựa trên 3 hình ảnh Wireshark bạn đã cung cấp:

**Câu hỏi / Số câu:** 1. Was a DNS query made before the connection? If so, what name was requested and what IP address(es) did the DNS response return?

* **Câu trả lời dựa trên capture:** Có, một truy vấn DNS đã được thực hiện trước khi kết nối. Tên miền được yêu cầu là `[www.google.com](https://www.google.com)`. DNS phản hồi trả về địa chỉ IP `142.251.153.119` (cùng các IP phụ khác).
* **Packet number nếu có:** Packet #1 (Query) và Packet #2 (Response).
* **Screenshot evidence nếu cần:** `image_54f1af.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Dòng màu đỏ bao quanh gói tin 1 & 2. Oval màu vàng khoanh tròn vùng "Name: [www.google.com](https://www.google.com/search?q=https%3A%2F%2Fwww.google.com)" và "Address: 142.251.153.119".

---

**Câu hỏi / Số câu:** 2. What is the destination IP address your client actually connected to? What is your own (source) IP address?

* **Câu trả lời dựa trên capture:** Địa chỉ IP đích (destination IP) mà client kết nối đến là `142.251.153.119`. Địa chỉ IP nguồn (source IP) của client là `192.168.1.181`.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `image_54f173.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Hình oval đỏ (khoanh vùng danh sách gói tin) cột Source hiển thị `192.168.1.181` và Destination hiển thị `142.251.153.119`.

---

**Câu hỏi / Số câu:** 7. What HTTP method and version did your request use? Copy the exact request line.

* **Câu trả lời dựa trên capture:** Phương thức HTTP được sử dụng là `GET` và phiên bản HTTP là `HTTP/1.1`. Request line chính xác là: `GET / HTTP/1.1\r\n`.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `image_54f173.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Hình oval màu vàng ở khung chi tiết gói tin, dòng được bôi nền đỏ ghi `Request Method: GET`.

---

**Câu hỏi / Số câu:** 8. List every HTTP header your client sent. Why is the Host header required in HTTP/1.1?

* **Câu trả lời dựa trên capture:** Các HTTP headers mà client đã gửi bao gồm:
* `Host: [www.google.com](https://www.google.com)\r\n`
* `User-Agent: SocketLab/1.0\r\n`
* `Connection: close\r\n`


*Giải thích:* Header `Host` là bắt buộc trong HTTP/1.1 vì nó cho phép một địa chỉ IP vật lý lưu trữ nhiều tên miền (Virtual Hosting). Server cần header này để biết chính xác client đang muốn truy cập vào tên miền nào để trả về đúng trang web đó.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `image_54f173.jpg` (hiển thị phần Request) hoặc `image_54f157.jpg` (phần chữ màu đỏ đại diện cho client request).
* **Highlight/circle đúng field đang dùng để trả lời:** Nằm trong hình oval màu vàng phần Hypertext Transfer Protocol (`image_54f173.jpg`).

---

**Câu hỏi / Số câu:** 9. Roughly how many bytes was your request? Was it carried in one TCP segment or more?

* **Câu trả lời dựa trên capture:** Kích thước của toàn bộ gói tin request là 140 bytes (hoặc 86 bytes dữ liệu HTTP thuần). Request này nhỏ nên được truyền toàn bộ trong 1 TCP segment duy nhất.
* **Packet number nếu có:** Packet #7
* **Screenshot evidence nếu cần:** `image_54f173.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Dòng oval đỏ, cột Length ghi rõ giá trị `140`.

---

**Câu hỏi / Số câu:** 10. What HTTP status code and reason phrase did the server return? What does that code mean?

* **Câu trả lời dựa trên capture:** Mã trạng thái (status code) trả về là `200` và reason phrase là `OK`. Mã này biểu thị rằng yêu cầu (request) đã thành công, server đã xử lý và đang trả về dữ liệu được yêu cầu.
* **Packet number nếu có:** N/A (được quan sát trực tiếp trong TCP Stream)
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Phần gạch dưới màu đỏ dòng `HTTP/1.1 200 OK`.

---

**Câu hỏi / Số câu:** 11. If you received a redirect, what URL is given in the Location header? Where is the server trying to send you?

* **Câu trả lời dựa trên capture:** Không có sự chuyển hướng (redirect) nào xảy ra. Do máy chủ phản hồi thẳng với mã `200 OK`, gói tin không chứa header `Location`.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** N/A (quan sát dòng gạch đỏ `200 OK`).

---

**Câu hỏi / Số câu:** 12. Identify three response headers (e.g. Server, Content-Type, Content-Length or Transfer-Encoding, Date) and explain what each one tells the client.

* **Câu trả lời dựa trên capture:** Dựa vào TCP Stream, ta có thể xác định 3 response headers sau:
1. `Content-Type: text/html; charset=ISO-8859-1`: Báo cho client biết nội dung trả về là mã HTML, sử dụng bảng mã ISO-8859-1.
2. `Server: gws`: Cho biết tên phần mềm của máy chủ web (Google Web Server).
3. `Date: Sat, 15 Aug 2026 07:04:22 GMT`: Thời điểm cụ thể (theo múi giờ GMT) mà máy chủ tạo ra phản hồi này.


* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Dữ liệu text ngay bên dưới dòng `HTTP/1.1 200 OK` đã được gạch dưới đỏ.

---

**Câu hỏi / Số câu:** 13. Did the response include a message body? If so, what was in it (roughly)?

* **Câu trả lời dựa trên capture:** Có, phản hồi bao gồm message body. Dựa vào header Content-Type, nội dung của body chứa mã nguồn HTML của trang chủ website được yêu cầu (Google). Kích thước toàn bộ luồng hội thoại lên tới 84 kB.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Ở góc dưới bên trái có ghi dung lượng `Entire conversation (84 kB)`.

---

**Câu hỏi / Số câu:** 14. How does the response signal where the body ends: a Content-Length header, Transfer-Encoding: chunked, or by closing the connection? If it is chunked, note that there is no Content-Length — explain how the client knows the body is finished instead.

* **Câu trả lời dựa trên capture:** Máy chủ báo hiệu kết thúc body bằng cách chủ động ngắt kết nối (closing the connection). Không có header `Content-Length` hoặc `Transfer-Encoding: chunked` nào xuất hiện trong phản hồi, thay vào đó là header `Connection: close`.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Dòng `Connection: close` hiển thị ở cuối phần header phản hồi của máy chủ.

---

**Câu hỏi / Số câu:** 23. Wireshark could read your entire HTTP request and response as plain text. What does this tell you about the security of port-80 HTTP, and how does HTTPS (port 443) change what an eavesdropper can see?

* **Câu trả lời dựa trên capture:** Điều này cho thấy giao thức HTTP (cổng 80) hoàn toàn không có tính bảo mật; toàn bộ dữ liệu truyền đi (bao gồm cả các thông tin nhạy cảm) dưới dạng văn bản thô (plain text) nên bất kì ai bắt được gói tin cũng có thể đọc hiểu nội dung. Trong khi đó, HTTPS (cổng 443) dùng TLS/SSL để mã hoá kết nối. Kẻ nghe lén bắt được gói tin HTTPS sẽ chỉ thấy chuỗi dữ liệu mã hoá mà không đọc được request hay response thực tế.
* **Packet number nếu có:** N/A
* **Screenshot evidence nếu cần:** `image_54f157.jpg`
* **Highlight/circle đúng field đang dùng để trả lời:** Toàn bộ nội dung của TCP Stream trong ảnh có thể đọc được một cách dễ dàng dưới định dạng ASCII.

---

**Câu hỏi / Số câu:** 24. In one short paragraph, describe the complete lifecycle of your request in order: DNS → handshake → request → response → close.

* **Câu trả lời dựa trên capture:** Vòng đời của kết nối bắt đầu bằng truy vấn **DNS** khi client gửi gói tin để phân giải tên miền `[www.google.com](https://www.google.com)` và nhận về địa chỉ IP `142.251.153.119`. Tiếp theo, giữa client và IP đích thiết lập kết nối TCP tin cậy thông qua quá trình **handshake** (bắt tay 3 bước). Ngay sau khi thiết lập, client lập tức gửi HTTP GET **request** qua kết nối này. Máy chủ nhận yêu cầu, xử lý và trả về đoạn dữ liệu HTML thông qua HTTP 200 OK **response**. Cuối cùng, kết nối TCP được đóng lại (**close**) từ phía server như chỉ định tại header `Connection: close`.
* **Packet number nếu có:** Từ Packet #1 đến đoạn kết thúc stream.
* **Screenshot evidence nếu cần:** Tóm lược trên cả 3 file `image_54f1af.jpg`, `image_54f173.jpg`, và `image_54f157.jpg`.
* **Highlight/circle đúng field đang dùng để trả lời:** Tổng hợp dựa vào tất cả các vùng khoanh tròn, hình oval và vệt đỏ trên các ảnh chứng minh.