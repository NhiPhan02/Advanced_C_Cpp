#include <stdio.h>
#include <stdint.h>
#define LED1 1 << 0 //0b0000 0001
#define LED2 1 << 1 //0b0000 0010
#define LED3 1 << 2 //0b0000 0100
#define LED4 1 << 3 //0b0000 1000

void enableLed(uint8_t *GPIO_PORT, uint8_t LED){
    *GPIO_PORT |= LED;
}

void disableLed(uint8_t *GPIO_PORT, uint8_t LED){
    *GPIO_PORT &= ~LED;
}

int main(){
    uint8_t GPIO_PORT = 0;

    //bật LED
    printf("Enable LED 1, 2\n");
    enableLed(&GPIO_PORT, LED1 | LED2);
    if(GPIO_PORT & LED1) 
        printf("LED 1 bật\n");
    else                 
        printf("LED 1 tắt\n");
    if(GPIO_PORT & LED2) 
        printf("LED 2 bật\n");
    else                 
        printf("LED 2 tắt\n");
    if(GPIO_PORT & LED3) 
        printf("LED 3 bật\n");
    else                 
        printf("LED 3 tắt\n");

    printf("Disable LED 2\n");
    disableLed(&GPIO_PORT, LED2);
    if(GPIO_PORT & LED1) 
        printf("LED 1 bật\n");
    else                 
        printf("LED 1 tắt\n");
    if(GPIO_PORT & LED2) 
        printf("LED 2 bật\n");
    else                 
        printf("LED 2 tắt\n");
    if(GPIO_PORT & LED3) 
        printf("LED 3 bật\n");
    else                 
        printf("LED 3 tắt\n");

    return 0;
}