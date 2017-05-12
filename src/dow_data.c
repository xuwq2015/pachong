#include <dow_data.h>
#include <err_warn.h>
#include <curl/curl.h>
#include <common.h>
#include <string.h>

static char str_buf[PA_PAGE_CONTENT_BUF];

int pa_dow_data(char *url, char *data_str)
{
	memset(str_buf, '\0', sizeof(str_buf));
	
	CURL *curl = curl_easy_init();
	if(curl == NULL)
	{
		char err_str[] = "get_head_thread:获取句柄失败";
		pa_err(err_str);
		return;
	}
	
	curl_easy_setopt(curl, CURLOPT_URL, url); 				//设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        	//设置超时 
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        	//屏蔽其它信号 
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);          	//下载数据包括HTTP头部 
    //curl_easy_setopt(curl, CURLOPT_RANGE, "0-500");     	//用于断点续传, 设置下载的分片 
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);				//输出body内容
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);				//输出body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
     

    char buffer[PA_BUF_SIZE] = {0x0}; 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); //设置下载数据的回调函数 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);   


    curl_easy_perform(curl);   
    curl_easy_cleanup(curl); 
    //此时网站HTTP头信息已经存放在buffer内. 
	
	strncpy(data_str, str_buf, strlen(str_buf));
	return 0;
} 


/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	strncat(str_buf, ptr, size * nmemb);

    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
} 