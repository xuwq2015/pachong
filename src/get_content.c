#include <get_content.h>

static int data_cishu = 0;
static int data_size = 0;

int pa_start(char *pa_curl)
{
	char curl_ch[1024];
	strncpy(curl_ch, pa_curl, strlen(pa_curl));
	get_head_thread(curl_ch);	
	return 0;
}

void get_head_thread(char *ch) 
{ 
	printf("url:%s\n", ch);
    CURL *curl = curl_easy_init(); 
     

    curl_easy_setopt(curl, CURLOPT_URL, ch); //设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        //设置超时 
    //curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        //屏蔽其它信号 
    //curl_easy_setopt(curl, CURLOPT_HEADER, 1);          //下载数据包括HTTP头部 
    //curl_easy_setopt(curl, CURLOPT_RANGE, "0-500");     //用于断点续传, 设置下载的分片 
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);			//输出body内容
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);			//输出body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
     

    char buffer[MAXHEADLEN] = {0x0}; 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); //设置下载数据的回调函数 
    //curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);   


    curl_easy_perform(curl);   
    curl_easy_cleanup(curl); 
    //此时网站HTTP头信息已经存放在buffer内. 
    //
} 

size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	data_cishu++;
	FILE *fp = fopen("./cache/cache.html", "w+");
	int ret = fwrite(ptr, size, nmemb, fp);
	data_size += ret;
	printf("写入次数：%d;写入数据大小：%d\n", data_cishu, data_size);
    return size * nmemb;     //必须返回这个大小, 否则只回调一次, 不清楚为何. 
} 
