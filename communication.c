#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "userdata.h"
#include "communication.h"

char* replaceCommas(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == ',') {
            str[i] = '$';
        }
    }
    return str;
}

char* restoreCommas(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == '$') {
            str[i] = ',';
        }
    }
    return str;
}

// Function to mark the first character of each line in a CSV file as '1'
void markasread(char *filename) {
    // Check if the filename is provided
    if (filename == NULL) {
        printf("Error: File name is NULL\n");
        return;
    }

    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    
    // Check if the file is opened successfully
    if (file == NULL) {
        return;
    }

    // Open a temporary file in write mode
    FILE *tempFile = fopen("temp.csv", "w");

    // Check if the temporary file is opened successfully
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary file\n");
        fclose(file);
        return;
    }

    // Process each line in the CSV file
    char line[1000]; // Adjust the size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        // Mark the first character as '1'
        if (line[0] != '\0' && line[0] != '\n') {
            line[0] = '1';
        }

        // Write the modified line to the temporary file
        fputs(line, tempFile);
    }

    // Close both files
    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(filename);
    rename("temp.csv", filename);

    // printf("File %s marked as read.\n", filename);
    return;
}

// return if message send successfully
bool sendmessage(struct _Message Message) {

    struct _Userdata user_buffer;
    FILE *fp;
    // to store tne sent time
    time_t nowtime = time(NULL);
    char filename_buffer[128];

    Message.read = false;
    // replace all the commas to prevent CSV error
    replaceCommas(Message.content);

    if( !read_userdata_by_id(&user_buffer, atoi(Message.receiver)) ) {
        printf("查無此收件人\n");
        return false;
    }

    // append a new message to the receiver inbox
    strcpy(filename_buffer, "./user_data/");
    strcat(filename_buffer, Message.receiver);
    fp = fopen( strcat(filename_buffer, "_received.csv"), "a" );
    fprintf(fp, "%d,%s,%s,%d,%s\n", Message.read, 
                                    Message.sender, 
                                    Message.receiver, 
                                    nowtime, 
                                    Message.content);
    fclose(fp);

    // append a new row in the sender log
    strcpy(filename_buffer, "./user_data/");
    strcat(filename_buffer, Message.sender);
    fp = fopen( strcat(filename_buffer, "_sent.csv") , "a" );
    fprintf(fp, "%d,%s,%s,%d,%s\n", Message.read, 
                                    Message.sender, 
                                    Message.receiver, 
                                    nowtime, 
                                    Message.content);
    fclose(fp);

    return true;
}

// input a unmalloc _Message pointer to save the array
// input a user to get all of the received message
// mode "read" to read messages the user received
// mode "unread" equals ro "read" but won't mark as read
// mode "log"  to read messages the user sent
// return the number of the unread message
// return -1 if the reading process got problem
int readmessage(struct _Message *list, struct _Userdata user, char *mode) {
    
    // allowcate memory for the list
    // list = malloc(sizeof(struct _Message)*128);
    // a temp var during the reading process
    struct _Message temp;
    time_t temp_time_t;
    struct tm *temp_tm;

    // to process filename
    char filename_buffer[128];
    // for file pointer
    FILE *fp;
    // to read each line of the file
    char buffer[2048];
    // to save every column value
    char *value;
    // counter of the column
    int column;
    // conter of the message number
    int line;

    strcpy(filename_buffer, "./user_data/");
    strcat(filename_buffer, user.account);

    if( strcmp(mode, "read") == 0 || strcmp(mode, "unread") == 0 )
        fp = fopen( strcat(filename_buffer, "_received.csv"), "r+" );
    else if( strcmp(mode, "log") == 0 )
        fp = fopen( strcat(filename_buffer, "_sent.csv"), "r+" );

    line = 0;
    while( fgets(buffer, 2048, fp) != NULL ) {
        value = strtok(buffer, ",");
        // read data column by column
        column = 0;

		while (value)
		{
			switch (column) {

				case 0:
                    temp.read = atoi(value);
                    break;
				
				case 1:
                    strcpy(temp.sender, value);
					break;
				
				case 2:
                    strcpy(temp.receiver, value);
					break;

				case 3:
                    temp_time_t = atoi(value);
                    temp_tm = localtime(&temp_time_t);
                    temp.time = *temp_tm;
					break;
				
				case 4:
                    strcpy(temp.content, restoreCommas(value));
					break;

				default:
					break;

			}
			value = strtok(NULL, ",");
			column++;
		}
        list[line] = temp;
        line++;
    }

    fclose(fp);
    if(strcmp(mode, "unread") != 0 ) markasread(filename_buffer);
    // list = realloc(list, sizeof(struct _Message)*line);
    return line;
}

