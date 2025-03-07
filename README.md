# Advanced C/C++
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

Variadic macro thường sử dụng đối với hàm có tham số truyền vào không xác định, cho phép truyền vào số lượng đối số bất kỳ. 
  
```c
#include <stdio.h>
#define COUNT_ARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int))
/*
 * COUNT_ARGS(1, 2, 3)
 * sizeof((int[]){1, 2, 3}) = 12 byte
 * sizeof(int) = 4
 * => n = 3 phần tử
 */

#define sum2(...)                   \
int arr[] = {__VA_ARGS__};          \
int tong = 0;                       \
int n = COUNT_ARGS(__VA_ARGS__);    \
int i = 0;                          \
while (i != n){                     \
    tong += arr[i];                 \
    i++;                            \
}                                   \
printf("Tổng là: %d", tong);        


int main()
{
     int a, b, c;
    sum2(1, 2, 1, 0, 8, 9, 6);
    return 0;

}
```

</p>
</details>













<details><summary>LESSON 2: STDARG-ASSERT</summary>
<p>
  
## 1. Thư viện STDARG

Thư viện stdarg là tương tự với Macro Variadic ở Lesson 1, nhưng được viết thành 1 thư viện, cung cấp các biến và hàm. Mục đích hỗ trợ làm việc với các hàm có số lượng input parameter không xác định. 

Một số hàm:

-**va_list**: Là một kiểu dữ liệu dành cho tập hợp các tham số không xác định. Bản chất của nó là con trỏ kiểu char được định nghĩa lại tên bằng typedef: 
```bash
typedef char* va_list
```
Thông thường ta sử dụng va_list để khai báo một biến chứa các tham số không xác định. Vd:
```bash
va_list args;
```

-**va_start(va, l)**: Dùng để bắt đầu truy xuất các tham số biến. 
va_start nhận hai đối số: Biến đã khai báo bằng va_list; Tên biến của tham số cố định cuối cùng trong danh sách tham số truyền vào.
Sau hàm này chuỗi truyền vào sẽ được tách ra gồm: Tên tham số cố định cuối được truyền vào; Danh sách tham số không xác định. Vd:
```bash
va_start(args, count);
```

-**va_arg(va, type)**: Lấy các đối số tiếp theo trong danh sách các đối số không xác định. Cast nó sang kiểu dữ liệu được chỉ định trong type. Vd:
```bash
va_arg(args, int);
```

-**va_copy(va_list dest, va_list src)**: Copy danh sách của src gắn vào dest. Vd:
```bash
va_copy(check,args);
```


-**va_end(va)**: Sau khi hoàn tất việc truy cập các đối số, cần gọi va_end để giải phóng tài nguyên được sử dụng bởi va_list. Vd:
```bash
va_end(args);
```

**Ví dụ 1: Xuất các số ra màn hình**
Cách 1: Cách làm sau đây sử dụng biến count cho biết số lượng phần tử không xác định.
Nhược điểm của cách làm này là phải biết số lượng count trước
```c
#include <stdio.h>
#include <stdarg.h>

void Output_Func(int count, ...){
    va_list args;
    /*
     * typedef char* va_list
     * args = "int count, 2, 5, 9, 10, 11"
            0xa0 'i', 0xa1 'n', ... 0xaa '2', ... 0xbf '1'
     */
    
    va_start(args, count); //"count"  "2, 5, 9, 10, 11"
    
    /*
     * Hàm va_arg(args,int)
     * args: 
     */
    for(int i=0; i<count; i++){
        printf("Giá trị thứ %d là: %d\n", i, va_arg(args, int));
    }

    va_end(args); //
}

int main(){
    Output_Func(5, 2, 5, 9, 10, 11);
}

```

**Ví dụ 2: Tính tổng**
Cách 2: Cách làm sau đây không cần biết trước số lượng tham số không xác định truyền vào.
Nhược điểm là sẽ sai nếu chuỗi có số 10.
Do mã ASCII của '\n' = 10
```c
#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__, '\n')

void sum(int count, ...){
    va_list args;
    va_list check;
    va_start(args, count);
    va_copy(check, args);
    int result = count;
    
    while(va_arg(check, char*) != (char*)'\n'){
        result += va_arg(args, int);
    }
    printf("Kết quả là: %d", result);

    va_end(args);
    va_end(check);
}
int main(){
    tong(4, 8, 20, 0, 2, 3);
}

```
## 2. Thư viện ASSERT

Thư viện assert.h là thư viện để hỗ trợ debug chương trình.

