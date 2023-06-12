# 141337 - Lập trình mạng - IT4060

Buổi 7

1. Sử dụng kỹ thuật đa tiến trình, lập trình ứng dụng fileserver đơn giản như sau:
   - Khi client mới được chấp nhận, server sẽ gửi danh sách cácfile cho client. Các file này trong thư mục được thiết lập trên server.
   - Dòng đầu danh sách là chuỗi “OKN\r\n” nếu có N file trong thư mục. Các tên file phân cách nhau bởi ký tự \r\n, kết thúc danh sách bởi ký tự \r\n\r\n
   - Nếu không có file nào trong thư mục thì server gửi chuỗi “ERROR No files to download\r\n” rồi đóng kết nối.
   - Client gửi tên file để tải về, server kiểm tra nếu file tồn tại thì gửi chuỗi “OK N\r\n” trong đó N là kích thước file, sau đó là nội dung file cho client và đóng kết nối, nếu file không tồn tại thì gửi thông báo lỗi và yêu cầu client gửi lại tên file.
2. Sử dụng kỹ thuật đa luồng, lập trình ứng dụng chat nhóm 2 người như sau:
   - Mỗi client khi kết nối đến server sẽ được lưu vào hàng đợi, nếu số lượng client trong hàng đợi là 2 thì 2 client này sẽ được ghép cặp với nhau.
   - Khi 2 client đã được ghép cặp thì tin nhắn gửi từ client này sẽ được chuyển tiếp sang client kia và ngược lại.
   - Nếu 1 trong 2 client ngắt kết nối thì client còn lại cũng được ngắt kết nối.
