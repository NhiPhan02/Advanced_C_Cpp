#include <stdio.h>

void count(){
    static int a = 5;
    printf("a = %d\n", a++); //0xa5: 5 - BSS
}

//extern void display(); //lỗi do display là static void display()

int main(){
    count();    //a = 5 -> 0xa5: 6
    count();    //a = 6 -> 0xa5: 7
    count();    //a = 7 -> 0xa5: 8

    //display();
    return 0;
}