#include <stdio.h>
#include <math.h>
#include "calculation.h"

//extern float calculateDelta;

int main(){
    Equation ketqua;
    inputCoefficients(1, -3, 2);
    result(&ketqua);
    printf("x1 = %f\n", ketqua.x1);
    printf("x2 = %f\n", ketqua.x2);

    //printf("delta = %d\n", calculateDelta());
    return 0;
}