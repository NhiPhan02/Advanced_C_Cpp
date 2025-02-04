#include <stdio.h>

int main(){
    int key = 0;
    main_menu:
    
    do{
        printf("1. Menu chinh\n");
        printf("2. ...\n");
        printf("3. ...\n");
        printf("Nhap cac tuy chon: \n");  
        scanf("%d", &key);
    }while(key != 1);

    switch(key){
        case 1:
            printf("4. ...\n");
            printf("5. Ket thucc\n");
            printf("6. Quay lai main menu\n");
            printf("Nhap cac tuy chon: ");  scanf("%d", &key);
            switch(key){
                case 4:
                    
                case 5: goto exit_prog;
                
                case 6: goto main_menu;
                
            }
        case 2:

        case 3:

        break;
    }
    exit_prog:
    return 0;
}