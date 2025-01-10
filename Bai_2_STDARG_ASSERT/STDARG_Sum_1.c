#include <stdio.h>
#include <stdarg.h>

//Cách 2: Cách sau đây không cần biết trước số lượng tham số không xác định truyền vào.
//Nhược điểm là nếu giữa chuỗi truyền có giá trị 0 thì hàm sẽ dừng ở vị trí đó
#define tong(...) sum(__VA_ARGS__, 0)

void sum(int count, ...){
    va_list args;
    va_start(args, count);
    int result = count;
    int value;
    while((value = va_arg(args, int)) != 0){
        result += value;
    }
    printf("Kết quả là: %d", result);
    
    va_end(args);
}
int main(){
    tong(4, 8, 10, 2, 3);
}


