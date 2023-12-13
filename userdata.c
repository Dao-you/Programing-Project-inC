#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "userdata.h"
void read_userdata_by_row(struct Userdata *userdata,int row){

    int i;
    char buffer[1024],*Token;

    if(row>500){
        row=row-1119500;
    }

    FILE *fp=fopen("./user_data/userdata.csv","r");
    if(!fp){
        printf("Can't open the user file\n");
        return false;
    }

    for(i=1;i<=row;i++){
        fgets(buffer,1024,fp);
    }

    Token=strtok(buffer,",");
    printf("%s",Token);
    Token=strtok(NULL,",");
    printf("%s",Token);
    /*
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
                    userdata->account=atoi(value);
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
    */
}

bool update_userdata(struct Userdata *userdata,int pos,char *changed_password){
    if(pos>500){
        pos=pos-1119500;
    }

    FILE *fp=fopen("./user_data/userdata.csv","r+");
    if(!fp){
        printf("Can't open the user file\n");
        fclose(fp);
        return false;
    }
    else{
        char buffer[1024];
        int i;

        for(i=1;i<=pos;i++){
            fgets(buffer,1024,fp);

        }

        strtok(buffer,",");
        strtok(NULL,",");
        fseek(fp,0,SEEK_SET);
        fprintf(fp,"%s",changed_password);
        fclose(fp);
        return true;
    }
}