-**Hàm assert()**: Dùng để kiểm tra điều kiện. Nếu điều kiện đúng (true) thì chương trình tiếp tục. Nếu điều kiện sai (false) thì dừng và báo lỗi. 

**Ví dụ báo lỗi chia cho 0:**

```c
#include <stdio.h>
#include <assert.h>
double divide (int a, int b){
    assert(b != 0 && "b phải khác 0");
    return (double)a/b;
}

int main(){
    printf("a/b = %f", divide(6,0));
    return 0;
}
```

**Báo lỗi:** Do truyền vào b = 0, không thoả điều kiện b != 0 => Báo lỗi assert "b phải khác 0".

```bash
Assertion failed: b != 0 && "b phải khác 0", file ASSERT_Ex0.c, line 4
```
</p>
</details>





















<details><summary>LESSON 3: POINTER</summary>
<p>
  
## 1. Định nghĩa con trỏ (pointer)

Con trỏ là một biến chứa địa chỉ của một đối tượng khác (đối tượng ở đây có thể là: biến, hàm, mảng, …).
Đối với 1 biến, máy tính sẽ hiểu 2 nội dung: Địa chỉ của biến (nằm trong vùng RAM, cấp phát cho biến), giá trị của biến tại địa chỉ đã cấp phát.
Đối với con trỏ, cũng có 2 nội dung: Địa chỉ của con trỏ (cũng nằm trong vùng RAM), giá trị của con trỏ (là địa chỉ của biến mà con trỏ đang trỏ đến)
Vd:   
<img src="https://github.com/user-attachments/assets/298b43a9-db68-45f8-a208-ecba2ec79c4b" alt="Compiler Macro" width="550">

**Kích thước của con trỏ:** Kích thước con trỏ trong lập trình thường được hiểu là kích thước bộ nhớ mà con trỏ chiếm dụng để lưu trữ địa chỉ của một biến hoặc đối tượng trong bộ nhớ. Kích thước này phụ thuộc vào hệ điều hành và kiến trúc của máy tính, cụ thể là số bit của bộ vi xử lý.
 
 - Ví dụ:
 - Trên hệ thống 32-bit, kích thước của con trỏ thường là 4 byte (32 bit).
 - Trên hệ thống 64-bit, kích thước của con trỏ thường là 8 byte (64 bit).
 - Lý do con trỏ có kích thước như vậy là vì con trỏ chỉ chứa một địa chỉ bộ nhớ, và địa chỉ này phải có độ dài phù hợp để chỉ đến một ô nhớ trong bộ nhớ của máy tính.

