#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <get_content.h>
#include <common.h>
#include <curl/curl.h>
#include <err_warn.h>


int main(int argc, char *argv[])
{
	if(argc < 1)
	{
		char str[] = "参数输入错误，请重新输入";
		pa_err(str);
		exit(0);
	}

	CURLcode ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	int ret = pa_start(argv[1]);

	curl_global_cleanup();
	return 0;
}
