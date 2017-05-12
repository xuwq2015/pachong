/*
 *通过种子url获取文章url，并保存到数据库中
 **/

#include <get_seed.h>
#include <db_option.h>
#include <err_warn.h>
#include <string.h>
#include <pa_string.h>

//保存下载的种子网页内容
static char str_buf[PA_PAGE_CONTENT_BUF];	

void pa_get_seed(MYSQL *pa_mysql, pa_seed_url *seed_url_p)
{
	char ret_str[PA_BUF_SIZE] = {'\0'};
	pa_seed_url *p = NULL;
	
	pa_seed_inquire(pa_mysql, seed_url_p);
	memset(str_buf, '\0', sizeof(str_buf));
	
	p = seed_url_p->next;
	while(p)
	{
		pa_warn(p->url);
		memset(str_buf, '\0', sizeof(str_buf));
		memset(ret_str, '\0', sizeof(ret_str));
		pa_dow_data(p->url, str_buf);
		pa_get_article_link(pa_mysql, str_buf);
		p = p->next;
	}
}

/*
 * 获取列表页所有文章内容
 **/
static int pa_get_article_link(MYSQL *pa_mysql, char *str)
{
	char ch1[2][PA_PAGE_CONTENT_BUF] = {"\0", "\0"};
	char *ch[4] = {"<li class=\"i_list list_n2\">", 
					"</li>", "<a", ">"};
	char href[PA_BUF_SIZE] = {'\0'};
	char title[PA_BUF_SIZE] = {'\0'};
	char *start = str, *end = NULL;
	int str_size = 0;
	
	while(start != NULL)
	{
		if((start = pa_strtok(start, ch[0], ch[1], ch1[0])) < 0)
		{
			pa_warn("字符串提取失败");
			continue;
		}
		
		if(pa_strtok(ch1[0], ch[2], ch[3], ch1[1]) < 0)
		{
			pa_warn("字符串提取失败");
			continue;
		}
		
		if(pa_strtok_link(ch1[1], href, title))
		{
			pa_warn("字符串提取失败");
			continue;
		}
		pa_insert_article_link(pa_mysql, href, title);
		memset(ch1[0], '\0', sizeof(ch1[0]));
		memset(ch1[1], '\0', sizeof(ch1[1]));
		memset(href, '\0', sizeof(href));
		memset(title, '\0', sizeof(title));
	}
}
/* 
 * 通过正则表达式获取str中的连接 
 * str:源字符串
 * ret_str:从str中匹配到的字符串，是此函数的返回值
 *
 * 此函数以弃用
 * */
static int pa_match_str(char *str, char *ret_str)
{
	char pa_rule[] = ".*<img class=\"waitpic\" src=\"([^\"]).*";
	regex_t reg;
	regmatch_t pm[2];
	int  iret = 0;
	int index_start = 0, index_end = 0;

	iret = regcomp(&reg, pa_rule, REG_EXTENDED|REG_NEWLINE);
	if (iret != 0)
	{  
        return -1;  
    }
	iret = regexec(&reg, str, 2, pm, 0);
	if(iret == REG_NOMATCH)
	{
		return -1;
	}
	index_start = pm[1].rm_so;
	index_end = pm[1].rm_eo;
	strncpy(ret_str, &str[index_start], (index_end - index_start));
	return 0;
}