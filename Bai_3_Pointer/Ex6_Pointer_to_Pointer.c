#include <stdio.h> 
int main() { 
int a = 10; 
int *ptr1 = &a; // Con trỏ ptr1 trỏ đến biến a 
int **ptr2 = &ptr1; // Con trỏ ptr2 trỏ đến con trỏ ptr1 
printf("Địa chỉ của a = %p. Giá trị của a = %d\n", &a, a); // In ra giá trị của a 
printf("Địa chỉ của ptr1 = %p. Giá trị của ptr1 = %d\n", &ptr1, *ptr1); // In ra giá trị ptr1 trỏ tới (giá trị của a) 
printf("Địa chỉ của ptr2 = %p. Giá trị của ptr2 = %d\n", &ptr2, **ptr2); // In ra giá trị ptr2 trỏ tới (giá trị của a qua ptr1) 
return 0; 
}
