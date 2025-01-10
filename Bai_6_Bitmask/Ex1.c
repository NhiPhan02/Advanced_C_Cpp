#include <stdio.h>
#include <stdint.h>

//Ví dụ shift left bitwise
                       //                         0      1
#define GENDER    1 << 0  //bit 0: giới tính     nữ     nam   0b0000 0001
#define SHIRT     1 << 1  //bit 1: áo thun      không   có    0b0000 0010
#define HAT       1 << 2  //bit 2: nón          không   có    0b0000 0100
#define SHOES     1 << 3  //bit 3: giày         không   có    0b0000 1000
#define FEATURE1  1 << 4  //bit 4: tính năng 1  không   có    0b0001 0000
#define FEATURE2  1 << 5  //bit 5: tính năng 2  không   có    0b0010 0000
#define FEATURE3  1 << 6  //bit 6: tính năng 3  không   có    0b0100 0000
#define FEATURE4  1 << 7  //bit 7: tính năng 4  không   có    0b1000 0000


//Dùng | để ứng dụng bitmask
void enableFeature(uint8_t *options, uint8_t feature){
    *options |= feature;
}
// options   = 0bxxxx xxxx
// feature   = 0b0000 0010
// OR        = 0bxxxx xx1x
// feature   = 0b0000 1000
// OR        = 0bxxxx 1x1x

//Dùng AND và NOT để ứng dụng bitmask
void disableFeature(uint8_t *options, uint8_t feature){
    *options &= ~feature;
}
// options   = 0bxxxx xxxx
// ~ feature = 0b1111 1110
// AND       = 0bxxxx xxx0
// ~ feature = 0b1111 0111
// AND       = 0bxxxx 0xx0

uint8_t isFeatureEnable(uint8_t options, uint8_t feature){
    return((options & feature) != 0); 
    //true:  feature ON
    //false: feature OFF
}

void listSelectedFeatures(uint8_t options){
    printf("Selected Features: \n");

    const char *featuresName[] = {
        "Gender",
        "Shirt",
        "Hat",
        "Shoes",
        "Feature 1",
        "Feature 2",
        "Feature 3",
        "Feature 4"
    };
    
    for (int i = 0; i < 8; i++){
        if((options >> i) & 1){
            printf("%s\n", featuresName[i]);
        }
    }
}

int main(){
    uint8_t options = 0;
    enableFeature(&options, GENDER | HAT | SHOES);
    if(isFeatureEnable(options, GENDER)) 
        printf("GENDER được chọn\n");
    else
        printf("GENDER không được chọn\n");

    if(isFeatureEnable(options, HAT))  
        printf("HAT được chọn\n");
    else                            
        printf("HAT không được chọn\n");
    disableFeature(&options, HAT);
    listSelectedFeatures(options);
    return 0;
}