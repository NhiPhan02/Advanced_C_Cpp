#include <stdio.h>
#include <time.h>

int main(){
    clock_t start_time = clock();
    register int i;
    for (i=0; i<2000000; i++){

    }
    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time))/CLOCKS_PER_SEC;
    printf ("Thời gian chạy: %f\n", time_taken);
    return 0;
}