## 2. Các loại con trỏ
**Void pointer:** Là con trỏ mà có thể trỏ đến bất kỳ địa chỉ nào, mà không cần biết kiểu dữ liệu của giá trị tại địa chỉ đó
```bash
void *ptr_void;
```
Khi in ra giá trị mà void pointer trỏ đến, ta phải ép kiểu con trỏ void pointer trùng với kiểu dữ liệu sẽ đọc 
```bash
*(int*)ptr
```
Ví dụ:
```c
#include <stdio.h>

int main(){
    void *ptr;
    int a = 5;
    ptr = &a;
    printf("Địa chỉ = %p. Giá trị = %d\n", ptr, *(int*)ptr);
    //Địa chỉ dùng %p để hiển thị
    //(int*)ptr: ép kiểu cho con trỏ, để con trỏ biết nó đang trỏ đến số nguyên => sẽ đọc 4 byte giá trị
    //*(int*)ptr: lấy 4 byte tại địa chỉ ptr đang trỏ đến

    double b = 3.14;
    ptr = &b;
    printf("Địa chỉ = %p. Giá trị = %f\n", ptr, *(double*)ptr);
    printf("Địa chỉ = %p. Giá trị = %0.2f\n", ptr, *(double*)ptr);

    char c = 'c';
    ptr = &c;
    printf("Địa chỉ = %p. Giá trị = %c\n", ptr, *(char*)ptr);

    char arr[] = "hello";
    ptr = arr; //không cần & 
    printf("Địa chỉ = %p. Giá trị = %c\n", ptr, *(char*)ptr);           //ký tự đầu của "hello"
    printf("Địa chỉ = %p. Giá trị = %c\n", ptr, *(char*)(ptr + 1));     //ký tự thứ 2 của "hello" = e
    printf("Địa chỉ = %p. Giá trị = %c\n", ptr, *(char*)(ptr + 1) + 1); //ký tự e + 1
    for(int i = 0; i<5; i++){
        printf("Địa chỉ = %p. Giá trị = %c\n", ptr, *(char*)(ptr + i));
    }

    //Mảng con trỏ void
    printf("\nMảng con trỏ void:\n");
    void *ptr1[] = {&a, &b, &c, arr};
    printf("Giá trị ptr1[0] = %d\n", *(int*)ptr1[0]);
    printf("Giá trị ptr1[1] = %f\n", *(double*)ptr1[1]);
    printf("Giá trị ptr1[2] = %c\n", *(char*)ptr1[2]);
    printf("Giá trị ptr1[3] = %c\n", *(char*)ptr1[3]);
    printf("Giá trị ptr1[3] = %c\n", *(char*)(ptr1[3]+1));


    printf("\nvoid pointer của của int\n");
    int num[] = {322, 5, 9};   //322 = 0b0001 0100 0010
    void *ptr2 = num;
    // printf("Địa chỉ = %p. Giá trị = %d\n", ptr2, *(char*)ptr2); //sai kiểu dữ liệu của pointer. KQ =66
    // printf("Địa chỉ = %p. Giá trị = %d\n", ptr2, *(char*)(ptr2 + 1)); //sai kiểu dữ liệu của pointer. KQ =1
    printf("Địa chỉ = %p. Giá trị = %d\n", ptr2, *(int*)(ptr2 + 4)); //KQ = Giá trị num[1] = 5

    return 0;
}
```
**Function pointer (con trỏ hàm):** Là con trỏ trỏ đến địa chỉ của một hàm.
Để khai báo con trỏ hàm cần xem xét 2 thứ:
Kiểu trả về của hàm, tham số truyền vào có kiểu dữ liệu là gì. Để khi khai báo con trỏ hàm phải có cùng kiểu trả về, và các tham số của nó phải có cùng kiểu dữ liệu
```bash
void (*ptr)(int, double);  
```
- Con trỏ ptr này sẽ trỏ đến một hàm có kiểu trả về là void và hàm này nhận vào hai tham số với kiểu dữ liệu lần lượt là int và double.
- Con trỏ này có thể trỏ tới bất kỳ hàm nào trong chương trình có cùng kiểu trả về và kiểu tham số tương ứng như đã định nghĩa.

