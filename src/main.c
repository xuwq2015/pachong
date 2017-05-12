#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <mysql/mysql.h>
#include <common.h>
#include <err_warn.h>
#include <db_option.h>
#include <get_seed.h>

MYSQL pa_mysql; 				// mysql连接
pa_seed_url seed_url_p;			// 种子curl链表头部

/* 程序初始化函数 */
int pa_init()
{
	CURLcode ret_code;
	
	pa_init_mysql(&pa_mysql);
	ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	return 0;
}

int pa_free()
{
	mysql_close (&pa_mysql);	//关闭数据库连接
	curl_global_cleanup();		//关闭curl
	
	/* 释放种子url链表 */
	pa_seed_url *p = seed_url_p.next;
	while(seed_url_p.next != NULL)
	{
		p = p->next;
		free(seed_url_p.next);
		seed_url_p.next = p;
	}
	
	return 0;
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
	
	pa_get_seed(&pa_mysql, &seed_url_p);	
	
	pa_free();
	
	return 0;
}
