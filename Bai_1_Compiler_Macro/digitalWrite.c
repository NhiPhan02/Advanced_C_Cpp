#include <stdio.h>

typedef enum{
    LOW,
    HIGH
}Status;

typedef enum{
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
}Pin;

#define ESP32       1
#define STM32       2
#define ATmega324   3

#define MCU ESP32
int main(){
    while(1){
        #if MCU == STM32
            void digitalWrite(Pin pin, Status status){
                if(state == HIGH){
                    GPIOA -> BSRR = (1 << pin); //Đặt bit tương ứng để thiết lập
                }
                else{
                    GPIOA -> BSRR = (1 << (pin + 16)); //Đặt bit tương ứng để reset
                }
            }
        #elif MCU == ESP32
            void digitalWrite(Pin pin, Status status){
                if(state == HIGH){
                    GPIOA.out_w1ts = (1 << pin); //Đặt bit tương ứng để thiết lập
                }
                else{
                    GPIOA.out_w1tc = (1 << pin);//Đặt bit tương ứng để reset
                }
            }
        #else
            void digitalWrite(Pin pin, Status status){
                if(state == HIGH){
                    PORTA |= (1 << pin); //Đặt bit tương ứng để thiết lập
                }
                else{
                    PORTA &= ~(1 << pin);//Xóa bit tương ứng để reset
                }
            }
        #endif
    }
}
