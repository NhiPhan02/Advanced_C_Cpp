#include <stdio.h>
#include <stdarg.h>

//Cách 3: Cách sau đây không cần biết trước số lượng tham số không xác định truyền vào.
//Nhược điểm là sẽ sai nếu chuỗi có số 10.
//Do mã ASCII của '\n' = 10
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