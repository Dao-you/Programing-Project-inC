#ifndef USERDATA
#define USERDATA

#include <stdbool.h>

struct Userdata{
    int account[20]; //�b��
    char password[20]; //�K�X
};

void read_userdata_by_row(struct Userdata *userdata,int row);
bool update_userdata(struct Userdata *userdata,int pos,char *changed_password);

#endif
