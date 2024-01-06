#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "classroom.h"
#include "userdata.h"
#include "bulletin_board.h"
#include "communication.h"

#define MENU_NUMBER 4

int main(){

    system("chcp 65001");
    struct _Userdata user;

    int i, j, k;

    printf("歡迎使用教室使用登記系統！\n");
    printf("當前帳號數量:5500\n");

    printf("\n");

    printf("登入帳號為員工編號或學號\n");
    printf("教職員工:001-500\n");
    printf("一般學生:1120001-1125000\n");
    printf("首次登入的預設密碼為 1234。\n");

    printf("\n");

    printf("\n公告-----------------------------\n");

    // show all of the notice
    bulletinshow();

    printf("\n---------------------------------\n");

    printf("\n");

    user = login();
    printf("\n");
    printf("%s, 登入成功!\n", user.account);

    int unread_count = countunread(user);
    if(unread_count != 0) printf("您有 %d 則未讀訊息，請記得確認重要訊息!\n", unread_count);
    else printf("您沒有未讀訊息!\n");

    // to store the options in the menu
    char *menu[MENU_NUMBER] = {
        "更改登入密碼",
        "查看訊息",
        "傳送訊息",
        "期初教室登記系統"
    };

    while(true){

        printf("\n---------------------------------\n");

        printf("\n");

        printf("功能選單:\n");
        for (i = 0; i < MENU_NUMBER; i++){
            printf("%d.\t", i+1);
            printf("%s\n", menu[i]);
        }

        printf("\n");
        printf("請輸入選單編號:");
        char user_input_int;
        fflush(stdin);
        scanf("%c", &user_input_int);

        switch (user_input_int){
            case '1': // 更改登入密碼
                printf("\n%c.%s\n\n", user_input_int, menu[user_input_int]);
                password_modify(&user);
                printf("\n密碼更改完成，請重新登入");
                return 0;
            
            case '2': // 查看訊息
                printf("\n%c.%s\n\n", user_input_int, menu[user_input_int]);


            default:
                break;
        }

    }

    return 0;
}
