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