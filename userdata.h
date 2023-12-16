#ifndef USERDATA
#define USERDATA

#include <stdbool.h>

struct _Userdata{
    char account[20]; //±b¸¹
    char password[20]; //±K½X
};

bool read_userdata_by_id(struct _Userdata *userdata,int id);
bool update_userdata(struct _Userdata *userdata);

#endif