```c
#include <stdio.h>

void sum(int a, int b) {printf("%d + %d = %d\n", a, b, a+b);}
void subtract(int a, int b) {printf("%d - %d = %d", a, b, a-b);}
void calculate(void (*ptr)(int, int), int a, int b){
    ptr(a, b);
}
int main(){
    //Cách 1:
    // void (*ptr)(int, int) = sum;
    // ptr (2, 3);

    // ptr = subtract;
    // ptr (5, 20);

    //Cách 2:
    // void (*ptr[])(int, int) = {&sum, &subtract};
    // ptr[0](2, 3);
    // ptr[1](5, 20);

    //Cách 3:
    calculate(sum, 2, 3);
    calculate(subtract, 5, 20);
    return 0;

}

```
**Pointer to constant (con trỏ hằng):** Là con trỏ mà một khi trỏ tới địa chỉ nào đó rồi thì nó sẽ không được phép thay đổi giá trị tại địa chỉ mà nó trỏ đến thông qua dereference (*ptr). Nhưng giá trị tại địa chỉ đó có thể thay đổi.
- Ứng dụng: Đối tượng đang được trỏ đến không bị thay đổi trong suốt quá trình chạy
```bash
int const *ptr_const; 
const int *ptr_const;
```
```c
#include <stdio.h>
int a = 5;
int b = 20;
const int *ptr = &a;
int *const ptr1 = &b;

void stringCompare(const char *str1, const char *str2){
    int *ptr2 = NULL; //trỏ đến 0x00
}
int main(){
    //pointer to constant
    //*ptr = 10; error: assignment of read-only location '*ptr'
    a = 10;
    printf("Địa chỉ = %p. Giá trị của a = %d\n", ptr, *ptr);

    ptr = &b;
    printf("Địa chỉ = %p. Giá trị của b = %d\n", ptr, *ptr);

    //constant pointer
    //ptr1 = &a; error: assignment of read-only variable 'ptr1'
    return 0;
}
```
**Constant pointer (hằng con trỏ):** Constant to pointer là một con trỏ mà trỏ đến 1 địa chỉ cố định. Sau khi con trỏ được khởi tạo, địa chỉ mà nó trỏ đến không thể thay đổi.
```bash
int *const const_ptr = &value;
```
```c
#include <stdio.h>
#include <stdlib.h>
int main() {
    int value = 5;
    int test = 15;
    int *const const_ptr = &value;
    printf("value: %d\n", *const_ptr);  

    *const_ptr = 7;
    printf("value: %d\n", *const_ptr); 
    //const_ptr = &test;  wrong
    return 0;
}
```
**Null pointer (con trỏ null):** Null Pointer là một con trỏ không trỏ đến bất kỳ đối tượng hoặc vùng nhớ cụ thể nào.
- Khi khai báo 1 con trỏ mà chưa sử dụng ngay (chưa gán cho nó địa chỉ) thì phải mặc định cho nó là NULL, để nó không trỏ tới địa chỉ khác. Hoặc là sau khi sử dụng con trỏ xong, cũng phải trỏ nó đến NULL, để tránh nó trỏ đến các địa chỉ khác trong vùng RAM
```bash
int *ptr_null = NULL;
```
```c
#include <stdio.h>

int main(){
    int *ptr = NULL;
    if (ptr == NULL)
        printf("ptr = NULL\n");
    else    
        printf("ptr khác NULL\n");
    
    int a = 5;
    ptr = &a;
    *ptr = 30;
    ptr = NULL;
    printf("a ban đầu = 5. Hiện tại a = %d\n", a);
}
```
**Pointer to pointer (con trỏ cấp 2, cấp 3):** Là một kiểu dữ liệu trong ngôn ngữ lập trình cho phép lưu trữ địa chỉ của một con trỏ. Con trỏ đến con trỏ cung cấp một cấp bậc trỏ mới, cho phép thay đổi giá trị của con trỏ gốc. Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi làm việc với các hàm cần thay đổi giá trị của con trỏ.
- Con trỏ đến con trỏ là một kiểu dữ liệu cho phép lưu trữ địa chỉ của một con trỏ.
- Nó cung cấp một cấp bậc trỏ mới, cho phép thay đổi giá trị của con trỏ gốc.
- Cấp bậc này có thể hữu ích trong nhiều tình huống, đặc biệt là khi làm việc với các hàm cần thay đổi giá trị của con trỏ.
```bash
int **ptr;
```
```c
#include <stdio.h> 
int main() { 
int a = 10; 
int *ptr1 = &a; // Con trỏ ptr1 trỏ đến biến a 
int **ptr2 = &ptr1; // Con trỏ ptr2 trỏ đến con trỏ ptr1 
printf("Địa chỉ của a = %p. Giá trị của a = %d\n", &a, a); // In ra giá trị của a 
printf("Địa chỉ của ptr1 = %p. Giá trị của ptr1 = %d\n", &ptr1, *ptr1); // In ra giá trị ptr1 trỏ tới (giá trị của a) 
printf("Địa chỉ của ptr2 = %p. Giá trị của ptr2 = %d\n", &ptr2, **ptr2); // In ra giá trị ptr2 trỏ tới (giá trị của a qua ptr1) 
return 0; 
}
```

</p>
</details>




































<details><summary>LESSON 4: GOTO - SETJMP</summary>
<p>
  
## 1. Goto
	
Goto được gọi là một từ khoá trong ngôn ngữ lập trình C/C++, cho phép chương trình nhảy từ vị trí này đến vị trí bất kì **trong cùng một hàm**. Từ khóa goto chỉ có thể nhảy cục bộ trong hàm, ví dụ hàm main. Thực chất có các cách khác để nhảy, ví dụ như tạo ra một biến để quản lý trạng thái, nhưng khai báo biến sẽ gây tốn vùng nhớ trên RAM để cấp phát, vì vậy dùng goto là cách tối ưu hơn vì không tốn vùng nhớ.
Goto giúp việc kiểm soát luồng chạy (flow) của chương trình tốt hơn.

**Ví dụ: In từ 0 đến 4**

```c
#include <stdio.h>

int main(){
    int i = 0;
    start:
    if(i >= 5)
        goto end;
    printf("i = %d\n",i);
    i++;
    goto start;
    end:
    return 0;
}
```
**Kết quả:**

```bash
i = 0
i = 1
i = 2
i = 3
i = 4
```


Từ khóa `goto` có thể thay thế `break` hoặc các phương pháp khác khi cần thoát ra khỏi nhiều vòng lặp lồng nhau, giúp làm mã nguồn trở nên đơn giản và dễ quản lý hơn.

