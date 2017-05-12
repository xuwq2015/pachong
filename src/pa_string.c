#include <pa_string.h>
#include <string.h>

/*
 * 自定义字符串切割函数。
 * 从字符串src中将以start开头至end结尾的字符片段
 * 提取并保存到des中。
 * 成功则返回字符串end之后的指针，失败返回NULL。
 * */
char *pa_strtok(char *src, char *start, char *end, char *des)
{
	char *ch, *ch1;
	int str_size;
	
	ch = strstr(src, start);
	ch1 = strstr(ch, end);
	
	str_size = ch - ch1;
	if(str_size < 0)
		str_size *= -1;
	
	str_size += strlen(end);
	
	if(strncpy(des, ch, str_size) == NULL)
		return NULL;
	return strstr(ch1, start);	//str_size大小不包括结尾的'\0'
}

int pa_strtok_link(char *src, char *href, char *title)
{
	char *start = NULL, *end = NULL;
	int str_size = 0;
	
	start = strstr(src, "http://");
	if(start == NULL)
	{
		href = NULL;
		title = NULL;
		return -1;
	}
	end = strstr(start, "\"");
	str_size = start - end;
	if(str_size < 0)
		str_size *= -1;
	strncpy(href, start, str_size);
	
	start = strstr(src, "title=");
	if(start == NULL)
	{
		title = NULL;
		return -1;
	}
	start = strstr(start, "\"");		//将start指针指向title内容的第一个双引号地址
	start = start + 1;
	end = strstr(start, "\"");
	str_size = start - end;
	if(str_size < 0)
		str_size *= -1;
	strncpy(title, start, str_size);
	
	return 0;
}