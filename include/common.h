#ifndef _COMMON_H_
#define _COMMON_H_

#define BUF_SIZE 1024
#define MAXHEADLEN 1024
#define FILENAME_SIZE 60

#define FILE_DIR "./cache/"

typedef struct link_struct
{
    char link[BUF_SIZE];
    struct link_struct *next;
}pa_link_st;

#endif
