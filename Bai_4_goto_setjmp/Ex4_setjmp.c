// #include <stdio.h>
// #include <setjmp.h>

// int exception;
// jmp_buf buf;
// int main()
// {
//     exception = setjmp(buf);

//     if (exception == 0){
//         printf("Exception = %d\n", exception);
//     }
//     else if (exception == 2){
//         printf("Exception = %d\n", exception);       
//     }
//     longjmp(buf, 0);

//     return 0;
// }


#include <stdio.h>
#include <setjmp.h>


jmp_buf buf;
int exception;
#define TRY if ((exception = setjmp(buf)) == 0)
#define CATCH(x) else if (exception == x)
#define THROW(x) longjmp(buf, x)

int main()
{
    TRY
    {
        printf("Exception = %d\n", exception);
    }
    CATCH(2)
    {
        printf("Exception = %d\n", exception);       
    }
    THROW(2);

    return 0;
}