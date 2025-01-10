#include <stdio.h>
#include <stdarg.h>

//Cách 1: Cách làm sau đây sử dụng biến count cho biết số lượng phần tử không xác định.
//Nhược điểm của cách làm này là phải biết số lượng count trước
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



