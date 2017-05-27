#ifndef _DB_OPTION_H_
#define _DB_OPTION_H_

#include <common.h>
#include <mysql/mysql.h>
#include <pa_get_article.h>

int pa_init_mysql();							//初始化连接
static int pa_executesql(const char*);		//执行sql语句
int pa_seed_inquire();			//url种子表查询函数
int pa_insert_article_link(char*, char*);	//插入文章url

int pa_article_url_inquire(article_url_st *st);						//查询文章url
int pa_insert_article_content(article_content_st *p);

#endif