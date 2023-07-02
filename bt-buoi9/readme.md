# 141337 - Lập trình mạng - IT4060

Buổi 9


1. Lập trình thực hiện ứng dụng HTTP server gồm các tính năng sau:
    + Khi trình duyệt yêu cầu địa chỉ thư mục gốc (chỉ nhập tên miền và cổng ở thanh địa chỉ), trả lại kết quả cho trình duyệt một trang web có nội dung gồm các tập tin và thư mục con của thư mục hiện tại. Tên thư mục in đậm, tên file in nghiêng. Mỗi tên thư mục hoặc tập tin là một hyperlink đến thư mục hoặc tập tin đó.
    + Nếu người dùng nhấn vào thư mục con thì server trả về nội dung của thư mục con đó.
    + Nếu người dùng nhấn vào tập tin thì server trả về nội dung của tập tin. Các tập tin cần xử lý gồm tệp văn bản (có phần mở rộng là TXT, C, CPP), tệp ảnh (phần mở rộng là JPG, PNG), tệp âm thanh (phần mở rộng là MP3).