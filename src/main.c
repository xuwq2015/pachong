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

MYSQL pa_mysql; 								// mysql连接

pa_seed_url pa_seed_head;						// 种子url链表头
article_url_st pa_article_url_head;				// 文章url链表头
article_content_st pa_article_content_head;		// 文章内容链表头

char *dow_content_buf[PA_PAGE_CONTENT_BUF];		// 下载到的网页内容缓冲区

/* 程序初始化函数 */
void pa_init(void)
{
	CURLcode ret_code;
	
	pa_init_mysql();
	ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
}

void pa_free(void)
{
	pa_seed_url *url_next;
	pa_seed_url *url_p = pa_seed_head.next;
	
	article_url_st *article_url_next;
	article_url_st *article_url_p = pa_article_url_head.next;
	
	article_content_st *article_content_next;
	article_content_st *article_content_head = pa_article_content_head.next;
	
	mysql_close (&pa_mysql);	//关闭数据库连接
	curl_global_cleanup();		//关闭curl
	
	/* 释放种子url链表 */
	while(url_p != NULL)
	{
		url_next = url_p->next;
		free(url_p);
		url_p = url_next;
	}
	
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
}

void pa_free_seed_list(void)
{
	pa_seed_url *url_next;
	pa_seed_url *url_p = pa_seed_head.next;
	
	/* 释放种子url链表 */
	while(url_p != NULL)
	{
		url_next = url_p->next;
		free(url_p);
		url_p = url_next;
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
	
	pa_init();
	
	
	/* 从数据库中查询种子url */
	pa_seed_inquire();
	
	/* 从种子url中获取文章url并保存 */
	pa_get_seed();	
	pa_free_seed_list();
	
	
	/* 从数据库中读取文章url，
		并提取文章url内容保存到数据库中 */
	pa_get_article_content();
	
	pa_free();
	
	return 0;
}
