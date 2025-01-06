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

