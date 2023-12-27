#ifndef USERDATA
#define USERDATA

#include <stdbool.h>

struct _Userdata{
    char account[20]; //帳號
    char password[20]; //密碼
    char symbol[2]; //管理員:m 老師:t 學生:s
};

bool read_userdata_by_id(struct _Userdata *userdata,int id);
bool update_userdata(struct _Userdata *userdata);

#endif