// input a _Message list to count unread number
int countunread(struct _Userdata user) {
    int unread_count = 0;
    int num_messages;
    struct _Message message_list[128];

    num_messages = readmessage(message_list, user, "unread");
    for (int i = 0; i < num_messages; ++i) {
        if (!message_list[i].read) {
            unread_count++;
        }
    }
    
    return unread_count;
}

// input NULL if there is no receiver assigned
bool writemessage(struct _Userdata user,char *receiver) {
    
    struct _Message Message;
    char input_buffer[1024];
    printf("撰寫新訊息:\n\n");

    // set sender
    printf("寄件人: %s\n", user.account);
    strcpy(Message.sender, user.account);

    // set receiver, require user input if not exist
    printf("收件人: ");
    if(receiver == NULL) {
        scanf("%s", Message.receiver);
    }
    else {
        strcpy(Message.receiver, receiver);
    }

    // input message contents
    getchar();
    printf("請輸入訊息(至多340字, 至換行結束):");
    scanf("%[^\n]", Message.content);

    printf("\n");
    if(sendmessage(Message)){
        printf("訊息傳送成功!\n\n");
        return true;
    }
    else{
        printf("訊息傳送失敗!\n\n");
        return false;
    }

    return false;
}

// compare the time and return string how long ago
char* timeDifference(struct tm inputTime) {
    time_t now;
    struct tm *currentTime;
    char* output = (char*)malloc(100 * sizeof(char));
    
    // Get the current time
    time(&now);
    // Convert the current time to a tm struct
    currentTime = localtime(&now);

    // Calculate the differences in years, months, days, hours, and minutes
    int yearsDiff = currentTime->tm_year - inputTime.tm_year;
    int monthsDiff = currentTime->tm_mon - inputTime.tm_mon;
    int daysDiff = currentTime->tm_mday - inputTime.tm_mday;
    int hoursDiff = currentTime->tm_hour - inputTime.tm_hour;
    int minutesDiff = currentTime->tm_min - inputTime.tm_min;

    // Determine the appropriate time difference and create the output string
    if (yearsDiff > 0) {
        snprintf(output, 100, "%d 年前  ", yearsDiff);
    } else if (monthsDiff > 0) {
        snprintf(output, 100, "%d 個月前", monthsDiff);
    } else if (daysDiff > 0) {
        snprintf(output, 100, "%d 天前  ", daysDiff);
    } else if (hoursDiff > 0) {
        snprintf(output, 100, "%d 小時前", hoursDiff);
    } else if (minutesDiff > 0) {
        snprintf(output, 100, "%d 分鐘前", minutesDiff);
    } else {
        snprintf(output, 100, "剛剛     ");
    }

    return output;
}

// print message list in the console
// input a _Message array and the number of the array
void listmessage(struct _Message *list, int number){
    int i;
    char *difftime;

    printf("  \t   \t來自\t時間     \t內容\n");
    for (i = 0; i < number; i++){
        printf("%d.\t", i+1);
        // print if the message is new
        if(list[i].read) printf("[ ]\t");
        else             printf("[*]\t");
        
        // compare time and return the string directly
        difftime = timeDifference(list[i].time);
        printf("%s\t%s\t%s",    list[i].sender, 
                                difftime, 
                                list[i].content);
    }
    free(difftime);
    
}

// print message list in the console
// input a _Message array and the number of the array
void logmessage(struct _Message *list, int number){
    int i;
    char *difftime;

    printf("  \t送往\t時間\t內容\n");
    for (i = 0; i < number; i++){
        printf("%d.\t", i+1);
        // compare time and return the string directly
        difftime = timeDifference(list[i].time);
        printf("%s\t%s\t%s",    list[i].receiver, 
                                difftime, 
                                list[i].content);
    }
    free(difftime);
    
}
/*
int main(){

    system("chcp 65001");
    struct _Userdata user;
    struct _Message message_list[128];
    int message_count;
    int unread_count;
    int i;
    strcpy(user.account, "12345");
    writemessage(user, NULL);

    message_count = readmessage(message_list, user, "log");
    printf("%d\n", message_count);
    logmessage( message_list, message_count );

    printf("\n------------------\n");
    printf("In the case user 123: \n");
    strcpy(user.account, "123");
    strcpy(user.password, "1234");
    strcpy(user.symbol, "t");

    unread_count = countunread( user );
    printf("您有 %d 則新訊息，共 %d 則訊息\n", unread_count, message_count);
    message_count = readmessage(message_list, user, "read");

    // printf("讀取\t傳送者\t內容\n");
    // for (i = 0; i < message_count; i++){
    //     printf("%d\t%s\t%s\n", message_list[i].read,
    //                                message_list[i].sender,
    //                                message_list[i].content );
    // }

    listmessage( message_list, message_count );    

    return 0;
}
*/