```c
#include <stdio.h>

int main(){
    int key = 0;
    main_menu:
    
    do{
        printf("1. Menu chinh\n");
        printf("2. ...\n");
        printf("3. ...\n");
        printf("Nhap cac tuy chon: \n");  
        scanf("%d", &key);
    }while(key != 1);

    switch(key){
        case 1:
            printf("4. ...\n");
            printf("5. Ket thucc\n");
            printf("6. Quay lai main menu\n");
            printf("Nhap cac tuy chon: ");  scanf("%d", &key);
            switch(key){
                case 4:
                case 5: goto exit_prog;
                case 6: goto main_menu;   
            }
        case 2:
        case 3:
        break;
    }
    exit_prog:
    return 0;
}
```

## 2. Setjmp.h

 - Goto chỉ có thể nhảy trong cùng 1 hàm, vậy muốn nhảy từ hàm này sang hàm khác thì ta sử dụng setjmp.h. Thư viện setjmp.h cung cấp các hàm như setjmp hoặc longjmp để nhảy từ vị trí ở hàm này sang vị trí ở hàm khác.
 -  Ứng dụng của setjmp longjmp là dùng để debug chương trình, dùng để tạo ra xử lý lỗi ngoại lệ
 -  Khác biệt so với Assert: khi dùng assert, nếu có lỗi sẽ dừng ngay lập tức ở assert. Còn setjmp sẽ hiển thị lỗi và chương trình vẫn tiếp tục thực thi
 -  Setjmp sẽ thực hiện 2 chức năng: lưu lại trạng thái hiện tại (địa chỉ của dòng đó) và trả về 1 giá trị, và lần đầu tiên gọi thì sẽ trả lại giá trị 0, từ lần thứ 2 trở đi giá trị sẽ phụ thuộc vào hàm longjmp.
 -  Chức năng của longjmp là khi gọi longjmp ra nó sẽ mặc định nhảy về vị trí của setjmp và gán con số cho hàm setjmp.
 -  Cách sử dụng:
 -  Đầu tiên, cần khai báo một biến buf, biến này có kiểu dữ liệu jmp_buf được định nghĩa trong thư viện setjmp.h
```bash
    jmp_buf buf;
```

 -  Tiếp theo, sử dụng hàm `setjmp` của thư viện `setjmp.h` để lưu trạng thái hiện tại của buf. Lần đầu tiên được gọi, setjmp sẽ trả về giá trị 0, từ lần thứ 2 trở đi giá trị sẽ phụ thuộc vào hàm longjmp.
```bash
exception = setjmp(buf);
```
 -  Tiếp theo, sử dụng hàm `longjmp` của thư viện `setjmp.h` nó sẽ mặc định nhảy về vị trí của setjmp và gán con số cho hàm setjmp.
```bash
longjmp(buf, x);
```  

**Ví dụ:**
```c
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;

#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(x) else if(exception == x)
#define THROW(x) longjmp(buf, x)

double divide (int a, int b){
    if(a == 0 && b == 0)
        THROW(1);
    else if (b == 0)
        THROW(2);
    return (double)a/b;
}
int main(){
    TRY    
        printf("Ket qua la : %f\n", divide (3,0));
    CATCH(1)
        printf("a va b = 0\n");
    CATCH(2)
        printf("b = 0\n");
}
```

**Kết quả:**

```bash
b = 0
```

</p>
</details>























<details><summary>LESSON 5: EXTERN-STATIC-VOLATILE-REGISTER</summary>
<p>

Một số từ khoá thường đi với khai báo biến hoặc khai báo hàm gồm: extern, static, volatile, register.
## 1. Extern

Mục đích của extern là 
 - Dùng để chia sẻ tài nguyên (biến, mảng, hàm) giữa các file trong cùng một thư mục
 - Khi dùng extern chỉ được phép khai báo, không được định nghĩa nội dung cho nó. Ví dụ: `extern int a;`
 - Khi dùng extern thì phải liên kết file. Ví dụ: `gcc File1.c File2.c main.c -o main`

Khi trình biên dịch gặp biến có từ khoá extern thì nó sẽ hiểu biến hoặc hàm đó đã được định nghĩa ở một nơi khác (file khác) và có thể được sử dụng ở file hiện tại.
**Extern** thường ứng dụng trong thiết kế thư viện.
**Lưu ý:** Trong C/C++, đối với hàm void, dù không sử dụng từ khoá extern vẫn có thể gọi lại trong các file khác.

