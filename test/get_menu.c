#include <string.h>
#include "./get_menu.h"
#include "common.h"
#include "download_page.h"

int pa_get_menu(char *str)
{
	char file_name[PA_BUF_SIZE] = {'\0'};

	pa_extract_filename(str, file_name);
	pa_download_page(str, file_name);
	return 0;
}

/* 根据提供的url提取网页内容写入文件名 */
static void pa_extract_filename(char *url_ch, char *ret_filename)
{
        char file_name[PA_FILENAME_SIZE] = {'\0'};
        int num = 0;

        //去掉"http://"
       	if(strstr(url_ch, "http") != NULL)
       	{ 
        	url_ch = &url_ch[7];
        }
        //去掉字符串"www"
        if(strstr(url_ch, "www") != NULL)
        {
        	url_ch = &url_ch[4];
        }

        strncpy(file_name, PA_FILE_DIR, strlen(PA_FILE_DIR));
        num = strlen(url_ch) - strlen(strchr(url_ch, '.'));
        strncat(file_name, url_ch, num);
        
       	strncpy(ret_filename, file_name, strlen(file_name));
}
