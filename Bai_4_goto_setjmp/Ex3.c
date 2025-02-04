/*****************************************************
 * @file .c
 * @brief Hiển thị các ký tự trên LED ma trên 8x8 theo 3 mẫu câu
 * @details Chương trình này sử dụng các ý tự "HI", "FASHION", và "SUITABLE" 
 *          và hiển thị chúng trên ma trận 8x8 LED. Người dùng có thể dừng 
 *          chương trình bằng cách nhấn phím 'M'.
 * @version 1.0
 * date 2025-11-12
******************************************************/

#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

//Hàm delay theo giây, ví dụ delay(2000) ->2s
void delay(unsigned int miliseconds){
    unsigned int start = clock();
    while (clock() - start < miliseconds);
}

char first_sentence[] = "HI";
char second_sentence[] = "FASHION";
char third_sentence[] = "SUITABLE";

int letter_H[8][8] = 
{
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,1,1,1,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
    {1,0,0,0,1,0,0,0},
};

int letter_I[8][8] =
{
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1,1},
};

int letter_F[8][8] = 
{
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
};

int letter_S[8][8] = 
{
    {0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,0},
};

//mô phỏng nút nhấn bấm dừng chương trình
int button = 0;

//khởi tạo kiểu liệt kê đại diện cho 3 câu cần hiển thị
typedef enum{
    FIRST,
    SECOND,
    THIRD
}Sentence;

//hàm in ký tự ra LED ma trận 8x8
void print_char(const int matrix[8][8]){
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (matrix[i][j] == 1){
                printf("*");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

bool is_stop_key_pressed()
{
    //Kiểm tra xem có phím nào được nhấn
    if (kbhit())
    {
        char button = getch();
        if (button == 'M' || button == 'm')
            return true;
    }

    return false;
}

int main()
{
    //Biến 'sentence' được khởi tạo với giá trị 'FIRST', đại diện cho câu đầu tiên cần hiển thị
    Sentence sentence = FIRST;

    while(1)
    {
        //Kiểm tra ký tự 'M' được nhấn
        if (is_stop_key_pressed())
        {
            printf("Stop\n");
            break;
        }

        switch (sentence)
        {
            case FIRST:
                for (int i=0; i<sizeof(first_sentence); i++)
                {
                    if(first_sentence[i] == 'H'){
                        print_char(letter_H);
                    }
                    else if (first_sentence[i] == 'I'){
                        print_char(letter_I);
                    }

                    if(button == 1) goto exit_loops;
                }
                printf("First sentence is done\n");
                printf("\n");
                delay(2000);
                goto logic;
            case SECOND:
                for(int i=0; i<sizeof(second_sentence); i++)
                {
                    if (second_sentence[i] == 'F'){
                        print_char(letter_F);
                    }
                    else if(second_sentence[i] == 'A'){
                        print_char(letter_S);
                    }

                    if (button == 1) goto exit_loops;
                }
                printf("Second sentence is done\n");
                printf("\n");
                delay(2000);
                goto logic;
            case THIRD:
                for (int i=0; i<sizeof(third_sentence); i++)
                {
                    if(third_sentence[i] == 'S'){
                        print_char(letter_S);
                    }
                    else if (third_sentence[i] == 'U'){
                        //in ra ký tự 'U'
                    }

                    if (button == 1) goto exit_loops;
                }

                printf("Third sentence is done\n");
                printf("\n");
                delay(2000);
                goto logic;
        }
        logic: 
            if (sentence == FIRST)          sentence = SECOND;
            else if (sentence == SECOND)    sentence = THIRD;
            else if (sentence == THIRD)     sentence = FIRST;
            goto exit;

        exit_loops:
            printf("Stop\n");
            break;
        
        exit:;
    }

    return 0;
}
