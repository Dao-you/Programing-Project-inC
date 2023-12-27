#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // include the bool standard function.
#include "userdata.h"

// Read the userdata,the first argument is struct _Userdata and pass by pointer,
// the second argument will be the id to query.
bool read_userdata_by_id(struct _Userdata *userdata,int id){
    int i;

    if((id>500&&id<1120001)||(id<0)||(id>1125000))
        return false;

    if(id>500){
        id=id-1119500;
    }

    FILE *fp=fopen("./user_data/userdata.csv","r");
    if(!fp){
        printf("Can't open the user file\n");
        return false;
    }
    else{
        char buffer[1024];
        int now=0,column=0;

        while(now<id+1){
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
                case 2:
                    strcpy(userdata->symbol,value);
                    break;
            }
            value=strtok(NULL,",");
            column++;
        }
        fclose(fp);
        return true;
    }
}

// Update the userdata, argument is struct _Userdata and pass by pointer.
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
            data_length=fprintf(fp,"%s,%s,%c",
                                userdata->account,
                                userdata->password,
                                userdata->symbol);
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
