#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userdata.h"

int main()
{
    system("chcp 65001"); // 將控制台編碼設置為UTF-8
    struct _Userdata userdata_1;
    int i;
    char acc[20],pas[20];

    // Test the read function
    /*
    read_userdata_by_id(&userdata_1,15);
    printf("%s, %s, %s\n", userdata_1.account,
                           userdata_1.password,
                           userdata_1.symbol);
    */

    printf("歡迎使用教室與討論室管理系統!\n\n教職員工人數為500人,一般學生人數為5000人\n\n");
    printf("帳號格式如下:\n\n");
    printf("教職員工:001-500\n");
    printf("一般學生:1120001-1125000\n\n");

    printf("預設密碼格式如下:\n\n");
    printf("教職員工與一般學生的預設密碼皆為1234\n");
    printf("請初次使用本系統的使用者登入後更新密碼!\n\n");

    printf("請輸入帳號:");
    scanf("%s",acc);
    printf("\n請輸入密碼:");
    scanf("%s",pas);

    // 驗證帳號密碼是否正確，若不正確則請使用者重新輸入帳號密碼
    while(!(read_userdata_by_id(&userdata_1, atoi(acc)) && !(strcmp(userdata_1.password,pas)))){
        printf("\n帳號密碼錯誤!\n\n");
        printf("請輸入帳號:");
        scanf("%s",acc);
        printf("\n請輸入密碼:");
        scanf("%s",pas);
    }

    // 判斷密碼是否為預設密碼1234，若為預設密碼則請使用者更新密碼
    if(!strcmp(userdata_1.password,"1234")){
        printf("\n請更改密碼!\n");
        printf("請輸入密碼:");
        scanf("%s",pas);
        strcpy(userdata_1.password, pas);
        update_userdata(&userdata_1);
    }

    return 0;
}
