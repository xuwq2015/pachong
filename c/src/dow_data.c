/*
 * libcurl库相关操作，主要用来下载网页内容
 */

#include <dow_data.h>
#include <err_warn.h>
#include <curl/curl.h>
#include <common.h>
#include <string.h>
#include <stdio.h>

FILE *down_fp = NULL;
char down_path[PA_BUF_SIZE];

int pa_init_curl()
{
	curl_global_init(CURL_GLOBAL_NOTHING);
}

int pa_cleanup_curl()
{
	curl_global_cleanup();		//关闭curl
}

int pa_dow_data(char *url, char *down_file)
{
	CURLcode res;
	CURL *curl = curl_easy_init();
	char buf[PA_BUF_SIZE] = {"\0"};

	memset(buf, '\0', sizeof(buf));
	memset(down_file, '\0', sizeof(down_file));
	gen_random_string(10, buf);
	sprintf(down_file, "%s/%s", down_path, buf);
	down_fp = NULL;
	
	if((down_fp = fopen(down_file, "a")) == NULL) {
		pa_errorno(down_file, "file failed to open");
		return -1;
	}
	fprintf(down_fp, "%s\n", url);
	
	if(curl == NULL)
	{
		pa_err("get_head_thread:获取句柄失败");
		return -1;
	}
	
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);						//报告每一件意外的事情
	curl_easy_setopt(curl, CURLOPT_URL, url); 							//设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 200);        				//设置超时 
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        				//屏蔽其它信号 
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);          				//获取HTTP头部  
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);							//获取body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);					//自动301，302跳转
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); 	//设置下载数据的回调函数  

    res = curl_easy_perform(curl);   
	if(res != CURLE_OK) {
		pa_warns("curl_easy_perform() failed:", curl_easy_strerror(res));
		fclose(down_fp);
		curl_easy_cleanup(curl);
		return -1;
	}

	fclose(down_fp);
	pa_warns("Downloaded", url);
	pa_warns("file name:", down_file);
    curl_easy_cleanup(curl); 
	return 0;
} 

/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	fwrite(ptr, size, nmemb, down_fp);
	//strncat(dow_content_buf, ptr, size * nmemb);
    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
} 