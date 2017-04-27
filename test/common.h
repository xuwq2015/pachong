#ifndef _COMMON_H_
#define _COMMON_H_

#define PA_BUF_SIZE 1024
#define PA_PARAMETER_ERR "参数输入错误，请重新输入"
#define PA_FILENAME_SIZE 100
#define PA_FILE_DIR "./cache/"

typedef struct link_struct
{
    char link[PA_BUF_SIZE];
    struct link_struct *next;
}pa_link_st;

#endif
