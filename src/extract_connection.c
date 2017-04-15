#include <extract_connection.h>

static pa_link_st *pa_link;

/* 从下载的首页中获取所有链接  */
int pa_extract_connection(char *file_name)
{
	char filename_suffix[] = "_home";
	char write_filename[BUF_SIZE] = {'\0'};
	char buf[BUF_SIZE] = {'\0'};
	char ret_str[BUF_SIZE] = {'\0'};

	strncpy(write_filename, file_name, strlen(file_name));
	strncat(write_filename, filename_suffix, strlen(filename_suffix));

	FILE *fp = fopen(file_name, "r");
	if(fp == NULL)
	{
		printf("文件打开失败\n");
		return -1;
	}
	FILE *wfp = fopen(write_filename, "w+");
	if(wfp == NULL)
	{
		printf("写文件打开失败\n");
		fclose(fp);
		return -1;
	}


	while(!feof(fp))
	{
		if(fgets(buf, BUF_SIZE, fp) != NULL) 
		{ 
			if((pa_match_str(buf, ret_str) != -1))
			{
				strncat(ret_str, "\n", 1);
				fputs(ret_str, wfp);
			}
		}	
		memset(buf, '\0', sizeof(buf));
		memset(ret_str, '\0', sizeof(ret_str));
	}

	fclose(fp);
	fclose(wfp);
}

static int pa_match_str(char *str, char *ret_str)
{
	char pa_rule[] = ".*(<a.*</a>).*";
	regex_t reg;
	regmatch_t pm[2];
	int  iret = 0;
	int index_start = 0, index_end = 0;

	iret = regcomp(&reg, pa_rule, REG_EXTENDED|REG_NEWLINE);
	if (iret != 0)
	{  
        return -1;  
    }
	iret = regexec(&reg, str, 2, pm, 0);
	if(iret == REG_NOMATCH)
	{
		return -1;
	}
	index_start = pm[1].rm_so;
	index_end = pm[1].rm_eo;
	strncpy(ret_str, &str[index_start], (index_end - index_start));
	return 0;
}
