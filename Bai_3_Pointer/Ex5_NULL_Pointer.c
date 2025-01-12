#include <stdio.h>

int main(){
    int *ptr = NULL;
    if (ptr == NULL)
        printf("ptr = NULL\n");
    else    
        printf("ptr khác NULL\n");
    
    int a = 5;
    ptr = &a;
    *ptr = 30;
    ptr = NULL;
    printf("a ban đầu = 5. Hiện tại a = %d\n", a);
}