#include <stdio.h>
#include <stdarg.h>

typedef enum{
    TEMPERATURE_SENSOR,
    PRESSURE_SENSOR
}SensorType;

void processSensorData(SensorType type, ...){
    va_list args;
    va_start(args, type);

    switch(type){
        case TEMPERATURE_SENSOR:{
            int numArgs = va_arg(args, int);
            int sensorID = va_arg(args, int);
            float temperature = va_arg(args, double); //float được cast thành double
            printf("Temperature Sensor ID: %d, Reading %f degrees\n", sensorID, temperature);
            //Xử lý thêm tham số nếu có:
            if(numArgs > 2){
                char* AdditionalInfo = va_arg(args, char*);
                printf("Additional Info: %s\n", AdditionalInfo);
            }
            break;
        }
        case PRESSURE_SENSOR:{
            int numArgs = va_arg(args, int);
            int sensorID = va_arg(args, int);
            int pressure = va_arg(args, int);
            printf("Pressure Sensor ID: %d, Reading %d PA\n", sensorID, pressure);
            if(numArgs > 2){
                char* unit = va_arg(args, char*);
                printf("Unit: %s\n", unit);
            }
            break;
        }
    }
    va_end(args);
}

int main(){
    processSensorData(TEMPERATURE_SENSOR, 3, 3, 37.5, "Room temperature");
    processSensorData(PRESSURE_SENSOR, 2, 4, 29093);

}