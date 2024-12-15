# Advanced_C
<details><summary>LESSON 1: COMPILER AND MARCO</summary>
</p>

Visual Code (VS Code) gồm có 2 phần là Compiler (dùng để biên dịch chương trình) và Text Editor (dùng để soạn thảo code). Compiler của VS Code dựa trên gcc và g++. Sau đây ta sẽ tìm hiểu về Compiler.

## 1. Compiler

Compiler (trình biên dịch) là một chương trình chuyển đổi mã nguồn (source code) viết bằng ngôn ngữ lập trình cao cấp (như C, Java, Python) thành mã máy (mã nhị phân 0 1) mà máy tính có thể hiểu và thực thi.

Quá trình biên dịch gồm các giai đoạn như sau:

<p align="center">
  <img src="https://github.com/user-attachments/assets/a6f0e21e-df7d-4270-afdf-f744c329b9e6" alt="Compiler Macro" width="600">
</p>
Hình trên mô tả đầu vào, đầu ra các file và các câu lệnh trong VS Code để chạy chương trình

**Preprocessor (Tiền xử lý)**: Thực hiện 3 công việc, gồm:
 - Bộ tiền xử lý có nhiệm vụ thực hiện: 
    - Copy nội dung cắc file thư viện vào file main.c
    - Xóa bỏ các chú thích của chương trình
    - Xử lý các chỉ thị tiền xử lý

 -**Compiler**: Chuyển từ ngôn ngữ bậc cao sang ngôn ngữ bậc thấp assembly. Đầu vào là file .i, đầu ra là file .s.

```bash
gcc main.i -S -o main.s
```
 -**Assembler**: Chuyển sang mã máy (0, 1). Đầu vào là file .s, đầu ra là file .o hay còn gọi là file object.

```bash
gcc - c main.s -o main.o
```
 -**Linker**: Liên kết các file object.o lại thành một chương trình thực thi duy nhất.

```bash
gcc test1.o test2.o main.o -o main
./main
```

## 2. Macro
### Chỉ thị tiền xử lý

Chỉ thị tiền xử lý là những chỉ thị cung cấp cho bộ tiền xử lý để xử lý các thông tin trước khi quá trình biên dịch bắt đầu. Các chỉ thị tiền xử lý bắt đầu bằng ký tự #.

 -**#include**: Chèn nội dung của file được include vào file .i. Giúp chương trình dễ quản lý do phân chia thành các module.

```c
#include <stdio.h>
#include "test1.h"
```

 -**#define**: Được sử dụng để định nghĩa các hằng số hoặc các đoạn mã thay thế, không có kiểu dữ liệu. Việc sử dụng `#define` để định nghĩa được gọi là Macro.

```c
#define PI 3.14
```

 -**#undef**: Để hủy định nghĩa một `#define` đã được định nghĩa trước đó.

```c
#include <stdio.h>
#define MAX_SIZE 100

int main() {
    printf("MAX_SIZE is defined as: %d\n", MAX_SIZE);
    
    // Bỏ định nghĩa của MAX_SIZE
    #undef MAX_SIZE
    
    // Định nghĩa lại MAX_SIZE với giá trị khác
    #define MAX_SIZE 50
    
    printf("MAX_SIZE is now redefined as: %d\n", MAX_SIZE);

return 0;
}
```

 -**#if, #elif, #else**: Kiểm tra điều kiện của Macro.

```c
#include <stdio.h>
// Định nghĩa một macro
#define VERSION 3

int main() {
    // Sử dụng #if, #elif, #else
    #if VERSION == 1                               // Điều kiện #if sai, nếu không còn kiểm tra điều kiện nào
                                                    // nữa đi tới #endif luôn
    printf("This is version 1.\n");
    #elif VERSION == 2                             // Tiếp tục kiểm tra với #elif
    printf("This is version 2.\n");            
    #else                                          // Không có điều kiện nào ở trên đúng
    printf("This is another version.\n");
    #endif

return 0;
}
```

-**#ifdef, #ifndef**: Kiểm tra xem một macro đã được định nghĩa hay chưa.

+ `#ifdef` kiểm tra nếu một macro đã được định nghĩa.

+ `#ifndef` kiểm tra nếu một macro chưa được định nghĩa. Nếu điều kiện kiểm tra là đúng, đoạn mã phía sau sẽ được biên dịch, ngược lại sẽ bị bỏ qua."

```c
#include <stdio.h>
// Định nghĩa một macro
#define FEATURE_ENABLED

int main() {
    // Kiểm tra xem FEATURE_ENABLED đã được định nghĩa đúng không?
    #ifdef FEATURE_ENABLED
    printf("Feature is enabled.\n");
    #endif
    
    // Kiểm tra xem ANOTHER_FEATURE chưa được định nghĩa đúng không?
    #ifndef ANOTHER_FEATURE
    printf("Another feature is not enabled.\n");
    #endif

return 0;
}
```
    
### Macro function

Macro function là khi đoạn mã sử dụng `#define` với tham số truyền vào để hoạt động giống như một hàm. 

Nếu macro function có nhiều dòng, mỗi dòng (trừ dòng cuối) phải kết thúc bằng ký tự  `\`.

```c
#include <stdio.h>

#define DISPLAY_SUM(a,b)                        \
printf("This is macro to sum 2 number\n");      \
printf("Result is: %d", a+b);

int main() {
	DISPLAY_SUM(5,6);
return 0;
}
```

Ưu điểm của macro function so với function là tối ưu về tốc độ, nhưng không tối ưu về bộ nhớ. Cụ thể:

 -Khi function được gọi trong main(), Program Counter phải lưu địa chỉ hiện tại vào Stack Pointer, sau đó nhảy đến địa chỉ vùng nhớ chứa function. Quá trình này có thể làm giảm hiệu suất nếu gọi function nhiều lần.

 -Macro function sẽ thay thế trực tiếp mã trong chương trình chính tại vị trí macro được gọi nên tốc độ thực thi nhanh hơn. Tuy nhiên, do mỗi lần macro được sử dụng sẽ tạo ra một bản sao, nên chương trình sẽ chiếm nhiều bộ nhớ RAM hơn.

### Toán tử trong macro

**Toán tử #**: Tự chuẩn hóa kiểu chuỗi cho tham số nhập vào.

**Toán tử ##**: Nối các chuỗi lại với nhau.

```c
  #include <stdio.h>
  
  // Sử dụng toán tử tự chuẩn hóa 
  #define CREATE_FUNC(func, cmd)  \
  void func() {                   \
      printf(#cmd);               \
      printf("\n");               \
  }
  
  // Sử dụng toán tử nối chuỗi
  #define CREATE_VAR(name)        \
  int int_##name;                 
  
  CREATE_FUNC (test1, this is function test1); 
  CREATE_VAR(test);
  
  int main() {
      return 0;
  }
```

Kết quả trong file .i:

```c
void test1() { printf("this is function test1"); printf("\n"); };
int int_test;
```

### Variadic macro

Variadic macro là một loại macro có thể chấp nhận một số lượng tham số không xác định, cho phép truyền vào số lượng đối số bất kỳ. 
  
```c
#include <stdio.h>

// Định nghĩa một variadic macro
#define PRINT_ARGS(format, ...) printf(format, __VA_ARGS__)

int main() {
    // Sử dụng variadic macro để in ra các giá trị
    PRINT_ARGS("This is a variadic macro example: %d, %f\n", 42, 3.14);

    return 0;
}
```

</p>
</details>
