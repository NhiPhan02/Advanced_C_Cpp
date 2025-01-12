// #include <stdio.h>
// int sum(int a, double b){
//     return a + b;
// }
// int main(){
//     int (*ptr)(int, double);
//     return 0;
// }

// #include <stdio.h>
// void sum(int a, double b){
//     return a + b;
// }
// int main(){
//     void (*ptr)(int, double);
//     return 0;
// }

// #include <stdio.h>
// void sum(){
//     return a + b;
// }
// int main(){
//     void (*ptr)();
//     return 0;
// }

// #include <stdio.h>

// int sum(int a, int b){
//     return a + b;
// }
// int main(){
//     int (*ptr)(int, int);
//     return 0;
// }

#include <stdio.h>

void sum(int a, int b) {printf("%d + %d = %d\n", a, b, a+b);}
void subtract(int a, int b) {printf("%d - %d = %d", a, b, a-b);}
void calculate(void (*ptr)(int, int), int a, int b){
    ptr(a, b);
}
int main(){
    //Cách 1:
    // void (*ptr)(int, int) = sum;
    // ptr (2, 3);

    // ptr = subtract;
    // ptr (5, 20);

    //Cách 2:
    // void (*ptr[])(int, int) = {&sum, &subtract};
    // ptr[0](2, 3);
    // ptr[1](5, 20);

    //Cách 3:
    calculate(sum, 2, 3);
    calculate(subtract, 5, 20);
    return 0;

}
