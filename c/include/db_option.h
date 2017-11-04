#ifndef _DB_OPTION_H_
#define _DB_OPTION_H_

#include <common.h>
#include <mysql/mysql.h>
#include <pa_get_article.h>
#include <get_seed.h>

/* 数据库默认信息 */
#define DB_TYPE "mysql"
#define DB_HOST_NAME "127.0.0.1"
#define DB_USER_NAME "pachong"
#define DB_USER_PASSWD "Pachong=123"
#define DB_NAME "pachong"
#define DB_PORT 3306
#define DB_SEED_TABLE "essay_url"
#define DB_ARTICLE_URL_TABLE "essay_url"
#define DB_ARTICLE_TABLE "article_content"

#define DB_CONFIG_BUF 20

/* 数据库配置结构 */
typedef struct db_config_struct {
	int port;
	char type[DB_CONFIG_BUF];
	char host[DB_CONFIG_BUF];
	char user[DB_CONFIG_BUF];
	char passwd[DB_CONFIG_BUF];
	char name[DB_CONFIG_BUF];
	char seed_table[DB_CONFIG_BUF];
	char article_table[DB_CONFIG_BUF];
	char article_url_table[DB_CONFIG_BUF];
}db_config_st;

int pa_init_mysql();											//初始化连接
int pa_close_mysql();											//关闭数据库连接
int pa_seed_inquire();											//url种子表查询函数
int pa_insert_article_link();									//插入文章url
int pa_article_url_inquire(article_url_st *st);					//查询文章url
int pa_insert_article_content(article_content_st *p);			//插入文章内容

static int pa_executesql(const char*);			//执行sql语句

#endif