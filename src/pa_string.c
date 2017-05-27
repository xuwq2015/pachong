#include <pa_string.h>
#include <string.h>

/*
 * 自定义字符串切割函数。
 * 从字符串src中将以start开头至end结尾的字符片段
 * 提取并保存到des中。
 * 成功则返回end指针，失败返回NULL。
 * */
char *pa_strtok(char *src, char *start, char *end, char *des)
{
	char *ch, *ch1;
	int str_size;
	
	ch = strstr(src, start);
	if(ch == NULL)
		return NULL;
	ch1 = strstr(ch, end);
	
	str_size = ch - ch1;
	if(str_size < 0)
		str_size *= -1;
	
	str_size += strlen(end);
	strncpy(des, ch, str_size);
	
	return ch1;
}

/*
 * 自定义字符串切割函数。
 * 从字符串src中将以start开头至end结尾的字符片段
 * 提取并保存到des中。
 * 成功则返回0,失败返回-1。
 * */
int pa_strtok_r(char *src, char *start, char *end, char *des)
{
	char *ch, *ch1;
	int str_size;
	
	ch = strstr(src, start);
	if(ch == NULL)
		return -1;
	ch1 = strstr(ch, end);
	
	str_size = ch - ch1;
	if(str_size < 0)
		str_size *= -1;
	
	str_size += strlen(end);
	strncpy(des, ch, str_size);
	
	return 0;
}

/* 获取两个标签之间的内容，如：<h1>要获取的内容</h1> */
int pa_get_center(char *src, char *start, char *end, char *des)
{
	char *ch, *ch1;
	int str_size;
	
	ch = strstr(src, start);
	if(ch == NULL)
		return -1;
	ch = ch + strlen(start);
	ch1 = strstr(ch, end);
	
	str_size = ch - ch1;
	if(str_size < 0)
		str_size *= -1;
	strncpy(des, ch, str_size);
	
	return 0;
}

/* 
 * 获取标签“img”中的标题与连接
 * 返回值：
 * 0：src和alt全部获取成功
 * 1：只获取到src
 * 2：只获取到alt
 * -1：src和alt全部获取失败
 **/
int pa_get_img_link(char *src, char *href, char *title)
{
	char *start = NULL, *end = NULL;
	int str_size = 0;
	int href_status = 0;
	int title_status = 0;
	
	
	/* 获取标签中的src */
	start = strstr(src, "http://");
	if(start == NULL) {
		href_status = 0;
	}else{
		end = strstr(start, "\"");			//指向最后一个双引号
		
		str_size = start - end;				//计算src大小
		if(str_size < 0)
			str_size *= -1;
		
		strncpy(href, start, str_size);
		href_status = 1;
	}

	
	/* 获取标签中的alt */
	start = strstr(src, "alt=");
	if(start == NULL){
		title_status = 0;
	} else {
		start = strstr(start, "\"");		
		start = start + 1;
		end = strstr(start, "\"");
		str_size = start - end;
		if(str_size < 0)
			str_size *= -1;
		strncpy(title, start, str_size);
		title_status = 1;
	}
	
	
	/* 计算返回值 */
	if(href_status) {
		if(title_status)
			return 0;
		else
			return 1;
	} else if(title_status) {
		return 2;
	} else {
		return -1;
	}
}

/* 
 * 获取标签“a”中的标题与连接
 * 返回值：
 * 0：href和title全部获取成功
 * 1：只获取到href
 * 2：只获取到title
 * -1：href和title全部获取失败
 **/
int pa_strtok_link(char *src, char *href, char *title)
{
	char *start = NULL, *end = NULL;
	int str_size = 0;
	int href_status = 0;
	int title_status = 0;
	
	
	/* 获取标签中的href */
	start = strstr(src, "href=");
	if(start == NULL) {
		href_status = 0;
	}else{
		start = strstr(start, "\"");		//将start指针指向href内容的第一个双引号地址
		start = start + 1;					//排除第一个双引号
		
		end = strstr(start, "\"");			//指向最后一个双引号
		
		str_size = start - end;				//计算href大小
		if(str_size < 0)
			str_size *= -1;
		
		strncpy(href, start, str_size);
		href_status = 1;
	}
	
	
	/* 获取标签中的title */
	start = strstr(src, "title=");
	if(start == NULL){
		title_status = 0;
	} else {
		start = strstr(start, "\"");		
		start = start + 1;
		end = strstr(start, "\"");
		str_size = start - end;
		if(str_size < 0)
			str_size *= -1;
		strncpy(title, start, str_size);
		title_status = 1;
	}
	
	
	/* 计算返回值 */
	if(href_status) {
		if(title_status)
			return 0;
		else
			return 1;
	} else if(title_status) {
		return 2;
	} else {
		return -1;
	}
}