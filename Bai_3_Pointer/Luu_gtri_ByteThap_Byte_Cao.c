#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char const *argv[])
{
    uint16_t *arr = (uint16_t*)malloc(3*sizeof(uint16_t));

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;

    for (int i=0; i<6; i++)
    {
        printf("addr of element %d: %p - value: %d\n", i, (uint8_t*)arr + i, *((uint8_t*)arr + i));
    }

    return 0;
}