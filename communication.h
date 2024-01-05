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


#endif