Mini Paint
==========

**Biên dịch thử để kiểm tra lỗi:**  
 
Nhánh|Trạng thái
:--:|:--:
_master_|[![_Trạng thái_](https://travis-ci.org/manhtuvjp/mini-paint.svg?branch=master)](https://travis-ci.org/manhtuvjp/mini-paint)  
_test_|[![_Trạng thái_](https://travis-ci.org/manhtuvjp/mini-paint.svg?branch=test)](https://travis-ci.org/manhtuvjp/mini-paint)  

_Dự án được biên dịch tự động mỗi khi có thay đổi để biết thay đổi nào là đúng, biên dịch sẽ không bị lỗi_  
_Sử dụng công cụ biên dịch tự động Travis-CI_

# Mục lục:

<!-- MarkdownTOC depth=3 -->

- [Hướng dẫn biên dịch](#hướng-dẫn-biên-dịch)
    - [Linux](#linux)
    - [Windows](#windows)
- [Tải về](#tải-về)
- [Tác giả](#tác-giả)
- [Báo lỗi và đóng góp tính năng](#báo-lỗi-và-đóng-góp-tính-năng)

<!-- /MarkdownTOC -->

# Hướng dẫn biên dịch

**Thành phần phụ thuộc**

 - *Thư viện Qt*
 - *Trình biên dịch và liên kết C++*

## Linux

### Thư viện Qt:
+ Tải về: [Qt5.3.0.tar.xz](https://db.tt/56yg44N7)

+ Cài đặt:  

-Giải nén vào thư mục nào đó, nên là `/opt/Qt5.3.0`  
-Thêm biến môi trường cho thư viện Qt vừa giải nén:  
-Chạy lệnh:

    $ echo 'export PATH=/opt/Qt5.3.0/gcc_64/bin:$PATH' >> ~/.profile
    $ export PATH=/opt/Qt5.3.0/gcc_64/bin:$PATH

-Đăng xuất và đăng nhập lại

**Lưu ý:** *Đường dẫn trên có thể thay đổi, tùy thuộc vào nơi đặt thư mục chứa thư viện Qt*

### Trình biên dịch GCC: *sử dụng `g++` phiên bản > 4.6*  
Trên các hệ điều hành họ Debian, để cài đặt, chạy lệnh:   

    $ sudo apt-get install g++ make  

### Biên dịch:
Chạy các lệnh sau để biên dịch:

    $ cd <thư mục chứa source code>
    $ cd plugins/ && qmake && make
    $ cd ../ && qmake && make

*Sau khi biên dịch thành công có thể copy 2 tệp `minipaint-v1.0` và `extrafilters.so` vào cùng 1 thư mục để chạy*

## Windows
### Tải về và cài đặt QtCreator
Người dùng Windows có thể tải QtCreator cho Windowstại đây để biên dịch chương trình:
[QtCreator download](http://qt-project.org/downloads)

Tuy nhiên dung lượng tải về lớn và cài đặt khá mất thời gian nên nhóm phát triển đã biên dịch sẵn và kèm theo thư viện thực thi cho chương trình. Xem mục [Tải về](#tải-về) sau

# Tải về
_Chú ý đến trạng thái biên dịch, nếu thành công thì có thể an tâm tải về_  

+ Linux [![Build Status](https://drone.io/github.com/manhtuvjp/mini-paint/status.png)](https://drone.io/github.com/manhtuvjp/mini-paint/latest)
 - Thư viện thực thi Qt5.3: [Qt5.3.0.tar.xz](https://db.tt/56yg44N7)
 - Chương trình: [MiniPaint_v0.1.0.Linux.zip](https://drone.io/github.com/manhtuvjp/mini-paint/files/minipaint_v0.1.0_Linux.zip)

+ Windows [![Build Status](https://travis-ci.org/manhtuvjp/mxe-paint.svg?branch=master)](https://travis-ci.org/manhtuvjp/mxe-paint)
 - Chương trình (đã có sẵn thư viện): [MiniPaint_v0.1.0_Windows.zip](https://db.tt/CHDB4wY8)

# Tác giả
- Khang Mạnh Tử [@MT](manhtuvjp@gmail.com)
- Võ Hoài Phong [@phongchicken](hoaiphong95@gmail.com)

# Báo lỗi và đóng góp tính năng
Vui lòng góp ý cho nhóm phát triển [tại đây](https://github.com/manhtuvjp/mini-paint/issues?milestone=&sort=created&direction=desc&state=open)
