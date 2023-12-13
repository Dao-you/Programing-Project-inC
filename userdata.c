#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "userdata.h"

bool read_userdata_by_row(struct _Userdata *userdata,int row){
    int i;

    if((row>500&&row<1120001)||(row<0)||(row>1125000))
        return false;

    if(row>500){
        row=row-1119500;
    }

    FILE *fp=fopen("./user_data/userdata.csv","r");
    if(!fp){
        printf("Can't open the user file\n");
        return false;
    }
    else{
        char buffer[1024];
        int now=0,column=0;

        while(now<row+1){
            now++;
            if(fgets(buffer,1024,fp)==NULL) return false;
        }

        char *value=strtok(buffer,",");

        while(value){
            switch(column){
                case 0:
                    strcpy(userdata->account,value);
                    break;
                case 1:
                    strcpy(userdata->password,value);
                    break;
            }
            value=strtok(NULL,",");
            column++;
        }
        fclose(fp);
        return true;
    }
}

bool update_userdata(struct _Userdata *userdata){
    long long line_pos = -1;
    size_t line_length;
    int data_length;
    char *value;

    FILE *fp=fopen("./user_data/userdata.csv","r+");
    bool flag = false;

    if(!fp){
        printf("Can't open the user file\n");
        return false;
    }
    else{
        char buffer[1024];
        while( fgets(buffer,1024,fp) != NULL ){
            line_length = strlen(buffer) + 1;
            value=strtok(buffer, ",");
            if(!(strcmp(value,userdata->account))){
                flag = true;
                line_pos = ftell(fp);
                break;
            }
        }

        if(flag){
            fseek(fp, line_pos - line_length, SEEK_SET);
            data_length=fprintf(fp,"%s,%s",userdata->account,userdata->password);
            for (int i = data_length; i < strlen(buffer); i++) {
                fputc(' ', fp);
            }
            fclose(fp);
            return true;
        }
        else{
            fclose(fp);
            return false;
        }

    }
}
