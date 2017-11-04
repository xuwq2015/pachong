/*
 *通过种子url获取文章url，并保存到数据库中
 **/

#include <get_seed.h>
#include <db_option.h>
#include <err_warn.h>
#include <string.h>

pa_seed_url pa_seed_head;
pa_article_url pa_article_url_head;
extern web_config web_config_head;

/* 获取种子页面（文章列表页）内的所有文章url
	并写入数据库 */
void pa_get_seed_content()
{
	FILE *fp;
	char next_url[PA_BUF_SIZE];
	char down_file[PA_BUF_SIZE] = "\0";
	pa_seed_url *p = pa_seed_head.next;
	
	/* 开始下载种子页面数据 */
	while(p != NULL)
	{
		memset(p->file, '\0', sizeof(p->file));
		if(pa_dow_data(p->url, p->file) == -1) {
			memset(p->file, '\0', sizeof(p->file));
		}
		p = p->next;
	}

	/* 从已下载的分类页面中提取下一页，直至将所有页面全部下载 */
	p = pa_seed_head.next;
	
	while(p != NULL) {
		web_config *web_config_p = pa_get_web_config_p(p->url);
		
		memset(down_file, '\0', sizeof(down_file));
		strncpy(down_file, p->file, strlen(p->file));

		while(1) {
			memset(next_url, '\0', sizeof(next_url));
			if((pa_get_next_page(web_config_p, down_file, next_url)) != 0)
				break;
			memset(down_file, '\0', sizeof(down_file));
			if(pa_dow_data(next_url, down_file))
				break;
			pa_get_article_link(web_config_p, down_file);
		}
		p = p->next;
	}

	pa_free_seed_list();
	
}

static void pa_free_seed_list()
{
	pa_seed_url *url_next;
	pa_seed_url *url_p = pa_seed_head.next;
	
	/* 释放种子url链表 */
	while(url_p != NULL)
	{
		url_next = url_p->next;
		//remove(url_p->file);
		free(url_p);
		url_p = url_next;
	}
}

/*
 * 获取列表页所有文章标题和文章url，
 * 并保存到数据库中
 **/
static int pa_get_article_link(web_config *web_config_p, char *file_name)
{
	FILE *fp = NULL;
	int article_url_status = 0;
	char buf[PA_BUF_SIZE] = "\0";
	char ch[2][PA_BUF_SIZE] = {"\0", "\0"};
	pa_article_url *p1, *p = &pa_article_url_head;
	pa_connec_a connec_a;

	if((fp = fopen(file_name, "r")) == NULL) {
		pa_errorno(file_name, "File failed to open");
		return -1;
	}

	while(!feof(fp)) {
		memset(buf, '\0', sizeof(buf));
		if(fgets(buf, sizeof(buf), fp) == NULL)
			continue;
		if(strstr(buf, web_config_p->article_start) != NULL)
			article_url_status = 1;
		if(strstr(buf, web_config_p->article_end) != NULL)
			article_url_status = 0;
		if(article_url_status) {
			if(pa_match_strs(buf, web_config_p->article_url_rule, &connec_a))
				continue;
			p1 = (pa_article_url *)malloc(sizeof(pa_article_url));
			memset(p1->title, '\0', sizeof(p1->title));
			memset(p1->url, '\0', sizeof(p1->url));
			p1->next = NULL;

			strncpy(p1->url, connec_a.href, sizeof(connec_a.href));
			strncpy(p1->title, connec_a.title, sizeof(connec_a.title));
			pa_warns("href: ", p1->url);
			pa_warns("title: ", p1->title);

			p->next = p1;
			p = p->next;
		}
	}
	
	fclose(fp);
	pa_insert_article_link();
	return 0;
}

/*
 * 此函数用于判断目录页是否有下一页，如果有则下载下一页，
 * 并返回1。如果没有则返回0；
 **/
static int pa_get_next_page(web_config *web_config_p, char *file_name, char *next_url)
{
	FILE *fp = NULL;
	char ch[PA_BUF_SIZE] = "\0";
	char buf[PA_BUF_SIZE] = "\0";
	char domain[PA_BUF_SIZE] = "\0";
	strncpy(domain, web_config_p->url, sizeof(web_config_p->url));

	if((fp = fopen(file_name, "r")) == NULL)
		return -1;
	while(!feof(fp)) {
		memset(buf, '\0', sizeof(buf));
		if(fgets(buf, sizeof(buf), fp) == NULL)
			continue;
		if(strstr(buf, web_config_p->next_page) == NULL)
			continue;
		memset(ch, '\0', sizeof(ch));
		memset(next_url, '\0', sizeof(next_url));
		if(pa_match_str(buf, web_config_p->next_page_rule, ch) == 0)
			sprintf(next_url, "%s%s", domain, ch);
		break;
	}
	
	fclose(fp);
	if(strlen(next_url) == 0)
		return -1;
	return 0;
}

/* 根据url获取相应的网站配置信息，并将数据结构指针返回 */
static web_config *pa_get_web_config_p(char *url) 
{
	char domain[PA_BUF_SIZE] = "\0";
	web_config *web_config_p = &web_config_head;

	//获取网站域名
	pa_extract_domain(url, domain);
	while(web_config_p) {
		if(!strcmp(web_config_p->url, domain))
			break;
		web_config_p = web_config_p->next;
	}
	if(web_config_p == NULL)
		return NULL;
	else
		return web_config_p;
}