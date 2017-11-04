#ifndef _GET_SEED_H_
#define _GET_SEED_H_

#include <common.h>
#include <regex.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <pa_string.h>

/* 存放获取到的文件标题和连接 */
typedef struct pa_article_url_st {
	char title[PA_BUF_SIZE];
	char url[PA_BUF_SIZE];
	struct pa_article_url_st *next;
}pa_article_url;

 /* 种子url链表结构 */
typedef struct pa_seed_url_st
{
	char url[PA_SEED_BUF];
	char file[PA_SEED_BUF];
	struct pa_seed_url_st *next;
}pa_seed_url;

void pa_get_seed_content();

static int pa_get_article_link(web_config *web_config_p, char *file_name);
static int pa_get_next_page(web_config *web_config_p, char *file_name, char *next_url);
static void pa_free_seed_list();
static web_config *pa_get_web_config_p(char *url) ;

#endif