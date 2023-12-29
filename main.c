#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "classroom.h"
#include "userdata.h"

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
    printf("首次登入的預設密碼為 1234。");

    printf("\n");

    printf("\n公告---------------------------\n");

    // 請在這裡載入並顯示公告

    printf("---------------------------------\n");

    printf("\n");

    user = login();

    return 0;
}