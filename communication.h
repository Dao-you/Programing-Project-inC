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
int countunread(struct _Userdata user);
bool writemessage(struct _Userdata user,char *receiver);
void listmessage(struct _Message *list, int number);
void logmessage(struct _Message *list, int number);

#endif