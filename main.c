#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "classroom.h"
#include "userdata.h"
#include "bulletin_board.h"
#include "communication.h"
#include "apple.h"


int main(){

    system("chcp 65001");
    struct _Userdata user;
    // flag for while for user input
    bool flag = true, flagi, flagj, flagk;

    int i, j, k;

    
    printf("\033[0;0H\033[2J");
    printf("歡迎使用教室使用登記系統！\n");
    printf("當前帳號數量:5500\n");

    printf("\n");

    printf("登入帳號為員工編號或學號\n");
    printf("教職員工:001-500\n");
    printf("一般學生:1120001-1125000\n");
    printf("首次登入的預設密碼為 1234。\n");

    printf("\n");

    printf("\n公告-----------------------------\n\n");

    // show all of the notice
    bulletinshow();

    printf("\n---------------------------------\n");

    printf("\n");

    user = login();
    printf("\n");

    // to store all the messages
    struct _Message message_list[128];
    int message_count;
    // to store the options in the menu
    char *menu[] = {
        "退出系統",
        "更改登入密碼",
        "查看訊息",
        "查看已傳送的訊息",
        "傳送訊息",
        "期初教室登記系統",
        "管理員系統",
        "???????????"
    };

    char *admin_menu[] = {
        "退出",
        "重設用戶密碼",
        "登記公告"
    };

    do{
        flag = true;

        printf("\033[0;0H\033[2J");
        printf("%s, 登入成功!\n", user.account);

        int unread_count = countunread(user);
        if(unread_count != 0) printf("您有 %d 則未讀訊息，請記得確認重要訊息!\n", unread_count);
        else printf("您沒有未讀訊息!\n");

        printf("\n---------------------------------\n");

        printf("\n");

        printf("功能選單:\n");
        for (i = 0; i < sizeof(menu) / sizeof(menu[0]); i++){
            printf("%d.\t", i);
            printf("%s\n", menu[i]);
        }

        printf("\n");
        printf("請輸入選單編號:");
        char user_input_char;
        int user_input_int;
        fflush(stdin);
        scanf("%c", &user_input_char);

        printf("\033[0;0H\033[2J");
        printf("\n---------------------------------\n\n");
        switch (user_input_char){
            case '0': // 退出系統
                printf("正在退出系統");
                return 0;

            case '1': // 更改登入密碼
                printf("\n%c.%s\n\n", user_input_char, menu[1]);
                password_modify(&user);
                printf("\n密碼更改完成，請重新登入");
                return 0;
            
            case '2': // 查看訊息
                printf("\n%c.%s\n\n", user_input_char, menu[2]);
                message_count = readmessage(message_list, user, "read");
                // printf("%d", message_count);
                
                do{ // flagi
                    flagi = true;
                    listmessage(message_list, message_count);
                    printf("您有 %d 則新訊息，共 %d 則訊息\n", unread_count, message_count);
                    printf("\n");
                    printf("請輸入訊息編號，或輸入 0 退出: ");
                    scanf("%d", &user_input_int);

                    if(user_input_int == 0) break;
                    if(user_input_int > message_count || user_input_int < 0){
                        printf("輸入錯誤，請重新輸入");
                        continue;
                    }

                    printf("\033[0;0H\033[2J");
                    viewmessage(message_list[user_input_int-1]);
                    do{
                        flagj = false;
                        printf("\n");
                        printf("訊息選項: \n0. 退出\n1. 回覆\n2. 標記為未讀\n3. 刪除訊息\n");

                        printf("請輸入訊息選項代號: ");
                        fflush(stdin);
                        scanf("%c", &user_input_char);
                        switch (user_input_char){
                            case '0': // 退出
                                printf("\033[0;0H\033[2J");
                                printf("退出訊息\n");
                                printf("\n---------------------------------\n\n");
                                break;

                            case '1': // 回覆
                                writemessage(user, message_list[user_input_int-1].sender);
                                break;

                            case '2': // 標記為未讀
                                msrkasunread(user, user_input_int);
                                message_list[user_input_int-1].read = false;
                                printf("\033[0;0H\033[2J");
                                printf("已標記為未讀\n");
                                printf("\n---------------------------------\n\n");
                                break;

                            case '3': // 刪除訊息
                                deletemessage(user, user_input_int);
                                deleteMessageinarray(message_list, message_count, user_input_int-1);
                                message_count--;
                                printf("\033[0;0H\033[2J");
                                printf("已刪除訊息\n");
                                printf("\n---------------------------------\n\n");
                                break;
                            
                            default:
                                printf("\033[0;0H\033[2J");
                                printf("輸入格式錯誤，請重新輸入\n");
                                printf("\n---------------------------------\n\n");
                                flagj = true;
                                break;
                        }
                    }while (flagj);


                }while(flagi);

                break;
            
            case '3': // 查看已傳送的訊息
                printf("\n%c.%s\n\n", user_input_char, menu[3]);
                message_count = readmessage(message_list, user, "log");
                // printf("%d", message_count);
                
                do{ // flagi
                    flagi = true;
                    logmessage(message_list, message_count);
                    printf("共 %d 則訊息\n", message_count);
                    printf("\n");
                    printf("請輸入訊息編號，或輸入 0 退出: ");
                    scanf("%d", &user_input_int);

                    if(user_input_int == 0) break;
                    if(user_input_int > message_count || user_input_int < 0){
                        printf("輸入錯誤，請重新輸入");
                        continue;
                    }

                    printf("\033[0;0H\033[2J");
                    viewmessage(message_list[user_input_int-1]);
                    do{
                        flagj = false;
                        printf("\n");
                        printf("訊息選項: \n0. 退出\n1. 再傳送\n2. 刪除訊息\n");

                        printf("請輸入訊息選項代號: ");
                        fflush(stdin);
                        scanf("%c", &user_input_char);
                        switch (user_input_char){
                            case '0': // 退出
                                printf("\033[0;0H\033[2J");
                                printf("退出訊息\n");
                                printf("\n---------------------------------\n\n");
                                break;

                            case '1': // 回覆
                                writemessage(user, message_list[user_input_int-1].sender);
                                break;

                            case '2': // 刪除訊息
                                deletemessage(user, user_input_int);
                                deleteMessageinarray(message_list, message_count, user_input_int-1);
                                message_count--;
                                printf("\033[0;0H\033[2J");
                                printf("已刪除訊息\n");
                                printf("\n---------------------------------\n\n");
                                break;
                            
                            default:
                                printf("輸入格式錯誤，請重新輸入\n");
                                flagj = true;
                                break;
                        }
                    }while (flagj);


                }while(flagi);

                break;

            case '4': // 傳送訊息
                printf("\n%c.%s\n\n", user_input_char, menu[4]);
                writemessage(user, NULL);
                break;

            case '5': // 期初教室登記系統
                break;

            case '6': // 管理員系統
                if(user.symbol[0] == 'm'){
                    do
                    {
                        flagi = false;
                        printf("\n---------------------------------\n");

                        printf("\n");

                        printf("功能選單:\n");
                        for (i = 0; i < sizeof(admin_menu) / sizeof(admin_menu[0]); i++){
                            printf("%d.\t", i);
                            printf("%s\n", admin_menu[i]);
                        }

                        printf("\n");
                        printf("請輸入選單編號:");
                        fflush(stdin);
                        scanf("%c", &user_input_char);

                        switch (user_input_char){
                        case '0':
                            printf("正在退出\n");
                            break;
                        
                        case '1':
                            printf("\n---------------------------------\n");
                            printf("\n%c.%s\n\n", user_input_char, admin_menu[1]);
                            admin_resetpassword();
                            break;
                        
                        case '2':
                            printf("\n%c.%s\n\n", user_input_char, admin_menu[2]);
                            bulletinwrite(user.account);
                            break;

                        default:
                            break;
                        }

                    } while (flagi);
                    
                }
                else{
                    printf("權限不足，存取遭拒\n");
                    printf("按任意鍵繼續...\n");
                    fflush(stdin);
                    getchar();
                }
                break;
            
            case '7':
                badapple();

            default:
                printf("輸入錯誤，請重新輸入\n");
                break;
        }

    }while(true);

    return 0;
}
