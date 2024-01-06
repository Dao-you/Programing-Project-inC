#ifndef COMMUNICATION
#define COMMUNICATION

#include <time.h>

struct _Message {
    bool read;
    char sender[128];
    char receiver[128];
    struct tm time;
    char content[1024];
};

bool sendmessage(struct _Message Message);
int readmessage(struct _Message *list, struct _Userdata user, char *mode);
void msrkasunread(struct _Userdata user, int lineNumber);
void deletemessage(struct _Userdata user, int lineNumber);
void deleteMessageinarray(struct _Message *messages, int length, int indexToDelete);
int countunread(struct _Userdata user);
bool writemessage(struct _Userdata user,char *receiver);
void listmessage(struct _Message *list, int number);
void logmessage(struct _Message *list, int number);
void viewmessage(struct _Message message);


#endif