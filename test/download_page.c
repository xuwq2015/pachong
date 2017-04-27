#include <curl/curl.h>
#include "common.h"
#include "download_page.h"

int write_size = 0;
FILE *write_file_p = NULL; 

int pa_download_page(char *url, char *file_name) 
{
	write_file_p = fopen(file_name, "w+");
	if(write_file_p == NULL)
	{
		pa_err("pa_download_page:文件打开失败\n");
		return -1;
	}

	CURL *curl = curl_easy_init();
	if(curl == NULL)
        {
                char err_str[] = "get_head_thread:获取句柄失败";
                pa_err(err_str);
                return -1;
        }
	
	curl_easy_setopt(curl, CURLOPT_URL, url); //设置下载的URI
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        //设置超时
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        //屏蔽其它信号 
    	curl_easy_setopt(curl, CURLOPT_HEADER, 1);          //下载数据包括HTTP头部 
    	//curl_easy_setopt(curl, CURLOPT_RANGE, "0-500");     //用于断点续传, 设置下载的分片 
    	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);                      //输出body内容
    	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);                     //输出body内容
    	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

    	char buffer[PA_BUF_SIZE] = {0x0};
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, pa_curl_callback); //设置下载数据的回调函数 
    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

	curl_easy_perform(curl);
    	curl_easy_cleanup(curl);
    	//此时网站HTTP头信息已经存放在buffer内.
	
	fclose(write_file_p);
	return write_size;
}

/* curl回调函数 */
size_t pa_curl_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
        int ret = fwrite(ptr, size, nmemb, write_file_p);
	if(ret == -1)
	{
		pa_err("pa_curl_callback数据写入失败\n");	
		return size * nmemb;
	}
        write_size += ret;
    	return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
}
