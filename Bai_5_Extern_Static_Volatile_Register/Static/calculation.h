#ifndef CALCULATION_H
#define CALCULATION_H

typedef struct{
    float x1;
    float x2;
}Equation;

static int A, B, C;

void inputCoefficients(int a, int b, int c);

static float calculateDelta();

void result(Equation *equation);
#endif