#ifndef PCURL_H
#define PCURL_H

#include <curl/curl.h>
#include <sys/types.h>
#include <string>
#include <string.h>
#include <common.h>

using namespace std;

size_t callback_get_head(void *ptr, size_t size, size_t nmemb, void *userp);

class PcurlOperate
{
public:
	PcurlOperate();
	~PcurlOperate();
	
	int down(char *str);
	void get_down_content(char *str);
	
	int err;
	char err_str[PA_BUF_SIZE];
private:
	CURL *curl;	
	void set_err(char *str);
	void set_http_head(char *url);
};

#endif