#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <get_content.h>

int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		printf("参数输入错误，请重新输入\n");
		exit(0);
	}

	CURLcode ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	int ret = pa_start(argv[1]);

	curl_global_cleanup();
	return 0;
}
