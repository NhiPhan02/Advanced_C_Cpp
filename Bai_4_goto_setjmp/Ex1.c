#include <stdio.h>

int main(){
    int i = 0;
    start:
    if(i >= 5)
        goto end;
    printf("i = %d\n",i);
    i++;
    goto start;


    end:
    return 0;
}