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