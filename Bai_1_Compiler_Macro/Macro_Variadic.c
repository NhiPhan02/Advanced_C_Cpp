#include <stdio.h>

// //Macro variadic
// #define sum(a,b) a+b

// //Cách 2: Chưa xử lý được trường hợp có số 0 trong chuỗi
// #define sum1(...)                   \
// int arr[] = {__VA_ARGS__, 0};       \
// int tong = 0;                       \
// int i = 0;                          \
// while(arr[i] != 0){                 \
//     tong += arr[i];                 \
//     i++;                            \
// }                                   \
// printf("Tong la: %d", tong);

//Cách 3: 
#define COUNT_ARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int))
/*
 * COUNT_ARGS(1, 2, 3)
 * sizeof((int[]){1, 2, 3}) = 12 byte
 * sizeof(int) = 4
 * => n = 3 phần tử
 */

#define sum2(...)                   \
int arr[] = {__VA_ARGS__};          \
int tong = 0;                       \
int n = COUNT_ARGS(__VA_ARGS__);    \
int i = 0;                          \
while (i != n){                     \
    tong += arr[i];                 \
    i++;                            \
}                                   \
printf("Tổng là: %d", tong);        


int main()
{
     int a, b, c;
    // printf("Nhap vao a, b, c: "); scanf("%d %d %d", &a, &b, &c);

    // printf("Cac so da nhap la: %d %d %d\n", a, b, c);

    //sum1(1, 2, 4, 8, 9, 6);

    sum2(1, 2, 1, 0, 8, 9, 6);
    return 0;

}