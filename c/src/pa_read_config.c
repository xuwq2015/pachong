#include <pa_read_config.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pa_string.h>

extern db_config_st db_config;
extern char log_file[PA_BUF_SIZE];
extern char down_path[PA_BUF_SIZE];
web_config web_config_head;
static char web_config_path[PA_BUF_SIZE];

int pa_init_config()
{
	DIR *dir = NULL;
	FILE *fp = NULL;
	struct dirent *ptr;
	char conf_file[PA_BUF_SIZE] = {"\0"};

	init_default_config();
	
	/* 读取主配置文件 */
	sprintf(conf_file, "%s/%s", PA_CONFIG_DIR, PA_CONFIG_FILE);
	fp = fopen(conf_file, "r");
	if(fp == NULL) {
		pa_errorno(conf_file, "file failed to open");
		return -1;
	} else {
		read_main_config(fp);
	}
	fclose(fp);

	/* 读取web配置文件 */
	web_config *p = &web_config_head;
	if((dir = opendir(web_config_path)) == NULL) {
		pa_errorno(web_config_path, "The web_config directory opens failed");
		return -1;
	}
	while((ptr = readdir(dir)) != NULL) {
		if((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
			continue;
		
		memset(conf_file, '\0', sizeof(conf_file));
		sprintf(conf_file, "%s/%s", web_config_path, ptr->d_name);
		if((fp = fopen(conf_file, "r")) == NULL) {
			pa_errorno(conf_file, "file failed to open");
			continue;
		}
		read_web_config(fp, p);
		fclose(fp);
		p = p->next;
	}
}

static int init_default_config()
{
	/* 初始化默认的数据库配置信息 */
	memset(db_config.type, '\0', sizeof(db_config.type));
	memset(db_config.host, '\0', sizeof(db_config.host));
	memset(db_config.user, '\0', sizeof(db_config.user));
	memset(db_config.passwd, '\0', sizeof(db_config.passwd));
	memset(db_config.name, '\0', sizeof(db_config.name));
	memset(db_config.seed_table, '\0', sizeof(db_config.seed_table));
	memset(db_config.article_table, '\0', sizeof(db_config.article_table));
	memset(db_config.article_url_table, '\0', sizeof(db_config.article_url_table));

	db_config.port = DB_PORT;
	strncpy(db_config.type, DB_TYPE, sizeof(DB_TYPE));
	strncpy(db_config.host, DB_HOST_NAME, sizeof(DB_HOST_NAME));
	strncpy(db_config.user, DB_USER_NAME, sizeof(DB_USER_NAME));
	strncpy(db_config.passwd, DB_USER_PASSWD, sizeof(DB_USER_PASSWD));
	strncpy(db_config.name, DB_NAME, sizeof(DB_NAME));
	strncpy(db_config.seed_table, DB_SEED_TABLE, sizeof(DB_SEED_TABLE));
	strncpy(db_config.article_table, DB_ARTICLE_TABLE, sizeof(DB_ARTICLE_TABLE));
	strncpy(db_config.article_url_table, DB_ARTICLE_URL_TABLE, sizeof(DB_ARTICLE_URL_TABLE));
	

	/* 初始化log默认配置信息 */
	memset(log_file, '\0', sizeof(log_file));
	strncpy(log_file, PA_LOG_FILE, strlen(PA_LOG_FILE));

	/* 初始化web配置默认目录 */
	memset(web_config_path, '\0', sizeof(web_config_path));
	sprintf(web_config_path, "%s/%s", PA_CONFIG_DIR, PA_WEB_CONFIG_PATH);

	/* 初始化下载缓存默认目录 */
	memset(down_path, '\0', sizeof(down_path));
	strncpy(down_path, PA_DOWN_BUF_PATH, strlen(PA_DOWN_BUF_PATH));
	
	return 0;
}

/* 读取主配置文件 */
static int read_main_config(FILE *fp)
{
	char buf[PA_BUF_SIZE] = {"\0"};
	char key_name[PA_BUF_SIZE] = {"\0"};
	char key_value[PA_BUF_SIZE] = {"\0"};

	while(!(feof(fp))) {
		memset(key_name, '\0', sizeof(key_name));
		memset(key_value, '\0', sizeof(key_value));
		memset(buf, '\0', sizeof(buf));
		
		if(fgets(buf, sizeof(buf), fp) == NULL)
			continue;
		if((get_conf_value(buf, key_name, key_value)) > 0) {
			rep_main_config_info(key_name, key_value);
		}
	}
}

/* 读取web配置文件 */
static int read_web_config(FILE *fp, web_config *p)
{
	char buf[PA_BUF_SIZE] = {"\0"};
	char key_name[PA_BUF_SIZE] = {"\0"};
	char key_value[PA_BUF_SIZE] = {"\0"};
	
	web_config *p_next;
	p_next = (web_config *)malloc(sizeof(web_config));
	p_next->next = NULL;
	p->next = p_next;

	while(!(feof(fp))) {
		memset(key_name, '\0', sizeof(key_name));
		memset(key_value, '\0', sizeof(key_value));
		memset(buf, '\0', sizeof(buf));
		
		if(fgets(buf, sizeof(buf), fp) == NULL)
			continue;
		if((get_conf_value(buf, key_name, key_value)) > 0) {
			rep_web_config(key_name, key_value, p_next);
		}
	}

}

/* 根据从配置文件中读取到的配置信息 
 * 替换掉默认的配置信息
 */
static int rep_main_config_info(char *key_name, char *key_value)
{
	if(!strcmp(key_name, "db_type")) {
		memset(db_config.type, '\0', sizeof(db_config.type));
		strncpy(db_config.type, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_host")) {
		memset(db_config.host, '\0', sizeof(db_config.host));
		strncpy(db_config.host, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_user")) {
		memset(db_config.user, '\0', sizeof(db_config.user));
		strncpy(db_config.user, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_passwd")) {
		memset(db_config.passwd, '\0', sizeof(db_config.passwd));
		strncpy(db_config.passwd, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_name")) {
		memset(db_config.name, '\0', sizeof(db_config.name));
		strncpy(db_config.name, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_port")) {
		int port = 0, i = 0;
		for(i = 0; i < strlen(key_value); i++) {
			port = port * 10;
			port = port + (key_value[i] - '0');
		}
		db_config.port = port;
		return 0;
	}
	if(!strcmp(key_name, "db_seed_table")) {
		memset(db_config.seed_table, '\0', sizeof(db_config.seed_table));
		strncpy(db_config.seed_table, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "db_article_url_table")) {
		memset(db_config.article_url_table, '\0', sizeof(db_config.article_url_table));
		strncpy(db_config.article_url_table, key_value, strlen(key_value));
	}
	if(!strcmp(key_name, "db_article_table")) {
		memset(db_config.article_table, '\0', sizeof(db_config.article_table));
		strncpy(db_config.article_table, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "log_file")) {
		memset(log_file, '\0', sizeof(log_file));
		strncpy(log_file, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "web_config")) {
		memset(web_config_path, '\0', sizeof(web_config_path));
		strncpy(web_config_path, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "down_buf")) {
		memset(down_path, '\0', sizeof(down_path));
		strncpy(down_path, key_value, strlen(key_value));
		return 0;
	}
	return -1;
}

static int rep_web_config(char *key_name, char *key_value, web_config *p)
{
	if(!strcmp(key_name, "web_url")) {
		memset(p->url, '\0', sizeof(p->url));
		strncpy(p->url, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "web_type")) {
		p->type = key_value[0] - '0';
		return 0;
	}
	if(!strcmp(key_name, "article_start")) {
		memset(p->article_start, '\0', sizeof(p->article_start));
		strncpy(p->article_start, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "article_end")) {
		memset(p->article_end, '\0', sizeof(p->article_end));
		strncpy(p->article_end, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "article_url_rule")) {
		memset(p->article_url_rule, '\0', sizeof(p->article_url_rule));
		strncpy(p->article_url_rule, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "next_page")) {
		memset(p->next_page, '\0', sizeof(p->next_page));
		strncpy(p->next_page, key_value, strlen(key_value));
		return 0;
	}
	if(!strcmp(key_name, "next_page_rule")) {
		memset(p->next_page_rule, '\0', sizeof(p->next_page_rule));
		strncpy(p->next_page_rule, key_value, strlen(key_value));
		return 0;
	}
	return -1;
}

/* 获取键值 */
static int get_conf_value(char *conf, char *key_name, char *key_value)
{
	int len = 0;
	char *ch = NULL;

	//空行
	if(strlen(conf) == 0)
		return 0;
	//以#开头的注释行
	if(conf[0] == '#')
		return 0;
	
	pa_strrep(conf, '\n', '\0');		//去掉换行符
	pa_strrep(conf, '\r', '\0');		//去掉换行符
	if((ch = strchr(conf, ' ')) == NULL)
		return -1;

	//计算等号的位置
	len = ch - conf;
	if(len < 0)
		len = len * -1;
	
	strncpy(key_name, conf, len);
	len++;
	strncpy(key_value, conf + len, strlen(conf + len));
	return 1;
}