**Ví dụ:**
File1.c  
```c
#include <stdio.h>
#include "File1.h"

int a = 10;

void display1(){
    printf("This is File1.c\n");
}
```
File2.c
```c
#include <stdio.h>
#include "File2.h"

int b = 20;

void display2(){
    printf("This is File2.c\n");
}
```
main.c
```c
#include <stdio.h>
#include "File1.h"
#include "File2.h"

int main(){
    a = 1;
    printf("a = %d\n", a);

    b = 2;
    printf("b = %d\n", b);

    display1();
    display2();

    return 0;
}
```
Kết quả:
```bash
a = 1
b = 2
This is File1.c
This is File2.c
```
## 2. Static
Static gồm: static global và static local
### Static local variables
Static đi chung với biến cục bộ thì gọi là static cục bộ.  
Thay vì địa chỉ của biến bình thường nằm trong phân vùng stack, địa chỉ của biến static cục bộ sẽ nằm ở phân vùng BSS (nếu giá trị khác 0), còn nếu giá trị bằng 0 thì nằm ở phân vùng Data. Địa chỉ của biến static cục bộ sẽ tồn tại xuyên suốt chương trình.
**Ví dụ:**
```c
#include <stdio.h>

void count(){
    static int a = 5;
    printf("a = %d\n", a++); //0xa5: 5 - BSS
}

int main(){
    count();    //a = 5 -> 0xa5: 6
    count();    //a = 6 -> 0xa5: 7
    count();    //a = 7 -> 0xa5: 8

    return 0;
}
```
Với chương trình này, sẽ có sự khác biệt nếu ta khai báo biến a là `int a = 5;` và `static int a = 5;`  
1. Khi khai báo `int a = 5`: Lúc này, a là biến cục bộ của hàm `count`. Khi ta gọi hàm `count` 3 lần trong hàm `main`. Mỗi lần gọi thì biến a sẽ được khai báo lại, địa chỉ của mỗi lần khai báo có thể khác nhau. Kết quả lúc này là:
```bash
a = 5
a = 5
a = 5
```
2. Khi khi báo `static int a = 5`: a là biến cục bộ với từ khoá `static`. Lúc này, sau lần gọi đầu, biến a sẽ được cấp một địa chỉ và địa chỉ này không bị mất khi thoát khỏi hàm `count`. Kết quả lúc này sẽ là:
```bash
a = 5
a = 6
a = 7
```   
### Static global variables
**Chức năng:** Giới hạn phạm vi hoạt động của biến chỉ trong nội bộ của File hiện tại, dù các file khác muốn sử dụng lại biến này, dùng từ khoá extern thì cũng không được sử dụng lại biến này.	
**Ứng dụng:** Dùng để thiết kế các file thư viện, tránh việc sử dụng các hàm ở những file khác gây lỗi thư viện.
**Ví dụ:**
```c
#include <stdio.h>

static int a;
static void display(){
    printf("Static void\n");
}

int main(){

    return 0;
}
```
## 3. Volatile 

Khi một biến được khai báo nhưng không thay đổi trong suốt quá trình chạy, và trường hợp này xảy ra nhiều lần nhiều lần. Khi đó compiler sẽ tự động xoá biến đó, địa chỉ của biến đó sẽ bị thu hồi, gọi là tối ưu hoá.  
Ví dụ: Biến được khai báo dành cho nút nhấn, nếu nhiều lần biến không thay đổi thì nó sẽ bị tối ưu hoá, sau đó, mặc dù có nhấn nút thì nó cũng không cập nhật giá trị cho biến nút nhấn. Để khắc phục trường hợp bị tối ưu hoá, ta có thể khai báo biến đó là volatile.  
Volatile báo hiệu cho trình biên dịch rằng biến có thể thay đổi ngẫu nhiên, ngoài sự kiểm soát của chương trình.  
Ví dụ chương trình đọc một nút bấm, định nghĩa như sau:
```c
#include “stm32f4xx.h”
uint8_t *addr = (uint8_t*)0x20000000;
volatile uint8_t var = 0;
int main() {
while(1) {
	var = *addr;
	if (var != 0){
		break;
	}
    }
};
```
Ở đây nếu không có volatile, thì sau nhiều lần lặp, biến var sẽ bị tối ưu hoá, lúc này dù có thay đổi giá trị của biến var, giá trị biến var sẽ luôn bằng 0, lặp vô tận.
## 4. Register
Khi khai báo biến, biến sẽ được cấp phát địa chỉ nằm trong vùng RAM. Nếu ta thực hiện phép toán trên biến đó thì để trả về kết quả của phép tính sẽ phải qua một số quá trình.
<p align="center">
  <img src="https://github.com/user-attachments/assets/5368d917-f23f-4c36-aef6-fd29215ae5e9" alt="LESSON 5" width="579">
