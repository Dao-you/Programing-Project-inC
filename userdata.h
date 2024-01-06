#ifndef USERDATA
#define USERDATA

#include <stdbool.h>

struct _Userdata{
    char account[128]; //帳號
    char password[128]; //密碼
    char symbol[2]; //管理員:m 老師:t 學生:s
};

bool read_userdata_by_id(struct _Userdata *userdata,int id);
bool update_userdata(struct _Userdata *userdata);
struct _Userdata login();
void password_modify(struct _Userdata *userdata);
void admin_resetpassword()

#endif
