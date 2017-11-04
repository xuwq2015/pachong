#ifndef _COMMON_H_
#define _COMMON_H_

#define PA_BUF_SIZE 1024						//字符串数组缓冲区大小
#define PA_ESSAY_URL_BUF 350					//文章url缓冲区大小
#define PA_SEED_BUF 150							//种子url缓冲区大小
#define PA_PAGE_CONTENT_BUF	1048576				//页面缓存大小1M

/* 网站类型(文章，图片，视频) */
#define WEB_TYPE_ARTICLE 0
#define WEB_TYPE_TUPIAN 1
#define WEB_TYPE_SHIPIN 2

typedef struct web_config_st{
	int type;
	char url[PA_BUF_SIZE];
	char article_start[PA_BUF_SIZE];
	char article_end[PA_BUF_SIZE];
	char article_url_rule[PA_BUF_SIZE];
	char next_page[PA_BUF_SIZE];
	char next_page_rule[PA_BUF_SIZE];
	struct web_config_st *next;
}web_config;

#endif