</p>

 -  Từ vùng nhớ RAM sẽ đẩy vào Register để lưu trữ trong thanh ghi R1, R2, R3…
 -  Từ Register sẽ được đẩy vào ALU để thực hiện phép toán số học
 -  Sau khi tính toán xong, kết quả sẽ trả về lại Register rồi mới trả về lại RAM
 Quá trình thực hiện một phép tính phải qua nhiều bước, để tối ưu hoá việc này thì C/C++ cung cấp từ khoá Register.  
 Một biến được khai báo bằng từ khoá Register sẽ được lưu trữ trực tiếp trong thanh ghi. Nhưng biến này sẽ không có địa chỉ trong RAM.

**Ứng dụng:** Khai báo cho các biến đặt nặng vấn đề tính toán số học.  
**Lưu ý:** Từ khoá register chỉ được khai báo biến cục bộ, không được khai báo biến toàn cục.
 - Một là do biến register không có địa chỉ, làm giảm tính linh hoạt của biến. Biến toàn cục sẽ sử dụng ở nhiều vị trí khác nhau, khai báo bằng register sẽ không có địa chỉ, như vậy sẽ không thể truy cập được tới nó.
 - Hai là do số lượng hạn chế của thanh ghi, tuỳ loại máy tính và dòng vi điều khiển sẽ có số lượng thanh ghi khác nhau, ví dụ từ R0 đến R31. Khi khai báo register toàn cục, nó sẽ dành hẳn 1 thanh ghi cho register.
 
Tuy nhiên, việc sử dụng register chỉ là một đề xuất cho trình biên dịch và không đảm bảo rằng biến sẽ được lưu trữ trong thanh ghi. Trong thực tế, trình biên dịch có thể quyết định không tuân thủ lời đề xuất này

</p>
</details>





































<details><summary>LESSON 6: BITMASK</summary>
<p>

## 1. Khái niệm
Bitmask là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xóa và kiểm tra trạng thái của các bit cụ thể trong một từ (word).
Bitmask thường được sử dụng để tối ưu hóa bộ nhớ, thực hiện các phép toán logic trên một cụm bit, và quản lý các trạng thái, quyền truy cập, hoặc các thuộc tính khác của một đối tượng.
## 2. Ứng dụng bitmask 
Người ta dựa vào thuộc tính của các cổng logic NOT, AND, OR, XOR để vận dụng vào bitmask. Ví dụ:
 - Cổng NOT: ~a. Đảo bit
<img src="https://github.com/user-attachments/assets/ca3e9c64-c46b-4e11-bb25-defbb3116081" alt="Compiler Macro" width="350">

 - Cổng AND: a & b. Kết quả chỉ bằng 1 khi cả a và b cùng bằng 1.
<img src="https://github.com/user-attachments/assets/31c49323-3d6e-425b-bf20-d16f46a3d289" alt="Compiler Macro" width="400">

 - Cổng OR: a | b. Kết quả chỉ bằng 0 nếu a và b cùng bằng 0.
<img src="https://github.com/user-attachments/assets/eda6f8a9-9e1c-4894-8b9a-b65171e9be51" alt="Compiler Macro" width="400">

 - Cổng XOR: a ^ b. Có thể sử dụng để toggle bit, khi a XOR với 1 thì kết quả sẽ là ~a.
<img src="https://github.com/user-attachments/assets/915745ac-45fa-462c-91ae-2a9eac9147b3" alt="Compiler Macro" width="400">

 - Shift left bitwise: Dùng để dịch trái, và các bit ngoài cùng bên phải (sau khi dịch) sẽ được đặt giá trị 0.
   Vd:
```bash
   0b10010111 << 3 = 0b10111000
```
 - Shift right bitwise: Dùng để dịch phải, và các bit ngoài cùng bên trái (sau khi dịch) sẽ là 0 hoặc 1 tuỳ theo bit dấu MSB.
   Vd:
```bash
   0b10010111 >> 3 = 0b11110010
```
 - Ví dụ: 
