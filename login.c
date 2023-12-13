#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdata.h"

int main()
{
    system("chcp 65001");
    struct Userdata userdata_table[5500];
    int i,acc,pas;
    char box[20],text[20];

    printf("歡迎使用教室與討論室管理系統!\n\n教職員工人數為500人,一般學生人數為5000人\n\n");
    printf("帳號格式如下:\n\n");
    printf("教職員工:001-500\n");
    printf("一般學生:1120001-1125000\n\n");
    printf("請輸入帳號:");
    scanf("%d",&acc);

    while((acc>500&&acc<1120001)||(acc<0)||(acc>1125000)){
        printf("輸入帳號格式錯誤!\n請重新輸入!\n\n");
        printf("請輸入帳號:");
        scanf("%d",&acc);
    }

    read_userdata_by_row(userdata_table,acc);
/*
    if(){
        printf("\n請更改密碼!\n");
        printf("請輸入密碼:");
        scanf("%s",pas);
    }
    else{
        printf("\n請輸入密碼:");
        scanf("%s",pas);
        while(){
            printf("輸入密碼錯誤!\n請重新輸入!\n\n");
            printf("請輸入密碼:");
            scanf("%s",pas);
        }
    }
*/
    return 0;
}
