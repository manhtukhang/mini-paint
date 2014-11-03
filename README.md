Bare Bones Compiler
===================
Trình biên dịch cho ngôn ngữ lập trình Bare Bones

## Giới thiệu

### 1. Tên gọi

Bare Bones (programing language) dịch ra Tiếng Việt có nghĩa là  ngôn ngữ lập trình cơ bản nhất, đơn giản nhất;  
Vì tên dịch ra rất dài, khó nhớ nên từ đây trở về sau, trong tài liệu này sẽ quy ước tên gọi là **ngôn ngữ lập trình BareBones** hay đơn giản là **BareBones**

### 2. Đặc điểm

#### - Các câu lệnh

BareBones hết sức đơn giản, chỉ có 5 câu lệnh và 1 cấu trúc lặp `while ... do`

Câu lệnh                    | Ý nghĩa
:---------------------------|:-------
init <*biến*> = <*giá trị*>;| Khai báo biến và khởi tạo giá trị cho biến
clear <*biến*>;             | Xóa giá trị của biến (đưa về `0`) (`X := 0`)
incr <*biến*>;              | Tăng giá trị của lên 1 đơn vị (`X := X + 1`)
decr <*biến*>;              | Giảm giá trị của xuống 1 đơn vị, (`X := X - 1`)
copy <*biến*> to <*biến*>;  | Sao chép giá trị của 1 biến cho 1 biến khác (`Y := X`)
while <*biến*> not 0 do;<br> &nbsp;&nbsp;&nbsp;&nbsp;<*các câu lệnh*>;<br> end; | Nếu giá trị của `biến` chưa bằng `0` thì các câu lệnh trong vòng lặp `while` vẫn tiếp tục.

#### - Quy ước đặt tên
* Từ khóa (tên dành riêng): các từ trong danh sách sau là tên dành riêng được BareBones sử dụng, không được dùng để đặt tên cho biến
```
    clear  
    copy  
    decr  
    do  
    end  
    incr  
    init  
    not  
    to  
    while  
```
    Các từ khóa không phân biệt hoa thường

* Tên biến: Ngoài các từ khóa trên không được dùng,tên biến được đặt theo quy tắc sau:
    * Phải bắt đầu bằng 1 chữ cái trong bảng chữ cái alphabet (`a-z`)
    * Tên biến có thể chứa số (`0-9`) và dấu gạch dưới `_`
    * Không phân biệt hoa-thường (Các tên `a1b, A1B, a1B, A1b` là như nhau)

#### - Phạm vi giá trị của biến
Biến có thể nhận các giá trị là số nguyên không âm, giới hạn tối đa là `2^64-1` (Tương đương với kiểu `uintmax_t` của ngôn ngữ *C*)

#### - Nhập/xuất
BareBones không sử dụng nhập xuất từ bên ngoài chương trình. Giá trị được nhập lúc khởi tạo biến, khi chương trình kết thúc, các giá trị sẽ được xuất ra *thiết bị xuất chuẩn* (thường là màn hình)

#### - Dấu ngăn cách lệnh và chú thích
* Chú thích: sử dụng dấu `#`đầu chú thích, chú thích được tính từ sau dấu `#` đến cuối dòng, không có chú thích nhiều dòng, muốn làm vậy phải sử dụng `#` cho mỗi dòng cần chú thích
* Ngăn cách lệnh: sử dụng dấu `;` ở cuối mỗi lệnh. **Đặc biệt**, sau từ khóa `do` cũng phải có dấu `;`



