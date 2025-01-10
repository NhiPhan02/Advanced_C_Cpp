#include <stdio.h>
#include <assert.h>
double divide (int a, int b){
    assert(b != 0 && "b phải khác 0");
    return (double)a/b;
}

int main(){
    int x = 8;
    assert(x == 8 && "x không bằng 8"); 

    printf("a/b = %f", divide(6,0));
    return 0;
}