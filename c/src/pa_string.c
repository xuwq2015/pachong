#include <pa_string.h>
#include <stdlib.h>
#include <time.h>
#include <iconv.h>
#include <common.h>

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
	ch1 = strstr(ch + 1, end);
	
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
	ch1 = strstr(ch + 1, end);
	
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

/*
 * 在不知需要拷贝多少字符的情况下，将以src为开头至end
 * 之间的所有字符拷贝至des中，并在末尾添加'\0'。
 * 参数说明：
 * src：需要拷贝的字符串的开头
 * end：需要拷贝的字符串的结尾
 * 返回值：
 * 拷贝成功返回拷贝的字符串的个数（不包括结尾的'\0'），
 * 失败则返回-1；
 *
 * 注意：des的大小=需拷贝的字符串的个数+'\0'，
 * 在整个要拷贝的字符串之间不得有多个end字符。
 * */
int pa_strcpy(char *src, char *end, char *des)
{
	int cpy_size = 0;
	char *ch;
	
	ch = strstr(src, end);
	if(ch == NULL)
		return -1;
	
	cpy_size = src - ch;
	if(cpy_size < 0)
		cpy_size *= -1;
	
	if(sizeof(des) < (cpy_size + 1))
		return -1;
	strncpy(des, src, cpy_size + 1);
	
	return cpy_size;
}

/* 字符替换
 * 将字符串str中的original字符替换成new字符
 */
int pa_strrep(char *str, char original, char new)
{
	char *ch = NULL;
	int num = 0;

	while((ch = strchr(str, original)) != NULL) {
		num++;
		ch[0] = new;
	}
	return num;
}

/* 在url中提取域名，并拷贝到domain中 */
int pa_extract_domain(char *url, char *domain)
{
	char *ch = NULL;
	char *ch1 = NULL;
	char buf[PA_BUF_SIZE] = "\0";

	strncpy(buf, url, strlen(url));
	
	if(strstr(buf, "http://") != NULL)
		ch = buf + 7;
	else 
		ch = buf;
	
	if((ch1 = strchr(ch, '/')) != NULL)
		ch1[0] = '\0';
	if(ch != NULL)
		strncpy(domain, ch, strlen(ch));
	return 0;
}

/* 提取下一页连接地址 */
int pa_extract_next_addr(char *str, char *addr)
{
	char *ch;
	char buf[PA_BUF_SIZE]= "\0";
	char in_buf[PA_BUF_SIZE] = "\0";
	char out_buf[PA_BUF_SIZE] = "\0";

	strncpy(in_buf, str, strlen(str));
	code_convert("gb2312", "utf-8", in_buf, strlen(in_buf), out_buf, sizeof(out_buf));
	code_convert("gb2312", "utf-8", "下一页", strlen("下一页"), buf, sizeof(buf));
	if((ch = strstr(out_buf, buf)) == NULL)
		return -1;
	ch[0] = '\0';
	if((ch = strstr(out_buf, "<a")) == NULL)
		return -1;
	pa_strtok_link(ch, addr, ch);
	if(pa_strtok_link(ch, addr, ch) == -1)
		return -1;
	return 0;
}

//产生长度为length的随机字符串    
int gen_random_string(int length, char *ouput)  
{  
    int flag, i;  
    srand((unsigned int)time(NULL));
    for (i = 0; i < length - 1; i++)  
    {  
        flag = rand() % 3;  
        switch (flag)  
        {  
        case 0:  
            ouput[i] = 'A' + rand() % 26;  
            break;  
        case 1:  
            ouput[i] = 'a' + rand() % 26;  
            break;  
        case 2:  
            ouput[i] = '0' + rand() % 10;  
            break;  
        default:  
            ouput[i] = 'x';  
            break;  
        }  
    }  
    return 0;  
} 

/* 代码转换:从一种编码转为另一种编码 */
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;
 
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) 
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, (size_t *)&inlen, pout, (size_t *)&outlen) == -1) {
		iconv_close(cd);
		return -1;
	}
	
	iconv_close(cd);
	return 0;
}

int pa_match_strs(char *str, char *pa_rule, pa_connec_a *ret_str)
{
	regex_t reg;
	regmatch_t pm[3];
	int  iret = 0;
	int len = 0;
	char buffer[PA_BUF_SIZE] = "\0";

	memset(ret_str->href, '\0', sizeof(ret_str->href));
	memset(ret_str->title, '\0', sizeof(ret_str->title));

	iret = regcomp(&reg, pa_rule, REG_EXTENDED|REG_NEWLINE);
	if (iret != 0)
	{  
		regerror(iret, &reg, buffer, sizeof(buffer));
		pa_error("regcomp: ", buffer);
        return -1;  
    }
	iret = regexec(&reg, str, 3, pm, 0);
	if(iret == REG_NOMATCH)
	{
		//regerror(iret, &reg, buffer, sizeof(buffer));
		//pa_error("regexec: ", buffer);
		return -1;
	}
	len = pm[1].rm_eo - pm[1].rm_so;
	strncpy(ret_str->href, &str[pm[1].rm_eo], len);
	
	len = pm[2].rm_eo - pm[2].rm_so;
	strncpy(ret_str->title, &str[pm[2].rm_eo], len);
	return 0;
}

/* 
 * 通过正则表达式获取str中的连接 
 * str:源字符串
 * ret_str:从str中匹配到的字符串，是此函数的返回值
 * */
int pa_match_str(char *str,char *pa_rule, char *ret_str)
{
	regex_t reg;
	regmatch_t pm[2];
	int  iret = 0;
	int index_start = 0, index_end = 0;
	char buffer[PA_BUF_SIZE] = "\0";

	iret = regcomp(&reg, pa_rule, REG_EXTENDED|REG_NEWLINE);
	if (iret != 0)
	{  
		regerror(iret, &reg, buffer, sizeof(buffer));
		pa_error("regcomp: ", buffer);
        return -1;  
    }
	iret = regexec(&reg, str, 2, pm, 0);
	if(iret == REG_NOMATCH)
	{
		regerror(iret, &reg, buffer, sizeof(buffer));
		pa_error("regexec: ", buffer);
		return -1;
	}
	index_start = pm[1].rm_so;
	index_end = pm[1].rm_eo;
	strncpy(ret_str, &str[index_start], (index_end - index_start));
	return 0;
}