#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;
int exception;

#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(x) else if(exception == x)
#define THROW(x) longjmp(buf, x)

double divide (int a, int b){
    if(a == 0 && b == 0)
        THROW(1);
    else if (b == 0)
        THROW(2);
    return (double)a/b;
}
int main(){
    TRY    
        printf("Ket qua la : %f\n", divide (3,0));
    CATCH(1)
        printf("a va b = 0\n");
    CATCH(2)
        printf("b = 0\n");
    printf("Hello world\n");
}