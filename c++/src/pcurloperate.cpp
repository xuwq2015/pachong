#include <pcurloperate.h>
#include <string.h>
#include <stdio.h>
#include <fstream>

using namespace std;
char temp_file[PA_BUF_SIZE];

PcurlOperate::PcurlOperate()
{	
	curl_global_init(CURL_GLOBAL_ALL);  
}

PcurlOperate::~PcurlOperate()
{
	curl_global_cleanup();
}

int PcurlOperate::down(char *str)
{
	CURLcode res;
	
	char *ch = strrchr(str, '/');
	ch = tmpnam(ch);
	memset(temp_file, '\0', sizeof(temp_file));
	strncpy(temp_file, ch, strlen(ch));

	curl = curl_easy_init();
	if(curl == NULL)
	{
		set_err("get_head_thread:获取句柄失败");
	}
	curl_easy_setopt(curl, CURLOPT_URL, str);	//设置下载的URI 
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);							//报告每一件意外的事情
	//curl_easy_setopt(curl, CURLOPT_TIMEOUT, 200);        				//设置超时 
	//curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        				//屏蔽其它信号 
	//curl_easy_setopt(curl, CURLOPT_HEADER, 1);          				//获取HTTP头部  
	//curl_easy_setopt(curl, CURLOPT_NOBODY, 0);							//获取body内容
	//curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);					//自动301，302跳转
 	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); 	//设置保存下载数据的回调函数
	//set_http_head(str);												//设置http请求头
	res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		set_err((char *)curl_easy_strerror(res));
		curl_easy_cleanup(curl);
		return -1;
	}
	curl_easy_cleanup(curl); 
	return 0;
}

void PcurlOperate::set_http_head(char *url)
{
	char *ch = NULL;
	char host[PA_BUF_SIZE] = {'\0'};
	char referef[PA_BUF_SIZE] = {'\0'};

	if(strstr(url, "http://") != NULL) {
		ch = &(url[7]);
	} else {
		ch = url;
	}
	if(strstr(ch, "www.") == NULL) {
		strncpy(host, "www.", 4);
		strncat(host, ch, strchr(ch, '/') - ch);
	} else {
		strncpy(host, "www.", 4);
	}
	if(strchr(url, '/') != NULL) {
		strncat(host, ch, strchr(ch, '/') - ch);
	} else {
		strncat(host, ch, strlen(ch));
	}

	strncpy(referef, "Referer:", 8);
	strncat(referef, url, strlen(url));
	
	struct curl_slist *headers=NULL; 									
	headers = curl_slist_append(headers, "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8");
	headers = curl_slist_append(headers, "Accept-Encoding:gzip, deflate");
	headers = curl_slist_append(headers, "Accept-Language:zh-CN,zh;q=0.8");
	headers = curl_slist_append(headers, "Connection:keep-alive");
	headers = curl_slist_append(headers, "Cookie:ixaeareturnurl=http%3A%2F%2Fwww.113mm.com%2Fjiepaimeitui%2F; AJSTAT_ok_pages=8; AJSTAT_ok_times=1");
	headers = curl_slist_append(headers, "DNT:1");
	headers = curl_slist_append(headers, host);
	headers = curl_slist_append(headers, "If-Modified-Since:Tue, 10 Oct 2017 02:20:44 GMT");
	headers = curl_slist_append(headers, "If-None-Match:\"ba1ea1606e41d31:0\"");
	headers = curl_slist_append(headers, referef);
	headers = curl_slist_append(headers, "Upgrade-Insecure-Requests:1");
	headers = curl_slist_append(headers, "User-Agent:Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

//获取以下载的内容
void PcurlOperate::get_down_content(char *str)
{
	strncpy(str, temp_file, strlen(temp_file));
	return;
}

void PcurlOperate::set_err(char *str)
{
	memset(err_str, '\0', sizeof(err_str));
	err = -1;
	strncpy(err_str, str, strlen(str));
}

/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp)
{
	ofstream file;
	file.open(temp_file, std::ifstream::out | std::ifstream::app);

	if(file.is_open()) {
		file.write((const char*)ptr, size * nmemb);
	}
	file.close();

    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何.
}