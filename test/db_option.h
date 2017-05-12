#ifndef _DB_OPTION_H_
#define _DB_OPTION_H_

#include "common.h"
#include <mysql/mysql.h>

int pa_init_mysql(MYSQL*);							//初始化连接
static int pa_executesql(MYSQL*, const char*);		//执行sql语句
int pa_seed_inquire(MYSQL*, pa_seed_url*);			//url种子表查询函数

#endif