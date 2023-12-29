#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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


bool password_strenghten(char *password){
    int length = strlen(password);
    bool has_upper = 0, has_lower = 0;

    // Check length
    if (length < 8) {
        printf("密碼長度應該大於 8 。\n");
        return false;
    }

    // Check for uppercase, lowercase, and symbols
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) {
            has_upper = 1;
        } else if (islower(password[i])) {
            has_lower = 1;
        }
        if(has_upper && has_lower){
            break;
        }
    }

    if (!has_upper || !has_lower) {
        printf("密碼應該同時包含大寫字母和小寫字母。\n");
        return false;
    }

    // Check for duplicate strings with the same length exceeding 2
    for (int i = 0; i < length - 2; i++) {
        for (int j = i + 2; j < length - 1; j++) {
            if (strncmp(&password[i], &password[j], 3) == 0) {
                printf("不得出現長度大於 2 的重複字串。\n");
                return false;
            }
        }
    }

    return true;
}

struct _Userdata login(){
    struct _Userdata userdata;
    char account[128], password[128];

    printf("請輸入帳號：");
    scanf("%s", account);
    printf("請輸入密碼：");
    scanf("%s", password);

        // 驗證帳號密碼是否正確，若不正確則請使用者重新輸入帳號密碼
    while(!(read_userdata_by_id(&userdata, atoi(account)) && !(strcmp(userdata.password,password)))){
        printf("\n帳號密碼錯誤!\n\n");
        printf("請輸入帳號:");
        scanf("%s",account);
        printf("\n請輸入密碼:");
        scanf("%s",password);
    }

    // 判斷密碼是否為預設密碼1234，若為預設密碼則請使用者更新密碼
    if(!strcmp(userdata.password,"1234")){
        printf("\n請更改密碼!\n");
        printf("考量資通安全，密碼需符合以下要求:\n");
        printf("1. 可以使用英文字母和符號\n");
        printf("2. 需同時使用大小寫英文字母\n");
        printf("3. 不可包含重複的字串\n");
        printf("\n");
        printf("請輸入新密碼:");
        scanf("%s",password);

        while ( password_strenghten(password) ) {
            printf("密碼不符合要求，請重新輸入。\n\n");
            printf("請輸入新密碼:");
            scanf("%s",password);
        }

        strcpy(userdata.password, password);
        update_userdata(&userdata);
    }

    printf("%d, 登入成功!", userdata.account);
    return userdata;
}