#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "common.h"
#include "err_warn.h"

int main(int argc, char *argv[])
{
	CURLcode ret_code;
	int ret = 0;
	char str[PA_BUF_SIZE] = {'\0'};

	if(argc < 1)
	{
		strncpy(str, PA_PARAMETER_ERR, strlen(PA_PARAMETER_ERR));
		pa_err(str);
		exit(0);
	}

	ret_code = curl_global_init(CURL_GLOBAL_NOTHING);
	
	ret = pa_get_menu(argv[1]);

	curl_global_cleanup();
	return 0;
}
