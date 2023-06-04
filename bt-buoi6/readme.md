# 141337 - Lập trình mạng - IT4060

Buổi 6

1. Bài 1:
   Lập trình lại ứng dụng telnet_server (slide 174) sử dụng kỹ thuật multiprocessing.

2. Bài 2:
   Lập trình lại ứng dụng http_server (slide 154) sử dụng kỹ thuật preforking.

3. Bài 3:
   Lập trình ứng dụng time_server thực hiện chức năng sau:

- Chấp nhận nhiều kết nối từ các client sử dụng kỹ thuật multiprocessing.
- Client gửi lệnh GET_TIME [format] để nhận thời gian từ server.
- format là định dạng thời gian server cần trả về client. Các format cần hỗ trợ gồm:

* dd/mm/yyyy – vd: 30/01/2023
* dd/mm/yy – vd: 30/01/23
* mm/dd/yyyy – vd: 01/30/2023
* mm/dd/yy – vd: 01/30/23

- Cần kiểm tra tính đúng đắn của lệnh client gửi lên server.
