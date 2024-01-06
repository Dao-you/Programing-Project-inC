#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "bulletin_board.h"


char *file_location[]={
    "./Bulletin_Board/BulletinBoard.csv", 
    "./Bulletin_Board/log.csv", 
    "./Bulletin_Board/copy.csv"
};

struct bulletin
{
    int p_time[3], e_time[3];
    char user[32], bulletin[1024];
};


void bulletinconfirm()
{
    FILE *f[3];
    int i;
    if((f[1]=fopen(file_location[1],"a+"))==NULL)
       {
           f[1]=fopen(file_location[1],"w+");
       }
    if((f[0]=fopen(file_location[0],"a+"))==NULL)
       {
           f[0]=fopen(file_location[0],"w+");
           fclose(f[0]);
           return;
       }
    char s[1024],buffer[1024],*token;
    time_t t;
    struct tm *timeinfo;
    struct bulletin re;
    time(&t);
    timeinfo = localtime(&t);
    int system_time[3];
    system_time[0] = 1900 + timeinfo->tm_year;
    system_time[1] = 1 + timeinfo->tm_mon;
    system_time[2] = timeinfo->tm_mday;
    f[2]=fopen(file_location[2],"w+");
    while((fgets(s, sizeof(s), f[0])) != NULL)
        {
            strcpy(buffer,s);
            token=strtok(s,",");
            for(i=0;i<3&&token!=NULL;i++)
                {
                    re.e_time[i]=atoi(token);
                    if(system_time[0]>re.e_time[0])
                        {
                            fputs(buffer,f[1]);
                            break;
                        }
                    else if((i!=0)&&(system_time[i-1]==re.e_time[i-1])&&(system_time[i]>re.e_time[i]))
                        {
                            fputs(buffer,f[1]);
                            break;
                        }
                    token=strtok(NULL,",");
                }
            if(i>=3)
                {
                    fputs(buffer,f[2]);
                }
        }
    for(i=0;i<3;i++)
        {
            fclose(f[i]);
        }
    remove(file_location[0]);
    rename(file_location[2],file_location[0]);
    return;
}

void bulletinshow()
{
    int i,j;
    bulletinconfirm();
    FILE *f=fopen(file_location[0],"r+");
    char s[1024],*token,*pr[8]={"/","/","\t","\t\t\t\t\t","\t\t","/","/","\n"};
    if((fgets(s,sizeof(s),f))==NULL)
        {
            printf("暫無公告\n");
        }
    else
        {
            printf("結束時間\t公告內容\t\t\t\t\t公告人\t\t公告時間\n");
            do
            {
            token=strtok(s,",");
            for(i=0;i<8&&token!=NULL;i++)
                {
                    if(i==3)
                        {
                            printf("%s%s",token,pr[i]);
                        }
                    else
                        {
                            printf("%s%s",token,pr[i]);
                        }
                    token=strtok(NULL,",,\n");
                }
            }while((fgets(s,sizeof(s),f))!=NULL);
        }
    fclose(f);
    return;
}

bool date_confirmation(int time[3])
{
    if(time[1]>12||time[1]<1)
        {
            return true;
        }
    int day=31-(((time[1]-1)%7)%2)-(time[1]==2)*2+(((time[0]%4==0&&time[0]%100!=0)||(time[0]%400==0)));
    if(time[2]>day||time[2]<1)
        {
            return true;
        }
    return false;
}


void bulletinwrite(char user[128])
{
    bulletinconfirm();
    struct bulletin re[2];
    int i;
    bool fl ;
    char s[1024],buffer[1024],*token;
    time_t t;
    struct tm *timeinfo;
    do{
    fl=false;
    time(&t);
    timeinfo = localtime(&t);
    re[0].p_time[0] = 1900 + timeinfo->tm_year;
    re[0].p_time[1] = 1 + timeinfo->tm_mon;
    re[0].p_time[2] = timeinfo->tm_mday;
    printf("輸入結束時間(yyyy/mm/dd):");
    fflush(stdin);
    scanf("%[^\n]s",s);
    token=strtok(s,"/,\0,\n");
    for(i=0;i<3&&(token!=NULL)||i==0;i++)
        {
            re[0].e_time[i]=atoi(token);
            if(re[0].p_time[0]>re[0].e_time[0])
                {
                    fl=true;
                    printf("\n輸入時間有誤，請重新輸入\n");
                    break;
                }
            else if(!(re[0].p_time[0]<re[0].e_time[0])&&((i!=0)&&(re[0].p_time[i-1]==re[0].e_time[i-1])&&(re[0].p_time[i]>re[0].e_time[i]))||((token==NULL)&&(i==0)))
                {
                    fl=true;
                    printf("\n輸入時間有誤，請重新輸入\n");
                    break;
                }
            token=strtok(NULL,"/,\0,\n");
        }
    bool d=date_confirmation(re[0].e_time);
    if(d&&(!fl))
        {
            fl=true;
            printf("\n輸入時間有誤，請重新輸入\n");
        }
    }while(fl);
    printf("輸入公告內容:");
    fflush(stdin);
    fgets(re[0].bulletin, sizeof(re[0].bulletin), stdin);
    size_t len = strlen(re[0].bulletin);
    if (len > 0 && re[0].bulletin[len - 1] == '\n') {
        re[0].bulletin[len - 1] = '\0';
    }
    printf("--------%s", re[0].bulletin);
    FILE *f[2];
    f[0]=fopen(file_location[0],"r+");
    f[1]=fopen(file_location[2],"w+");
    fl=true;
    while((fgets(s, sizeof(s), f[0])) != NULL)
        {
            strcpy(buffer,s);
            token=strtok(s,",");
            for(i=0;i<3&&token!=NULL&&fl;i++)
                {
                    re[1].e_time[i]=atoi(token);
                    if(re[0].e_time[0]>re[1].e_time[0])
                        {
                            fputs(buffer,f[1]);
                            break;
                        }
                    else if((i!=0)&&(re[0].e_time[i-1]==re[1].e_time[i-1])&&(re[0].e_time[i]>re[1].e_time[i]))
                        {
                            fputs(buffer,f[1]);
                            break;
                        }
                    token=strtok(NULL,",");
                }
            if(i>=3&&fl)
                {
                    fprintf(f[1], "%d,%02d,%02d,%s,%s,%d,%02d,%02d\n", re[0].e_time[0], re[0].e_time[1], re[0].e_time[2], re[0].bulletin, user, re[0].p_time[0], re[0].p_time[1], re[0].p_time[2]);
                    fl=false;
                }
            if(!fl)
                {
                    fputs(buffer,f[1]);
                }
        }
    if(fl)
        {
            fprintf(f[1], "%d,%02d,%02d,%s,%s,%d,%02d,%02d\n", re[0].e_time[0], re[0].e_time[1], re[0].e_time[2], re[0].bulletin, user, re[0].p_time[0], re[0].p_time[1], re[0].p_time[2]);
        }

    for(i=0;i<2;i++)
        {
            fclose(f[i]);
        }
    remove(file_location[0]);
    rename(file_location[2],file_location[0]);
    return;

}
