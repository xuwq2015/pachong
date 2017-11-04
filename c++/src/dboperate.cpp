#include <dboperate.h>
#include <iostream>
#include <string.h>

using namespace std;

DbOperate::DbOperate()
{
	// init the database connection
	if(mysql_init(&pa_mysql) == NULL)
	{
		this->set_err((char *)mysql_error(&pa_mysql));
	} 
	else if(!mysql_real_connect(&pa_mysql, DB_HOST_NAME, DB_USER_NAME, DB_USER_PASSWD, 
		DB_NAME, DB_PORT, NULL, 0))
	{/* connect the database */
		this->set_err((char *)mysql_error(&pa_mysql));
	}
}
DbOperate::~DbOperate()
{
	mysql_close (&pa_mysql);	//关闭数据库连接
}

/* url种子表查询函数 */
int DbOperate::pa_seed_inquire(list<string> *seed_list)
{
	MYSQL_RES *g_res; 		// mysql 记录集
	MYSQL_ROW g_row; 		// 字符串数组，mysql 记录行
	//int iNum_rows = 0;		// 得到记录的行数
	//int iNum_fields = 0;	// 得到记录的列数
	const char *sql = "SELECT * FROM `seed_url`";
	
	if(pa_executesql(sql) == -1)
	{
		this->set_err((char *)mysql_error(&pa_mysql));
		return -1;
	}
	
	g_res = mysql_store_result(&pa_mysql); 		// 从服务器传送结果集至本地，mysql_use_result直接使用服务器上的记录集
	//iNum_rows = mysql_num_rows(g_res); 		// 得到记录的行数
	//iNum_fields = mysql_num_fields(g_res); 	// 得到记录的列数
	
	/* mysql_fetch_row:获取一行数据,并保存到g_row中 */
	while((g_row = mysql_fetch_row(g_res)))
	{
		seed_list->push_back(g_row[0]);
	}
	
	return 0;
}

/* 执行sql语句 */
int DbOperate::pa_executesql(const char *sql)
{
	const char *ch = "SET NAMES 'utf8'";
	mysql_real_query(&pa_mysql, ch, strlen(ch));
	
	/*query the database according the sql*/
	if(mysql_real_query(&pa_mysql, sql, strlen(sql)))
	{
		return -1;
	}

	return 0;
}

string DbOperate::get_db_err()
{
	return this->db_err;
}

void DbOperate::set_err(char *str)
{
	db_err.clear();
	db_err.append(str);
}