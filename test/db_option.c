#include "db_option.h"
#include "common.h"
#include "err_warn.h"
#include <stdlib.h>

/* 初始化连接 */
int pa_init_mysql(MYSQL *g_conn) 
{ 	
	// init the database connection
	if(mysql_init(g_conn) == NULL)
	{
		pa_err("pa_init_mysql:数据库初始化失败。");
		return -1;
	}
 
	/* connect the database */
	if(!mysql_real_connect(g_conn, DB_HOST_NAME, DB_USER_NAME, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0))
		return -1;
 
	return 0;
}

/* url种子表查询函数 */
int pa_seed_inquire(MYSQL *g_conn, pa_seed_url *seed_url_p)
{
	MYSQL_RES *g_res; 		// mysql 记录集
	MYSQL_ROW g_row; 		// 字符串数组，mysql 记录行
	int iNum_rows = 0;		// 得到记录的行数
	//int iNum_fields = 0;	// 得到记录的列数
	pa_seed_url *p;
	const char *sql = "SELECT * FROM `seed_url`";
	
	if(pa_executesql(g_conn, sql))
	{
		pa_err("pa_seed_inquire: 表seed查询失败。");
		return -1;
	}
	
	g_res = mysql_store_result(g_conn); 		// 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集
	iNum_rows = mysql_num_rows(g_res); 			// 得到记录的行数
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

/* 执行sql语句 */
static int pa_executesql(MYSQL *g_conn, const char *sql) 
{
	/*query the database according the sql*/
	if(mysql_real_query(g_conn, sql, strlen(sql)))
	{
		pa_err("pa_executesql: sql语句执行失败。");
		return -1;
	}

	return 0;
}