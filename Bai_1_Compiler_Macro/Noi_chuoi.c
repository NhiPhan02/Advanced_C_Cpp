#include <stdio.h>

#define CONCAT(a,b) a##b
#define TO_STRING(x) #x         //=>  "x"

int main()
{
    int xy = 1000;

    //Sử dụng define để nối chuỗi
    printf("Noi chuoi x va chuoi y, ket qua la: %d\n", CONCAT(x,y));

    //Sử dụng macro để chuẩn hóa chuỗi
    printf("Chuoi duoc chuan hoa la: %s\n", TO_STRING(abc) );
}