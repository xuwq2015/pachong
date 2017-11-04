#ifndef	_PA_GET_ARTICLE_H_
#define _PA_GET_ARTICLE_H_

#include <common.h>
#include <mysql/mysql.h>

/* 存放从数据库中读取到的文章url相关内容 */
typedef struct article_url {
	int uid;
	char url[PA_BUF_SIZE];
	char title[PA_BUF_SIZE];
	int status;
	char createtime[PA_BUF_SIZE];
	struct article_url *next;
}article_url_st;

/*保存下载的文章内容*/
typedef struct article_content {
	char url[PA_BUF_SIZE];
	char title[PA_BUF_SIZE];
	char content[PA_PAGE_CONTENT_BUF];
	struct article_content *next;
}article_content_st;

void pa_get_article_content();		//外部调用函数
static int pa_extract_article_content(char *article_url);
static int pa_extact_all_content_url(char *url);

#endif