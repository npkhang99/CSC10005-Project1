# CSC10005-Project1

CSC10005 - Computer Architecture and Assembly Language Project #1

## Thông tin tổng quát

### Thành viên nhóm:

- Nguyễn Phúc Khang - 1712224
- Nguyễn Quý Toàn - 1712823
- Nguyễn Lê Sang - 1712236

### Danh sách tính năng

- Số nguyên lớn:
  Kiểu dữ liệu số nguyên lớn QInt có độ lớn 16 byte với các tính năng:
    - [x] Hàm nhập / xuất
    - [x] Hàm chuyển đổi thập phân sang nhị phân
    - [x] Hàm chuyển đổi nhị phân sang thập phân
    - [x] Hàm chuyển đổi thập phân sang thập lục phân
    - [x] Hàm chuyển đổi nhị phân sang thập lục phân
    - [x] Các toán tử: `+`, `-`, `*`, `/`
    - [x] Các toán tử so sánh và gán: `<`, `>`, `<=`, `>=`, `==`, `=`
    - [x] Các toán tử bit: AND `&`, OR `|`, XOR `^`, NOT `~`
    - [x] Các toán tử dịch chuyển: dịch trái `<<`, dịch phải `>>`, xoay trái `rol`, xoay phải `ror`
- Dấu chấm động với độ chính xác cao:
  Kiểu dữ liệu biểu diễn số dấu chấm động có độ chính xác Quadruple-precision với độ lớn 128 bit với các tính năng:
    - [x] Hàm nhập / xuất
    - [x] Hàm chuyển đổi thập phân sang nhị phân
    - [x] Hàm chuyển đổi nhi phân sang thập phân
    - [x] Các toán tử: `+`, `-`, `*`, `/`
    - [x] Xác định các số nhị phân có dạng vô cùng `infinity`, không phải là một số dấu chấm động hợp lệ `NaN` hay số
      chưa được chuẩn hóa `denormalized`

## Thiết kế chương trình

### Cấu trúc thư mục

Bài làm được chia thành hai thư mục chính:

1. Thư mục `src/` chứa mã nguồn của QInt và QFloat
2. Thư mục `tests/` chứa testcase của QInt và QFloat tương ứng

## Biên dịch và chạy chương trình

_Chương trình đã được chạy thử nghiệm tốt trên Ubuntu 20.04._

### Yêu cầu tiên quyết

#### Linux

Để có thể biên dịch và chạy chương trình một cách ổn thỏa nhất, trên Linux, một người cần có những chương trình sau đây:

1. CMake
2. Make
3. Compiler cho C++ tương thích với C++11

#### Windows

Nếu bạn dùng Windows và sử dụng Visual Studio, bạn chỉ cần cho hết các file trong thư mục `src/`vào một project và chạy
project một cách bình thường.

Ngoài ra, bạn có thể dùng extension git của Visual Studio, clone repo này về và mở dưới dạng một project CMake và để
Visual Studio làm mọi việc còn lại.

### Biên dịch chương trình

Để biên dịch và chạy được chương trình, chúng ta cần phải config CMake để có thể tạo ra Makefile phù hợp.

Để config CMake dưới dạng Release, mình có viết một script giúp thực hiện công việc này, ta chỉ cần chạy lệnh sau

```sh
$ ./config.sh Release
```

Hoặc bạn muốn config dưới dạng Debug thì bạn chỉ cần thay `Release` thành `Debug` là ổn.

```sh
$ ./config.sh Debug
```

Sau khi CMake đã được config thành công và ta có thể bắt đầu build chương trình. Để build chương trình, ta chạy lệnh

```sh
$ make
```

Sau khi build xong, bạn có thể chạy chương trình bằng cách gọi file thực thi `CSC10005-Project1`.

### Chạy chương trình

Mặc định nếu bạn gọi file thực thi khi không kèm theo tham số, bạn sẽ thấy một dòng yêu cầu bạn nhập vào chế độ bạn mong
muốn sử dụng (QInt hay QFloat). Sau đó, bạn có thể nhập lệnh.

Nếu bạn gọi file thực thi có kèm theo tham số, bạn sẽ phải có đủ 3 tham số file đầu vào file xuất kết quả và chế độ xử
lý theo format:

