#ifndef DBOPERAE_H
#define DBOPERAE_H

using namespace std;

#include <list> 
#include <string>
#include <mysql/mysql.h>

/* 数据库信息 */
#define DB_HOST_NAME "127.0.0.1"
#define DB_USER_NAME "pachong"
#define DB_USER_PASSWD "Pachong=123"
#define DB_NAME "pachong"
#define DB_PORT 3306
#define DB_ARTICLE_LINK_TABLE "essay_url"
#define DB_ARTICLE_CONTENT_TABLE "article_content"

class DbOperate
{
public:
	DbOperate();
	~DbOperate();
	int pa_seed_inquire(list<string> *seed_list);
	string get_db_err();
private:
	MYSQL pa_mysql;
	string db_err;
	
	int pa_executesql(const char *sql);
	void set_err(char *str);
};

#endif