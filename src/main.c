#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <get_content.h>
#include <common.h>
#include <curl/curl.h>

CURLcode ret_curl;

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		printf("参数输入错误，请重新输入\n");
		exit(0);
	}

	ret_curl = curl_global_init(CURL_GLOBAL_NOTHING);

	int ret = pa_start(argv[1]);

	curl_global_cleanup();
	return 0;
}
