#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "classroom.h"
#include "registration.h"


void initial_registration_show()
{
    struct _Classroom *r=malloc(sizeof(struct _Classroom)*CLASSROOM_MAX_NUMBER);
    int type = 0, capacity = 0, week = 0, session = 0, number, i, j, k;
    bool usage[7 * 13];
    char *s[]={"一教","二教","三教","四教","五教","六教","綜科","億光","光華","共同","科研","先鋒","國百"},*typesetting[]={"\t\t","\n"},buffer_string[32];
    printf("\033[0;0H\033[2J");
    do
    {
        printf("\n教室類型\n0,所有教室\n1,一般教室\n2,E化講桌教室\n3,電腦教室\n4,演講廳\nE,退出\n輸入選項:");
        fflush(stdin);
        scanf("%s", buffer_string);
        printf("\033[0;0H\033[2J");
        type=atoi(buffer_string);
        if (buffer_string[0] == 'E' || buffer_string[0] == 'e')
        {
            printf("退出教室選擇\n");
            return;
        }
        else if(type < 0 || type > 4){
            printf("\n輸入有誤重新輸入\n");
        }
    } while (type < 0 || type > 4);
    printf("\033[0;0H\033[2J");
    printf("\n輸入人數\n0,不限人數\nE,退出\n其他,人數\n輸入選項:");
    fflush(stdin);
    scanf("%s", buffer_string);
    capacity=atoi(buffer_string);
    printf("\033[0;0H\033[2J");
    if (buffer_string[0] == 'E' || buffer_string[0] == 'e')
    {
        printf("\n退出教室選擇\n");
        return;
    }
    if (capacity == 0)
    {
        capacity = 0;
    }

    // 初始化使用情况数组
    for (i = 0; i < 13; i++)
    {
        for (j = 0; j < 7; j++)
        {
            usage[i * 7 + j] = 0;
        }
    }
    printf("\033[0;0H\033[2J");
    do
    {
        week = 0;
        session = 0;
        printf("\n輸入要的課程時間\nK,結束輸入課程時間\nE,退出\n其他,星期1~7,節數1~9,A~D\n輸入要得時間:");
        fflush(stdin);
        scanf("%c,%c", &week, &session);
        printf("\033[0;0H\033[2J");
        if (week == 'E' || week == 'e')
        {
            printf("退出教室選擇\n");
            return;
        }

        if (week == 'K' || week == 'k')
        {
            printf("break\n");
            break;
        }
        week -= 48;
        session -= ((session > 96) * 32 + (session > 64) * 7 + 48);

        if ((week < 1) || (week > 7) || (session < 1) || (session > 13))
        {
            printf("\n輸入有誤重新輸入\n");
        }
        else
        {
            usage[(week - 1) * 7 + session - 1] = true;
        }
    } while (1);
    if (type != 0)
    {
        number = search_classroom(&r, type, capacity, usage);
        k = number;
    }
    else
    {
        struct _Classroom *buffer=malloc(sizeof(struct _Classroom)*CLASSROOM_MAX_NUMBER);
        k = 0;
        for (i = 0; i < 4; i++)
        {
            number = search_classroom(&buffer, i + 1, capacity, usage);
            for(j=0;j<number;j++){
                r[j+k]=buffer[j];
            }
            k += number;
        }
        free(buffer);
        for(i=0;i<k;i++)
            {
                for(j=i;j<k;j++){
                    if(r[j].id<r[i].id)
                        {
                            swp(r[j],r[i]);
                        }
                }
            }
    }
    if(number==0){
        printf("沒有符合的教室");
    }
    number=-1;
    j=0;
    printf("\033[0;0H\033[2J");
    for (i = 0; i < k; i++)
    {

        if(number!=((int)(r[i].id)/10000)-1){
            if((i-j)%show_row!=0){
                printf("\n");
            }
            number=((int)(r[i].id)/10000)-1;
            printf("\n%s:\n",s[number]);
            j=i;
        }
        printf("%06d%15s%s", r[i].id,r[i].nickname,typesetting[((i-j)%show_row)==(show_row-1)]);
    }
    printf("\n");
    int conid;
    bool n;
    do{
    printf("輸入選擇教室的id:");
    fflush(stdin);
    scanf("%s",buffer_string);
    conid=atoi(buffer_string);
    if (buffer_string[0] == 'E' || buffer_string[0] == 'e')
        {
            printf("退出教室選擇\n");
            return;
        }
    for(j=0;j<k;j++){
        if(r[j].id==conid){
            printf("%d\t%s\t%s\n",r[j].id,r[j].wholename);
            n=(update_classroom_usage(&r[j]));
            if(!n){
                printf("更新失敗");
            }
            else{
                printf("登記成功\n\n");
            }
            break;
        }
    }
    if(j>=k){
        printf("輸入的id不存在重新輸入\n");
    }
    else{
        break;
    }
    }while(1);
    // 释放内存
    free(r);

}

/*
int main()
{
    system("chcp 65001");
    initial_registration_show();
    return 0;
}*/
