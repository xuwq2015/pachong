#include <pa_get_article.h>
#include <db_option.h>
#include <dow_data.h>
#include <common.h>
#include <pa_string.h>
#include <string.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <err_warn.h>

extern article_url_st pa_article_url_head;
extern char dow_content_buf[PA_PAGE_CONTENT_BUF];

void pa_get_article_content()
{
	pa_article_url_inquire(&pa_article_url_head);			//从数据库中获取文章url
	
	char current_url[PA_BUF_SIZE] = "\0";
	article_url_st *article_url_p = pa_article_url_head.next;
	
	while(article_url_p)
	{
		memset(current_url, '\0', sizeof(current_url));
		memset(dow_content_buf, '\0', sizeof(dow_content_buf));
		strncpy(current_url, article_url_p->url, strlen(article_url_p->url));
		
		if(pa_dow_data(current_url) == -1)	{	//下载文章
			article_url_p = article_url_p->next;
			continue;
		}
		if(pa_extact_all_content_url(current_url) == 0) {
			memset(dow_content_buf, '\0', sizeof(dow_content_buf));
			if(pa_dow_data(current_url) == -1) {	//下载文章
				article_url_p = article_url_p->next;
				continue;
			}
			pa_extract_article_content(current_url);
		} else {
			article_url_p = article_url_p->next;
			continue;
		}
		
		article_url_p = article_url_p->next;
	}
}

/* 获取“查看全部”的url */
static int pa_extact_all_content_url(char *url)
{
	int ret = 0;
	char *article_content = dow_content_buf;
	char str_buf[PA_BUF_SIZE] = "\0";
	const char *ch[] = {"<div class=\"post_au\">", "</div>", "<a href=", ">"};
	
	if(!pa_strtok_r(article_content, (char *)ch[0], (char *)ch[1], str_buf)) {
		if(!pa_strtok_r(str_buf, (char *)ch[2], (char *)ch[3], str_buf)) {
			ret = pa_strtok_link(str_buf, url, str_buf);
			if(ret == 2 || ret == -1) {
				return -1;
			}
		}
	} else {
		return -1;
	}
	return 0;
}

/* 提取文章内容 */
static int pa_extract_article_content(char *article_url)
{	
	char *article_content = dow_content_buf;
	char str_buf[PA_BUF_SIZE] = "\0";
	char content_buf[PA_BUF_SIZE] = "\0";
	article_content_st p;
	const char *ch[] = {"<img data-original=", ">"};
	
	memset(p.url, '\0', strlen(p.url));
	memset(p.title, '\0', strlen(p.title));
	memset(p.content, '\0', strlen(p.content));
	
	strncpy(p.url, article_url, strlen(article_url));
	
	/* 获取文章标题 */
	pa_get_center(article_content, "<title>", "</title>", p.title);
	
	while(1)
	{
		memset(str_buf, '\0', sizeof(str_buf));
		if((article_content = pa_strtok(article_content, (char *)ch[0], (char *)ch[1], str_buf)) == NULL)
			break;
		
		pa_get_img_link(str_buf, content_buf, NULL);
		
		strncat(p.content, content_buf, strlen(content_buf));
		strncat(p.content, ";", strlen(";"));
	}

	pa_insert_article_content(&p);
	
	return 0;
}