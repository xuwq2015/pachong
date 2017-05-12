#ifndef _COMMON_H_
#define _COMMON_H_

#define PA_BUF_SIZE 1024						//字符串数组缓冲区大小
#define PA_ESSAY_URL_BUF 350					//文章url缓冲区大小
#define PA_SEED_BUF 150							//种子url缓冲区大小
#define PA_PAGE_CONTENT_BUF	512000				//页面缓存大小


/* 数据库 */
#define DB_HOST_NAME "127.0.0.1"
#define DB_USER_NAME "pachong"
#define DB_USER_PASSWD "Pachong=123"
#define DB_NAME "pachong"
#define DB_PORT 3306
#define DB_ARTICLE_LINK_TABLE "essay_url"

/*
 *const char *g_host_name = "localhost";
 *const char *g_user_name = "root";
 *const char *g_password = "root";
 *const char *g_db_name = "test";
 *const unsigned int g_db_port = 3306;
 **/

 /* 种子url链表结构 */
typedef struct pa_seed_url_st
{
	char url[PA_SEED_BUF];
	struct pa_seed_url_st *next;
}pa_seed_url;

#endif