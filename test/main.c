#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <mysql/mysql.h>
#include "common.h"
#include "err_warn.h"
#include "db_option.h"

MYSQL seed_mysql; 				// mysql 连接
MYSQL essay_mysql;
pa_seed_url seed_url_p;

void pa_print_seed()
{
	pa_seed_url *p = seed_url_p.next;
	while(p != NULL)
	{
		printf("%s\n", p->url);
		p = p->next;
	}
}

void pa_free_seed(void)
{
	pa_seed_url *p = seed_url_p.next;
	while(seed_url_p.next != NULL)
	{
		p = p->next;
		free(seed_url_p.next);
		seed_url_p.next = p;
	}
}

int pa_get_seed()
{
	if(pa_init_mysql(&seed_mysql))
	{
		pa_err("pa_get_seed: 初始化数据库错误");
		return -1;
	}
	
	if(pa_seed_inquire(&seed_mysql, &seed_url_p))
	{
		pa_err("pa_get_seed:查询错误");
		return -1;
	}
}

int main(int argc, char *argv[])
{
	CURLcode ret_code;
	int ret = 0;
	char str[PA_BUF_SIZE] = {'\0'};

	if(argc < 1)
	{
		strncpy(str, PA_PARAMETER_ERR, strlen(PA_PARAMETER_ERR));
		pa_err(str);
		exit(0);
	}

	ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	pa_get_seed();
	pa_print_seed();

	curl_global_cleanup();
	mysql_close (&seed_mysql);
	pa_free_seed();
	return 0;
}