```sh
$ ./CSC10005-Project1 <input_file> <output_file> <type>
```

Trong đó, `type` là 1 nếu bạn chạy dưới dạng QInt, `type` là 2 nếu bạn mong muốn chạy dưới dạng QFloat.

### Test chương trình

Trong project này, mình có đính kèm theo thư mục `tests/` dùng để chứa các test được sử dụng trong lúc chấm, trải dài
trên nhiều trường hợp cho cả hai kiểu QInt và QFloat.

Sau khi một người đã config và compile (với CMake và Make) xong, người đó có thể test chương trình thông qua lệnh

```sh
$ make test
```

Chương trình sẽ tự test với input được cho sẵn và sẽ tự so sánh với output mẫu.

Một số lưu ý trong quá trình test QFloat là chương trình mô phòng số thực vẫn có thể có sai số. Tuy nhiên, script test
của mình chỉ config cho việc kiểm tra từng dòng một, không kiểm tra sai số, cho nên bạn cũng nên kiểm tra một cách thủ
công cho QFloat thay vì tin tưởng vào script của mình.

Bạn có thể hiểu rằng nếu sai số của bạn không vượt quá một mức đủ nhỏ nào đó (ví dụ như sai số bài của bạn và kết quả
mẫu không quá 0.0000000000000001 chẳng hạn) thì bạn sẽ coi như code của bạn cho ra đúng

## Định dạng cấu trúc tập tin input và output

Dưới đây là định nghĩa cấu trúc tập tin input cho dạng QInt.

- Gồm n dòng: không biết trước giá trị n
- Trong mỗi dòng, sẽ có chỉ thị p có các giá trị sau đây (các chỉ thị này được phân biệt với các toán hạng phía sau bằng
  đúng 1 ký tự khoảng trắng):
    - p = 2: thực hiện tính toán, xử lý ở chế độ Binary
    - p = 10: thực hiện tính toán, xử lý ở chế độ Decimal
    - p = 16: thực hiện tính toán, xử lý ở chế độ Hexa
- Nếu trong 1 dòng có 2 chỉ thị p1 và p2 (p1 và p2 cách nhau bởi đúng 1 khoảng trắng): có nghĩa là chuyển toán hạng ở
  chế độ p1 sang chế độ p2.
- Trong một dòng, các toán tử hai ngôi và toán hạng được cách nhau bởi đúng 1 khoảng trắng.
- Độ dài dãy bit nhị phân, dãy hexa không cố định và không vượt quá $128$ bit.
- Mặc định dữ liệu trên từng dòng đã có tính đúng đắn, không cần xét tính hợp lệ của dữ liệu đầu vào. Mỗi thành phần
  trên một dòng cách nhau bởi đúng 1 khoảng trắng.

Dưới đây là định nghĩa cấu trúc tập tin output cho dạng QInt.

- Ghi ra n dòng, mỗi dòng tương ứng của tập tin Input là kết quả của phép tính toán hoặc chuyển đổi.

**Ví dụ:**

| Input file                             | Output file                                                    |
| :------------------------------------- | -------------------------------------------------------------- |
| 2 1111100011101010111 + 01101110110111 | 1111110001100001110                                            |
| 2 11011011 * 010101111                 | 1001010110110101                                               |
| 2 10 01101010111110111111              | 438207                                                         |
| 10 2 8793278316383117319               | 11101000001000000000000000101000111011001010010010000000000111 |
| 16 85AF + 90BC                         | 1166B                                                          |
| 10 5678 >> 2                           | 1419                                                           |

**Định dạng tập tin input và output của QFloat tương tự như trên**

### Một số vấn đề còn gặp phải

Đối với QFloat, sai số vẫn còn là một trong những vấn đề nhóm chưa giải quyết được. Với việc chuyển đổi từ số thập phân
sang nhị phân, sai số gần như không đáng kể (chỉ vài bit cuối cùng trong phần bit biểu diễn mantissa). Tuy nhiên với
phần chuyển đổi từ hệ nhị phân sang thập phân, sai số có thể nói là khá cao, nhìn chung thì phần nguyên vẫn đúng, nhưng
sai số phần số thực thì nằm ở trong khoảng tương đối lớn.
