#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdata.h"

// 先判斷密碼是否為預設密碼1234
// 若是 則需改新密碼 且不能與預設密碼相同
// 否則 驗證密碼是否正確

int main()
{
    system("chcp 65001");
    struct _Userdata userdata_1;
    int i;
    char box[20],text[20],acc[20],pas[20];

    printf("歡迎使用教室與討論室管理系統!\n\n教職員工人數為500人,一般學生人數為5000人\n\n");
    printf("帳號格式如下:\n\n");
    printf("教職員工:001-500\n");
    printf("一般學生:1120001-1125000\n\n");

    printf("請輸入帳號:");
    scanf("%s",acc);
    printf("\n請輸入密碼:");
    scanf("%s",pas);
    while(!(read_userdata_by_row(&userdata_1, atoi(acc)) && (strcmp(userdata_1.password, pas)))){
        printf("\n帳號密碼錯誤!\n\n");
        printf("請輸入帳號:");
        scanf("%s",acc);
        printf("\n請輸入密碼:");
        scanf("%s",pas);
    }

    if(strcmp(userdata_1.password,"1234")){
        printf("\n請更改密碼!\n");
        printf("請輸入密碼:");
        scanf("%s",pas);
        strcpy(userdata_1.password, pas);
        update_userdata(&userdata_1);
    }

    return 0;
}
