/*#include <stdio.h>
#include <stdint.h>
#define COLOR_RED 0	
#define COLOR_BLUE 1
#define COLOR_BLACK 2
#define COLOR_WHITE 3
#define POWER_100HP 0
#define POWER_150HP 1
#define POWER_200HP 2
#define ENGINE_1_5L 0
#define ENGINE_2_0L 1

typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;



#define SUNROOF_MASK 1 << 0     // 0001
#define PREMIUM_AUDIO_MASK 1 << 1 // 0010
#define SPORTS_PACKAGE_MASK 1 << 2 // 0100
// Thêm các bit masks khác tùy thuộc vào tùy chọn


typedef struct {
    uint8_t additionalOptions : 3; // 3 bits thấp nhất cho các tùy chọn bổ sung
    CarColor color : 2;
    CarPower power : 2;
    CarEngine engine : 1;
    
} CarOptions;



void configureCar(CarOptions *car, CarColor color, CarPower power, CarEngine engine, uint8_t options) {
    car->color = color;
    car->power = power;
    car->engine = engine;
    car->additionalOptions = options;
}

void setOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions |= optionMask;
}

void unsetOption(CarOptions *car, uint8_t optionMask) {
    car->additionalOptions &= ~optionMask;
}


void displayCarOptions(const CarOptions car) {
    const char *colors[] = {"Red", "Blue", "Black", "White"};
    const char *powers[] = {"100HP", "150HP", "200HP"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("Car Configuration: \n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUNROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}

int main() {
    CarOptions myCar;
    configureCar(&myCar, COLOR_WHITE, POWER_150HP, ENGINE_2_0L, 0); 
	printf("myCar = %d\n", myCar); // = 1011 1000

    

    setOption(&myCar, SUNROOF_MASK);
//  setOption(&myCar, PREMIUM_AUDIO_MASK);    
    setOption(&myCar, SPORTS_PACKAGE_MASK);
    displayCarOptions(myCar);

    unsetOption(&myCar, PREMIUM_AUDIO_MASK); 
    displayCarOptions(myCar);

    printf("size of my car: %d\n", sizeof(CarOptions));

    return 0;
}
*/











#include <stdio.h>
#include <stdint.h>

#define COLOR_RED 0
#define COLOR_BLACK 1
#define COLOR_WHITE 2
#define COLOR_BLUE 3
#define POWER_100HP 0
#define POWER_150HP 1
#define POWER_200HP 2
#define ENGINE_1_5L 0
#define ENGINE_2_0L 1
#define SUN_ROOF_MASK 1 << 0
#define PREMIUM_AUDIO_MASK 1 << 1
#define SPORTS_PACKAGE_MASK 1 << 2

typedef uint8_t CarColor;
typedef uint8_t CarPower;
typedef uint8_t CarEngine;

//Các bit của additionalOptions sẽ nằm ở bit 210
typedef struct{
    uint8_t additionalOptions : 3;
    CarColor color : 2;
    CarPower power : 2;
    CarEngine engine : 1;
}CarOptions;

void configureCar(CarOptions *car, CarColor color, CarEngine engine, CarPower power, uint8_t options){
    car->color = color;
    car->engine = engine;
    car->power = power;
    car->additionalOptions = options;
} 

void setOptions(CarOptions *car, uint8_t options){
    car->additionalOptions |= options;
}

void unsetOptions(CarOptions *car, uint8_t options){
    car->additionalOptions &= ~ options;
}

void displayCarOptions(CarOptions car){
    const char *colors[] = {"Red", "Black", "White", "Blue"};
    const char *powers[] = {"100Hp", "150Hp", "200Hp"};
    const char *engines[] = {"1.5L", "2.0L"};

    printf("\nCar Options:\n");
    printf("Color: %s\n", colors[car.color]);
    printf("Power: %s\n", powers[car.power]);
    printf("Engine: %s\n", engines[car.engine]);
    printf("Sunroof: %s\n", (car.additionalOptions & SUN_ROOF_MASK) ? "Yes" : "No");
    printf("Premium Audio: %s\n", (car.additionalOptions & PREMIUM_AUDIO_MASK) ? "Yes" : "No");
    printf("Sports Package: %s\n", (car.additionalOptions & SPORTS_PACKAGE_MASK) ? "Yes" : "No");
}

int main(){
    CarOptions myCar;
    configureCar(&myCar, COLOR_BLACK, ENGINE_1_5L, POWER_150HP, SUN_ROOF_MASK | PREMIUM_AUDIO_MASK);
    displayCarOptions(myCar);

    setOptions(&myCar, SPORTS_PACKAGE_MASK);
    displayCarOptions(myCar);

    unsetOptions(&myCar, SUN_ROOF_MASK);
    displayCarOptions(myCar);
}

