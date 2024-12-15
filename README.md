# Advanced_C
<details><summary>LESSON 1: COMPILER - MARCO</summary>
    <p>
        

Visual Code (VS Code) gồm có 2 phần là Compiler (dùng để biên dịch chương trình) và Text Editor (dùng để soạn thảo code). Compiler của VS Code dựa trên gcc và g++. Sau đây ta sẽ tìm hiểu về Compiler.

## 1. Compiler

Compiler (trình biên dịch) là một chương trình chuyển đổi mã nguồn (source code) viết bằng ngôn ngữ lập trình cao cấp (như C, Java, Python) thành mã máy (mã nhị phân 0 1) mà máy tính có thể hiểu và thực thi.

Quá trình biên dịch gồm các giai đoạn như sau:

<p align="center">
  <img src="https://github.com/user-attachments/assets/2b7d9501-1db5-4add-84dc-0cb16d4ea5f9" alt="Compiler Macro" width="600">
</p>
Hình trên mô tả đầu vào, đầu ra các file và các câu lệnh trong VS Code để chạy chương trình

**Preprocessor (Tiền xử lý)**: Thực hiện 3 công việc, gồm:
- Copy nội dung các file header vào file main.c
- Xóa bỏ các chú thích của chương trình
- Thay thế toàn bộ macro #define

```bash
gcc -E main.c -o main.i
```

 **Compiler**: Chuyển từ ngôn ngữ bậc cao sang ngôn ngữ bậc thấp Assembly.

```bash
gcc -S main.i -o main.s
```
 **Assembler**: Chuyển từ Assembly sang mã máy (0, 1).

```bash
gcc -c main.s -o main.o
```
 **Linker**: Liên kết các file object.o lại thành một chương trình thực thi duy nhất (Sử dụng khi cần liên kết nhiều file .c)

```bash
gcc main.o test.o -o main
./main
```

## 2. Macro
### Chỉ thị tiền xử lý

Chỉ thị tiền xử lý là các lệnh được sử dụng để chỉ dẫn cho trình biên dịch thực hiện các thao tác trước khi biên dịch mã nguồn. Các chỉ thị này thường bắt đầu bằng dấu # (#include, #define, #undef, #if, #elif, #else, #ifdef, #ifndef, #endif) và không yêu cầu dấu chấm phẩy kết thúc.

 **#include**: Chèn nội dung của file được include vào file .i trong quá trình Preprocessor. Trong đó:
 - Nếu tên file header nằm trong dấu <>: Compiler sẽ tìm file header này trong thư mục cài đặt VS Code
 - Nếu tên file header nằm trong dấu "": Compiler sẽ tìm file header này trong thư mục chứa project hiện tại

```c
#include <stdio.h>
#include "test1.h"
```

 **#define**: Được sử dụng để định nghĩa các hằng số hoặc các đoạn mã thay thế, không có kiểu dữ liệu. Lưu ý, khi muốn define một đoạn mã có nhiều dòng, ta thêm `\` cuối mỗi dòng để liên kết các dòng với nhau

```c
#include <stdio.h>
#define XY 100
#define SUM(a, b) a + b
#define MUL(a, b) 				\
int mul = a*b;					\
printf("Giá trị %d * %d = %d\n", a, b, mul)

int main(){
	int a = 10;
	int b = 5;
	printf("XY = %d\n", XY);
	int tong = SUM(a, b);
	printf("Tong %d + %d = %d\n", a, b, tong);
	MUL(a, b);
}
```

 **#undef**: Để hủy định nghĩa một `#define` đã được định nghĩa trước đó.

```c
#include <stdio.h>
#define XY 100

int main() {
	printf("XY = %d\n", XY);
    
	// undefine XY
	#undef XY
    
	// Định nghĩa lại XY với giá trị khác
	#define XY 10
    
	printf("Giá trị mới của XY = %d\n", XY);
	return 0;
}
```

 -**#if, #elif, #else, #endif**: Kiểm tra và biên dịch mã dựa trên các điều kiện nhất định.

```c
#include <stdio.h>

#define DEBUG 1

int main() {
	#if DEBUG
        printf("Chế độ debug đang bật.\n");
    	#elif !DEBUG
        printf("Chế độ debug đang tắt.\n");
    	#else
        printf("Không xác định chế độ debug.\n");
    	#endif

   	return 0;
}
```

-**#ifdef, #ifndef, #endif**: Là các chỉ thị tiền xử lý được sử dụng để kiểm tra xem một macro đã được định nghĩa hay chưa.

+ `#ifdef` kiểm tra xem một macro có được định nghĩa hay không. Nếu macro đã được định nghĩa, điều kiện đúng.

+ `#ifndef` kiểm tra xem một macro chưa được định nghĩa. Nếu macro chưa được định nghĩa, điều kiện đúng.

```c
#include <stdio.h>

#define DEBUG

int main() {
    	//Đúng nếu DEBUG đã được định nghĩa
	#ifdef DEBUG
        printf("Chế độ debug đã được bật.\n");
   	#endif

	//Đúng nếu DEBUG chưa được định nghĩa
    	#ifndef DEBUG
        printf("Chế độ debug chưa được bật.\n");
   	#endif

   	return 0;
}

```
    
## Toán tử trong macro

**Toán tử #**: Tự chuẩn hóa kiểu chuỗi cho tham số nhập vào.

**Toán tử ##**: Nối các chuỗi lại với nhau.

```c
#include <stdio.h>

#define Noi(X, Y) X##Y

#define Create_Func(func, cmd)  \
void func(){                    \
    printf(#cmd);               \
}

int main(){
	int XY = 100;
	//Nối X và Y thành XY rồi in ra giá trị XY
	printf("XY = %d\n", Noi(X, Y));
	
	//Ví dụ dùng # để chuẩn hóa chuỗi
   	Create_Func(test, hello);
 }
```

## Variadic macro

Variadic macro là một loại macro có thể chấp nhận một số lượng tham số không xác định, cho phép truyền vào số lượng đối số bất kỳ. 
  
```c
#include <stdio.h>

//define Variadic Macro
#define PRINT(fmt, ...) printf(fmt, __VA_ARGS__)

int main() {
    PRINT("Hello, %s!\n", "World");  // In ra: Hello, World!
    return 0;
}
```

</p>
</details>
