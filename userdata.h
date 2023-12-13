#ifndef USERDATA
#define USERDATA

#include <stdbool.h>

struct _Userdata{
    char account[20];
    char password[20];
};

bool read_userdata_by_row(struct _Userdata *userdata,int row);
bool update_userdata(struct _Userdata *userdata);

#endif
