/*
 * 此文件定义了所有与数据库操作有关的函数
 **/

#include <db_option.h>
#include <common.h>
#include <err_warn.h>
#include <stdlib.h>
#include <string.h>

static MYSQL pa_mysql;
db_config_st db_config;
extern pa_seed_url pa_seed_head;
extern pa_article_url pa_article_url_head;

/* 初始化数据库连接 */
int pa_init_mysql() 
{ 	
	// init the database connection
	if(mysql_init(&pa_mysql) == NULL)
	{
		pa_err((char *)mysql_error(&pa_mysql));
		return -1;
	}

	/* connect the database */
	if(!mysql_real_connect(&pa_mysql, db_config.host, db_config.user, db_config.passwd, 
		db_config.name, db_config.port, NULL, 0))
	{
		pa_err((char *)mysql_error(&pa_mysql));
		return -1;
	} else {
		pa_warn("The database connection is successful");
	}
 
	return 0;
}

int pa_close_mysql()
{
	pa_warn("Close the database connection");
	mysql_close(&pa_mysql);	//关闭数据库连接
}

/* url种子表查询函数 */
int pa_seed_inquire()
{
	MYSQL_RES *g_res; 		// mysql 记录集
	MYSQL_ROW g_row; 		// 字符串数组，mysql 记录行
	//int iNum_rows = 0;	// 得到记录的行数
	//int iNum_fields = 0;	// 得到记录的列数
	pa_seed_url *p, *seed_url_p = &pa_seed_head;
	
	char sql[PA_BUF_SIZE] = "\0";
	sprintf(sql, "SELECT * FROM `%s`", db_config.seed_table);
	
	if(pa_executesql(sql))
	{
		pa_err((char *)mysql_error(&pa_mysql));
		return -1;
	}
	
	g_res = mysql_store_result(&pa_mysql); 		// 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集
	//iNum_rows = mysql_num_rows(g_res); 		// 得到记录的行数
	//iNum_fields = mysql_num_fields(g_res); 	// 得到记录的列数
	
	/* mysql_fetch_row:获取一行数据,并保存到g_row中 */
	while((g_row=mysql_fetch_row(g_res)))
	{
		p = malloc(sizeof(pa_seed_url));
		memset(p->url, '\0', sizeof(p->url));
		strncpy(p->url, g_row[0], strlen(g_row[0]));
		p->next = NULL;
		seed_url_p->next = p;
		seed_url_p = seed_url_p->next;
	}
	
	return 0;
}

/* 查询文章url，并存入st中 */
int pa_article_url_inquire(article_url_st *st)
{
	article_url_st *p;
	MYSQL_RES *g_res; 		// mysql 记录集
	MYSQL_ROW g_row; 		// 字符串数组，mysql 记录行
	//int iNum_rows = 0;		// 得到记录的行数
	//int iNum_fields = 0;	// 得到记录的列数

	char sql[PA_BUF_SIZE] = "\0";
	sprintf(sql, "SELECT * FROM `%s`", db_config.article_table);
	
	if(pa_executesql(sql))
	{
		pa_err((char *)mysql_error(&pa_mysql));
		return -1;
	}
	
	g_res = mysql_store_result(&pa_mysql); 		// 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集
	//iNum_rows = mysql_num_rows(g_res); 			// 得到记录的行数
	//iNum_fields = mysql_num_fields(g_res); 		// 得到记录的列数
	
	/* mysql_fetch_row:获取一行数据,并保存到g_row中 */
	while((g_row=mysql_fetch_row(g_res)))
	{
		
		p = (article_url_st *)malloc(sizeof(article_url_st));
		memset(p->url, '\0', sizeof(p->url));
		memset(p->title, '\0', sizeof(p->title));
		memset(p->createtime, '\0', sizeof(p->createtime));
			
		p->uid = *(g_row[0]);
		strncpy(p->url, g_row[1], strlen(g_row[1]));
		strncpy(p->title, g_row[2], strlen(g_row[2]));
		p->status = *(g_row[3]);
		strncpy(p->createtime, g_row[4], strlen(g_row[4]));
		p->next = NULL;
		
		st->next = p;
		st = st->next;
	}
	return 0;
}

/* 插入文章url */
int pa_insert_article_link()
{
	char sql[PA_BUF_SIZE] = "\0";
	pa_article_url *p = pa_article_url_head.next;

	while(p) {
		memset(sql, '\0', sizeof(sql));
		sprintf(sql, "INSERT INTO %s (url, title, stat) VALUES ('%s', '%s')", 
			db_config.article_url_table, p->url, p->title, '0');
		pa_executesql(sql);
		p = p->next;
	}
}

/* 插入文章内容 */
int pa_insert_article_content(article_content_st *p)
{
	char sql[PA_PAGE_CONTENT_BUF] = "\0";
	
	sprintf(sql, "INSERT INTO %s (url, title, content) VALUES ('%s', '%s', '%s')", 
		db_config.article_table, p->url, p->title, p->content);
	
	pa_executesql(sql);
		
	return 0;
}

/* 执行sql语句 */
static int pa_executesql(const char *sql) 
{
	const char *ch = "SET NAMES 'utf8'";
	mysql_real_query(&pa_mysql, ch, strlen(ch));
	
	/*query the database according the sql*/
	if(mysql_real_query(&pa_mysql, sql, strlen(sql)))
	{
		pa_err((char *)mysql_error(&pa_mysql));
		return -1;
	}

	return 0;
}