#ifndef CLASSROOM
#define CLASSROOM

#include <stdbool.h>

#define CLASSROOM_MAX_NUMBER 256

struct _Classroom {
    int id;              // 編號
    char  nickname[30];    // 教室簡稱
    char  wholename[60];   // 教室全名
    short type;            // 教室類型
    short capacity;        // 容量
    bool  usage[7][13];    // 使用情況
};

bool read_classroom_by_row(struct _Classroom *classroom, int row);
bool read_classroom_by_id(struct _Classroom *classroom, int id);
bool update_classroom_usage(struct _Classroom *classroom);
int search_classroom(struct _Classroom **classroom_list,int type, int capacity, bool *usage);

#endif