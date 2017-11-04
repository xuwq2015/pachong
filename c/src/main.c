#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <mysql/mysql.h>
#include <common.h>
#include <err_warn.h>
#include <db_option.h>
#include <get_seed.h>
#include <pa_get_article.h>
#include <pa_read_config.h>

article_url_st pa_article_url_head;				// 文章url链表头
article_content_st pa_article_content_head;		// 文章内容链表头
extern web_config web_config_head;


void pa_free(void)
{	
	article_url_st *article_url_next;
	article_url_st *article_url_p = pa_article_url_head.next;
	
	article_content_st *article_content_next;
	article_content_st *article_content_head = pa_article_content_head.next;

	web_config *web_config_next;
	web_config *web_config_p = web_config_head.next;
	
	/* 释放文章url链表 */
	while(article_url_p != NULL)
	{
		article_url_next = article_url_p->next;
		free(article_url_p);
		article_url_p = article_url_next;
	}
	
	/* 释放文章url链表 */
	while(article_content_head != NULL)
	{
		article_content_next = article_content_head->next;
		free(article_content_head);
		article_content_head = article_content_next;
	}

	/* 释放文章url链表 */
	while(web_config_p != NULL)
	{
		web_config_next = web_config_p->next;
		free(web_config_p);
		web_config_p = web_config_next;
	}
}

void pa_free_article_url_list(void)
{
	article_url_st *article_url_next;
	article_url_st *article_url_p = pa_article_url_head.next;
	
	/* 释放文章url链表 */
	while(article_url_p != NULL)
	{
		article_url_next = article_url_p->next;
		free(article_url_p);
		article_url_p = article_url_next;
	}
}

void pa_free_article_content_list(void)
{
	article_content_st *article_content_next;
	article_content_st *article_content_head = pa_article_content_head.next;
	
	/* 释放文章url链表 */
	while(article_content_head != NULL)
	{
		article_content_next = article_content_head->next;
		free(article_content_head);
		article_content_head = article_content_next;
	}
}

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		char str[] = "参数输入错误，请重新输入";
		pa_err(str);
		exit(0);
	}

	/* 各种初始化操作 */
	pa_init_config();
	open_log_file();
	pa_init_mysql();
	pa_init_curl();
	
	
	/* 从数据库中查询种子url */
	pa_seed_inquire();
	
	/* 从种子url中获取文章url并保存 */
	pa_get_seed_content();	
	
	
	/* 从数据库中读取文章url，
		并提取文章url内容保存到数据库中 */
	//pa_get_article_content();

	/* 各种清理操作 */
	pa_free();
	pa_close_mysql();	//关闭数据库连接
	pa_cleanup_curl();	//关闭curl
	close_log_file();	//关闭log文件
	
	return 0;
}
