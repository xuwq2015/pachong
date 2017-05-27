/*
 * libcurl库相关操作，主要用来下载网页内容
 */

#include <dow_data.h>
#include <err_warn.h>
#include <curl/curl.h>
#include <common.h>
#include <string.h>

extern char dow_content_buf[PA_PAGE_CONTENT_BUF];

int pa_dow_data(char *url)
{
	char strerr[PA_BUF_SIZE] = "\0";
	char head_buffer[PA_BUF_SIZE] = {0x0};
	CURLcode res;
	CURL *curl = curl_easy_init();
		
	memset(dow_content_buf, '\0', sizeof(dow_content_buf));
	
	if(curl == NULL)
	{
		char err_str[] = "get_head_thread:获取句柄失败";
		pa_err(err_str);
		return -1;
	}
	
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);						//报告每一件意外的事情
	curl_easy_setopt(curl, CURLOPT_URL, url); 							//设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        				//设置超时 
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        				//屏蔽其它信号 
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);          				//获取HTTP头部  
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);							//获取body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);					//自动301，302跳转
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); 	//设置下载数据的回调函数  

    res = curl_easy_perform(curl);   
	if(res != CURLE_OK) {
		sprintf(strerr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
		pa_warn(strerr);
		
		curl_easy_cleanup(curl);
		return -1;
	}
	
    curl_easy_cleanup(curl); 
	return 0;
} 

/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	strncat(dow_content_buf, ptr, size * nmemb);
    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
} 