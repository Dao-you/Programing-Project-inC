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
bool update_userdata(struct _Userdata *userdata) {
    FILE *fp = fopen("./user_data/userdata.csv", "r+"); // Open file

    // Check if the file is opened successfully
    if (!fp) {
        printf("Can't open the user file\n");
        return false;
    }

    char buffer[1024];
    long long line_pos = -1; // Position of the found line
    size_t line_length; // Length of a line
    bool flag = false; // Flag to indicate if the line is found

    // Find the line to update
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        line_length = strlen(buffer);
        char *value = strtok(buffer, ",");
        // Check if the account matches
        if (!(strcmp(value, userdata->account))) {
            flag = true;
            // Record the position before the line's contents for potential update
            line_pos = ftell(fp) - line_length - 1; // excluding the newline character
            break;
        }
    }

    if (flag) {
        // Find file size and remaining data size after the line to be updated
        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, line_pos + line_length + 1, SEEK_SET); // Move past the line

        long long remaining_data_size = file_size - ftell(fp);

        // Read remaining data after the updated line
        char *remaining_data = (char *)malloc(remaining_data_size);
        fread(remaining_data, sizeof(char), remaining_data_size, fp);

        // Move back to the position of the line to update
        fseek(fp, line_pos, SEEK_SET);

        // Write the new user data without a newline character
        fprintf(fp, "%s,%s,%s", userdata->account, userdata->password, userdata->symbol);

        // Write the remaining data after the updated line
        fwrite(remaining_data, sizeof(char), remaining_data_size, fp);

        // Close file and free memory
        fclose(fp);
        free(remaining_data);
        return true;
    } else {
        fclose(fp);
        return false; // Return false if the account is not found
    }
}

// return true if the password meet the requires
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
    for (int i = 0; i < length - 4; i++) {
        for (int j = i + 4; j < length - 1; j++) {
            if (strncmp(&password[i], &password[j], 4) == 0) {
                printf("不得出現長度大於 4 的重複字串。\n");
                return false;
            }
        }
    }

    return true;
}

// modify password and update database driectly
void password_modify(struct _Userdata *userdata){
        char password[128];
        char check   [128] = "1234";
        
        printf("考量資通安全，密碼需符合以下要求:\n");
        printf("1. 可以使用英文字母和符號，並建議加入符號\n");
        printf("2. 密碼長度應該大於 8 個字元\n");
        printf("3. 密碼長度不可超過 127 個字元\n");
        printf("4. 需同時使用大小寫英文字母\n");
        printf("5. 不可包含長度大於 4 的重複字串\n");
        printf("\n");

        do{
            printf("請輸入新密碼:");
            scanf("%s",password);

            while ( !password_strenghten(password) ) {
                printf("密碼不符合要求，請重新輸入。\n\n");
                printf("請輸入新密碼:");
                scanf("%s",password);
            }

            printf("請再輸入一次以確認密碼:");
            scanf("%s", check);
            
            while( strcmp(password, check) != 0 ){
                printf("確認密碼不相符\n");
                printf("請再輸入一次以確認密碼，或輸入 0 重新輸入密碼: ");
                scanf("%s", check);
                if (strcmp("0", check) == 0){
                    break;
                }
            }
            
        }while( strcmp("0", check) == 0 );

        strcpy(userdata -> password, password);
        update_userdata(userdata);
}

// Return the current userdata
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
        password_modify(&userdata);
    }
    
    return userdata;
}