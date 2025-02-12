#include <stdio.h>
#include "File1.h"
#include "File2.h"

// extern int a;
// extern int b;

// extern void display1();
// extern void display2();

int main(){
    a = 1;
    printf("a = %d\n", a);

    b = 2;
    printf("b = %d\n", b);

    display1();
    display2();

    return 0;
}