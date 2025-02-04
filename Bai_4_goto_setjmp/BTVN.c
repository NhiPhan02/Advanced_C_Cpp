#include <stdio.h>
#include <setjmp.h>

typedef enum {
    NO_ERROR, 
    FILE_ERROR, 
    NETWORK_ERROR, 
    CALCULATION_ERROR 
}ErrorCodes;

jmp_buf buf;
int exception;
char* error_message = NULL;
int error_code;

#define TOSTRING(x) #x

#define TRY if((exception = setjmp(buf)) == 0)
#define CATCH(error) else if(exception == error)
#define THROW(error, message){          \
    error_message = TOSTRING(message);  \
    longjmp(buf, error);                \
}


void readFile() {
    printf("\nĐọc file...\n");
    fflush(stdin);
    scanf("%d", &error_code);
    if(error_code == FILE_ERROR){
        THROW(FILE_ERROR, Lỗi đọc file: File không tồn tại.);
    }
}

void networkOperation() {
    printf("\nKiểm tra Network Operation...\n");
    fflush(stdin);
    scanf("%d", &error_code);
    if(error_code == NETWORK_ERROR){ 
        THROW(NETWORK_ERROR, Lỗi Network.);
    }
}
void calculateData() {
    printf("\nCalculation Data...\n");
    fflush(stdin);
    scanf("%d", &error_code);
    if(error_code == CALCULATION_ERROR){ 
        THROW(CALCULATION_ERROR, Lỗi Calculation.);
    }
}


int main(){
    
    TRY {
File:       readFile();             //Nhập 1 thì Kiểm tra lại, nhập các số khác thì chạy tiếp
Net:        networkOperation();     //Nhập 2 thì Kiểm tra lại, nhập các số khác thì chạy tiếp
Calcu:      calculateData();        //Nhập 3 thì Kiểm tra lại, nhập các số khác thì chạy tiếp
    } 
    CATCH(FILE_ERROR) {
        printf("%s\n", error_message);
        printf("Đọc file lại\n");
        goto File;
        } 
    
    CATCH(NETWORK_ERROR) {
        printf("%s\n", error_message);
        printf("Kiểm tra Network Operation lại\n");
        goto Net;
        } 
    
    CATCH(CALCULATION_ERROR) {
        printf("%s\n", error_message);
        printf("Calculation Data lại\n");
        goto Calcu;
        } 
    Exit_prog:
    return 0;
}
