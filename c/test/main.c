#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "common.h"
#include "err_warn.h"

char dow_content_buf[PA_PAGE_CONTENT_BUF];

/* curl回调函数 */
size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp) 
{ 
	strncat(dow_content_buf, ptr, size * nmemb);
    return size * nmemb;     //必须返回这个大小
} 

size_t header_callback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	strncat(userdata, buffer, size * nitems);
	return size * nitems;
}

static
void dump(const char *text,
          FILE *stream, unsigned char *ptr, size_t size)
{
  size_t i;
  size_t c;
  unsigned int width=0x10;
 
  fprintf(stream, "%s, %10.10ld bytes (0x%8.8lx)\n",
          text, (long)size, (long)size);
 
  for(i=0; i<size; i+= width) {
    fprintf(stream, "%4.4lx: ", (long)i);
 
    /* show hex to the left */
    for(c = 0; c < width; c++) {
      if(i+c < size)
        fprintf(stream, "%02x ", ptr[i+c]);
      else
        fputs("   ", stream);
    }
 
    /* show data on the right */
    for(c = 0; (c < width) && (i+c < size); c++) {
      char x = (ptr[i+c] >= 0x20 && ptr[i+c] < 0x80) ? ptr[i+c] : '.';
      fputc(x, stream);
    }
 
    fputc('\n', stream); /* newline */
  }
}
 
static
int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp)
{
  const char *text;
  (void)handle; /* prevent compiler warning */
  (void)userp;
 
  switch (type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "== Info: %s", data);
  default: /* in case a new one is introduced to shock us */
    return 0;
 
  case CURLINFO_HEADER_OUT:
    text = "=> Send header";
    break;
  case CURLINFO_DATA_OUT:
    text = "=> Send data";
    break;
  case CURLINFO_SSL_DATA_OUT:
    text = "=> Send SSL data";
    break;
  case CURLINFO_HEADER_IN:
    text = "<= Recv header";
    break;
  case CURLINFO_DATA_IN:
    text = "<= Recv data";
    break;
  case CURLINFO_SSL_DATA_IN:
    text = "<= Recv SSL data";
    break;
  }
 
  dump(text, stderr, (unsigned char *)data, size);
  return 0;
}

int main(int argc, char *argv[])
{
	CURLcode ret_code;
	CURL *curl;
	CURLcode res;
	char str[PA_BUF_SIZE] = "\0";
	char strerr[PA_BUF_SIZE] = "\0";
	char head_str[PA_BUF_SIZE] = "\0";	// 0x7fffffffd890

	if(argc < 1)
	{
		strncpy(str, PA_PARAMETER_ERR, strlen(PA_PARAMETER_ERR));
		pa_err(str);
		exit(0);
	}

	ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	curl = curl_easy_init();
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);							//报告每一件意外的事情
	//curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
	curl_easy_setopt(curl, CURLOPT_URL, "www.hao123.com"); 				//设置下载的URI 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 2000);        				//设置超时 
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);        				//屏蔽其它信号 
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);          				//获取HTTP头部  
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);							//获取body内容
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);					//自动301，302跳转
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_head); 	//设置下载数据的回调函数 
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);	//设置头部回调函数
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, head_str);
	
	memset(dow_content_buf, '\0', sizeof(dow_content_buf));
	memset(strerr, '\0', sizeof(strerr));
	memset(head_str, '\0', sizeof(head_str));
	
	res = curl_easy_perform(curl);   
	if(res != CURLE_OK) {
		sprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
	}
	
	printf("打印头部信息：\n");
	printf("%s\n", head_str);
	
	curl_easy_cleanup(curl); 
	curl_global_cleanup();
	return 0;	
}
