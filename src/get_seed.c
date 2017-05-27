/*
 *通过种子url获取文章url，并保存到数据库中
 **/

#include <get_seed.h>
#include <db_option.h>
#include <err_warn.h>
#include <string.h>
#include <pa_string.h>

extern char dow_content_buf[PA_PAGE_CONTENT_BUF];
extern pa_seed_url pa_seed_head;

/* 获取种子页面（文章列表页）内的所有文章url
	并写入数据库 */
void pa_get_seed()
{
	char dow_url[PA_BUF_SIZE] = "\0";
	char next_url[PA_BUF_SIZE] = "\0";
	pa_seed_url *p = NULL;
	
	
	/* 开始提取种子页面数据 */
	p = pa_seed_head.next;
	while(p)
	{
		strncpy(dow_url, p->url, strlen(p->url));
		while(1)
		{
			memset(dow_content_buf, '\0', sizeof(dow_content_buf));
			pa_dow_data(dow_url, dow_content_buf);
			pa_get_article_link();
			
			if(pa_get_next_page(next_url)) {
				if(!strcmp(next_url, dow_url)) {
					break;
				} else {
					memset(dow_url, '\0', sizeof(dow_url));
					strncpy(dow_url, next_url, strlen(next_url));
					memset(next_url, '\0', sizeof(next_url));
				}	
			} else {
				break;
			}
		}
		memset(dow_url, '\0', sizeof(dow_url));
		p = p->next;
	}
}

/*
 * 获取列表页所有文章标题和文章url，
 * 并保存到数据库中
 **/
static int pa_get_article_link()
{
	char ch1[2][PA_PAGE_CONTENT_BUF] = {"\0", "\0"};
	char *ch[4] = {"<li class=\"i_list list_n2\">", 
					"</li>", "<a", ">"};
	char href[PA_BUF_SIZE] = {'\0'};
	char title[PA_BUF_SIZE] = {'\0'};
	char *start = dow_content_buf, *end = NULL;
	int str_size = 0;
	
	while(start != NULL)
	{
		if((start = pa_strtok(start, ch[0], ch[1], ch1[0])) == NULL)
			break;
		
		if(pa_strtok(ch1[0], ch[2], ch[3], ch1[1]) == NULL)
			continue;
		
		if(pa_strtok_link(ch1[1], href, title))
			continue;

		pa_insert_article_link(href, title);
		memset(ch1[0], '\0', sizeof(ch1[0]));
		memset(ch1[1], '\0', sizeof(ch1[1]));
		memset(href, '\0', sizeof(href));
		memset(title, '\0', sizeof(title));
	}
}

/*
 * 此函数用于判断目录页是否有下一页，如果有则将下一页的url存入next_url中，
 * 并返回1。如果没有则返回0；
 **/
static int pa_get_next_page(char *next_url)
{
	int ret_num = 0;
	char *str_buf = dow_content_buf;
	char *ch[] = {"<a class=\"next page-numbers\"", ">"};
	char ch1[PA_BUF_SIZE] = {"\0"};
	char href[PA_BUF_SIZE] = "\0";
	char title[PA_BUF_SIZE] = "\0";
	
	if(pa_strtok_r(str_buf, ch[0], ch[1], ch1) == -1)
		return 0;
	
	ret_num = pa_strtok_link(ch1, href, title);
	if(ret_num == -1 || ret_num == 2) {
		return 0;
	}
	
	strncpy(next_url, href, strlen(href));
	return 1;
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