#ifndef CLASSROOM
#define CLASSROOM

#include <stdbool.h>

struct _Classroom {
    short id;              // 編號
    char  nickname[30];    // 教室簡稱
    char  wholename[60];   // 教室全名
    short type;            // 教室類型
    short capacity;        // 容量
    bool  usage[7][13];    // 使用情況
};

#endif