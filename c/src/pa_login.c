#include <pa_login.h>
#include <curl/curl.h>
#include <err_warn.h>

int pa_log_wordpress(char *wordpress_url)
{
	CURL *curl;
	CURLcode res;
	
	curl = curl_easy_init();
	if(curl == NULL)
	{
		char err_str[] = "pa_log_wordpress:获取句柄失败";
		pa_err(err_str);
		return -1;
	}
	
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE,"");					//初始化cookie引擎
    curl_easy_setopt(curl,CURLOPT_TIMEOUT,200);						//设置超时
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookie.txt");        //读取本地存储的cookie
	
	curl_easy_cleanup(curl);
	
	return 0;
}