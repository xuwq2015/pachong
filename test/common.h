#ifndef _COMMON_H_
#define _COMMON_H_

#define PA_BUF_SIZE 1024
#define PA_PARAMETER_ERR "参数输入错误，请重新输入"
#define PA_FILENAME_SIZE 100
#define PA_FILE_DIR "./cache/"

/* 数据库 */
#define DB_HOST_NAME "127.0.0.1"
#define DB_USER_NAME "pachong"
#define DB_USER_PASSWD "Pachong=123"
#define DB_NAME "pachong"
#define DB_PORT 3306

/*
 *const char *g_host_name = "localhost";
 *const char *g_user_name = "root";
 *const char *g_password = "root";
 *const char *g_db_name = "test";
 *const unsigned int g_db_port = 3306;
 **/

typedef struct link_struct
{
    char link[PA_BUF_SIZE];
    struct link_struct *next;
}pa_link_st;

typedef struct pa_seed_url_st
{
	char url[PA_BUF_SIZE];
	struct pa_seed_url_st *next;
}pa_seed_url;

#endif
