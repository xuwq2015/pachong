#include <get_content.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static pa_link_st *pa_link_p = NULL;	//链表头指针
static int data_size = 0;				//下载的数据的总大小
static FILE *fp = NULL;					//网页下载时所有保存的文件指针


/* 开始函数 */
int pa_start(char *pa_curl)
{
	char url_ch[1024] = {'\0'};
	char file_name[FILENAME_SIZE] = {'\0'}; 

	strncpy(url_ch, pa_curl, strlen(pa_curl));
	pa_extract_filename(url_ch, file_name);	
	fp = fopen(file_name, "w+");
	if(fp == NULL)
	{
		char err_str[] = "pa_start:文件打开失败";
		pa_err(err_str);
		return -1;
	}


	get_head_thread(url_ch);
	fclose(fp);
	printf("\n");
	
	pa_extract_connection(file_name, pa_link_p);
	pa_free();
	return 0;
}


/* 获取网页内容 */
void get_head_thread(char *ch) 
{ 
    CURL *curl = curl_easy_init(); 
	if(curl == NULL)
	{
		char err_str[] = "get_head_thread:获取句柄失败";
		pa_err(err_str);
		return;
	}
     

    curl_easy_setopt(curl, CURLOPT_URL, ch); //设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        //设置超时 
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        //屏蔽其它信号 
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);          //下载数据包括HTTP头部 
    //curl_easy_setopt(curl, CURLOPT_RANGE, "0-500");     //用于断点续传, 设置下载的分片 
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);			//输出body内容
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);			//输出body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
     

    char buffer[MAXHEADLEN] = {0x0}; 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); //设置下载数据的回调函数 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);   


    curl_easy_perform(curl);   
    curl_easy_cleanup(curl); 
    //此时网站HTTP头信息已经存放在buffer内. 
} 


/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	int ret = fwrite(ptr, size, nmemb, fp);
	data_size += ret;
	char err_str[BUF_SIZE] = "写入数据大小:"; 
	char str[] = ((char)data_size + 'a');
	strncat(err_str, str, strlen(str)), 
	pa_warn(err_str);
    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
} 


/* 根据提供的url提取网页内容写入文件名 */
static int pa_extract_filename(char *url_ch, char *ret_filename)
{
	char file_name[FILENAME_SIZE] = {'\0'}; 
	int num = 0;

	//去掉"http://"
	if(strstr(url_ch, "http") != NULL)
	{
		url_ch = &url_ch[7];
	}

	//去掉字符串"www"
	if(strstr(url_ch, "www") != NULL)
	{
		url_ch = &url_ch[4];
	}
	
	strncpy(file_name, FILE_DIR, strlen(FILE_DIR));
	num = strlen(url_ch) - strlen(strchr(url_ch, '.'));
	strncat(file_name, url_ch, num);

	strncpy(ret_filename, file_name, strlen(file_name));
	return 0;
}


/* 释放链表 */
static int pa_free()
{
	if(pa_link_p)
		pa_link_st *next_p = pa_link_p->next;	
	else 
		return 0;

	while(pa_link_p)
	{
		free(pa_link_p);
		pa_link_p = next_p;
		next_p = pa_link_p->next;
	}
	return 0;
}
