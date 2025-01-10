#include <stdio.h>
#include <stdlib.h>
#include "test.h"

//Create size array
#define SIZE 20
int array[SIZE];

#define CREATE_FUNC(name,cmd)   \
void name()                     \
{                               \
    printf(cmd);                \
}

CREATE_FUNC(test1,"This is function 1\n");
CREATE_FUNC(test2,"This is function 2\n");

//create the function
void test(){
    printf("Hello World\n");

}




int SIZE2 = 30;

int main(){
//    #undef SIZE;
//    SIZE = 10;
    display();

    #ifndef SIZE1
    #define SIZE1 30    
    int a = 5; 
    printf("a = %d\n", a);
    #endif

    int array2[SIZE2];
    
    
    test1();
    return 0;
}