```c
//Sử dụng shift left bitwise
#include <stdio.h>
#include <stdint.h>
                       //                         0      1
#define GENDER    1 << 0  //bit 0: giới tính     nữ     nam   0b0000 0001
#define SHIRT     1 << 1  //bit 1: áo thun      không   có    0b0000 0010
#define HAT       1 << 2  //bit 2: nón          không   có    0b0000 0100
#define SHOES     1 << 3  //bit 3: giày         không   có    0b0000 1000
#define FEATURE1  1 << 4  //bit 4: tính năng 1  không   có    0b0001 0000
#define FEATURE2  1 << 5  //bit 5: tính năng 2  không   có    0b0010 0000
#define FEATURE3  1 << 6  //bit 6: tính năng 3  không   có    0b0100 0000
#define FEATURE4  1 << 7  //bit 7: tính năng 4  không   có    0b1000 0000
```
Dùng OR trong bitmask:
```c
void enableFeature(uint8_t *options, uint8_t feature){
    *options |= feature;
}
// options   = 0bxxxx xxxx
// feature   = 0b0000 0010
// OR        = 0bxxxx xx1x
// feature   = 0b0000 1000
// OR        = 0bxxxx 1x1x
```

Dùng AND và NOT trong bitmask:
```c
void disableFeature(uint8_t *options, uint8_t feature){
    *options &= ~feature;
}
// options   = 0bxxxx xxxx
// ~ feature = 0b1111 1110
// AND       = 0bxxxx xxx0
// ~ feature = 0b1111 0111
// AND       = 0bxxxx 0xx0
```

```c
uint8_t isFeatureEnable(uint8_t options, uint8_t feature){
    return((options & feature) != 0); 
    //true:  feature ON
    //false: feature OFF
}

void listSelectedFeatures(uint8_t options){
    printf("Selected Features: \n");

    const char *featuresName[] = {
        "Gender",
        "Shirt",
        "Hat",
        "Shoes",
        "Feature 1",
        "Feature 2",
        "Feature 3",
        "Feature 4"
    };
    
    for (int i = 0; i < 8; i++){
        if((options >> i) & 1){
            printf("%s\n", featuresName[i]);
        }
    }
}

int main(){
    uint8_t options = 0;
    enableFeature(&options, GENDER | HAT | SHOES);
    if(isFeatureEnable(options, GENDER)) 
        printf("GENDER được chọn\n");
    else
        printf("GENDER không được chọn\n");

    if(isFeatureEnable(options, HAT))  
        printf("HAT được chọn\n");
    else                            
        printf("HAT không được chọn\n");
    disableFeature(&options, HAT);
    listSelectedFeatures(options);
    return 0;
}
```

 - Kết quả:
```bash
GENDER được chọn
HAT được chọn
Selected Features: 
Gender
Shoes
```


## 3. Bit field

Bit fields là kỹ thuật chỉ có trong struct, chỉ định các thành viên trong struct chiếm số lượng bit cụ thể, qua đó biểu thị trạng thái cờ on/off (Thay vì sử dụng toàn bộ các bit trong kiểu dữ liệu được khai báo thì chỉ sử dụng một số bit nhất định). Nhờ vậy, bit fields có tác dụng tối ưu bộ nhớ.

**Ví dụ**:

```c
#include <stdio.h>
#include <stdint.h>

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_WHITE 2
#define COLOR_BLUE 3
#define POWER_100HP 0
#define POWER_150HP 1
#define POWER_200HP 2
#define ENGINE_1_5L 0
#define ENGINE_2_0L 1
#define SUN_ROOF_MASK 1 << 0
#define PREMIUM_AUDIO_MASK 1 << 1
#define SPORTS_PACKAGE_MASK 1 << 2

typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;

//Các bit của additionalOptions sẽ nằm ở bit 210
typedef struct{
    uint8_t additionalOptions : 3;
    CarColor color : 2;
    CarPower power : 2;
    CarEngine engine : 1;
}CarOptions;

void configureCar(CarOptions *car, CarColor color, CarEngine engine, CarPower power, uint8_t options){
    car->color = color;
    car->engine = engine;
    car->power = power;
    car->additionalOptions = options;
} 

void setOptions(CarOptions *car, uint8_t options){
    car->additionalOptions |= options;
}

void unsetOptions(CarOptions *car, uint8_t options){
    car->additionalOptions &= ~ options;
}

void displayCarOptions(CarOptions car){
    const char *colors[] = {"Red", "Black", "White", "Blue"};
    const char *powers[] = {"100Hp", "150Hp", "200Hp"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("\nCar Options:\n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUN_ROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}

int main(){
    CarOptions myCar;
    configureCar(&myCar, COLOR_BLACK, ENGINE_1_5L, POWER_150HP, SUN_ROOF_MASK | PREMIUM_AUDIO_MASK);
    displayCarOptions(myCar);

    setOptions(&myCar, SPORTS_PACKAGE_MASK);
    displayCarOptions(myCar);

    unsetOptions(&myCar, SUN_ROOF_MASK);
    displayCarOptions(myCar);
}

```
</p>
</details>





















