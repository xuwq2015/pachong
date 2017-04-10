#include <get_content.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static CURL *easyhandle = NULL;
static FILE *dfp = NULL;
#define FILE_NAME "./cache/cache.html"

int pa_start(char *pa_curl)
{
	char url_ch[1024] = {'\0'};
	strncpy(pa_curl, url_ch, strlen(pa_curl));

	//获取句柄
	easyhandle = curl_easy_init();
	if(easyhandle == NULL)
	{
		printf("获取句柄失败\n");
		return -1;
	}



	//设置url参数
	CURLcode ret_code = curl_easy_setopt(easyhandle, CURLOPT_URL, url_ch);
	if(ret_code)
	{
		printf("url设置错误\n");
		return -1;
	}

	//设置接收数据的回调函数
	ret_code = curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, pa_rec);
	if(ret_code)
	{
		printf("设置接收数据的回调函数失败\n");
		return -1;
	}

	//设置接收body内容
	if((ret_code = curl_easy_setopt(easyhandle, CURLOPT_NOBODY, 0)) != 0)
	{
		printf("设置接收budy内容参数错误\n");
		return -1;
	}
	


	//发送请求
	ret_code = curl_easy_perform(easyhandle);
	if(ret_code)
	{
		printf("请求发送失败\n");
		return -1;
	}

	return 0;
}

static size_t pa_rec(char *ptr, size_t size, size_t nmemb, void *userdata)
{
/*
	dfp = tmpfile();
	fwrite(ptr, size, nmemb, dfp);
	return 0;
*/
	int len = size * nmemb;
	int fd = open(FILE_NAME, O_RDWR);
	write(fd, ptr, len);
	close(fd);
}
