#include <err_warn.h>
#include <time.h>
#include <string.h>
#include <common.h>
#include <stdio.h>
#include <errno.h>

char log_file[PA_BUF_SIZE];
static FILE *log_file_p = NULL;

void open_log_file()
{
	log_file_p = fopen(log_file, "a");
}

void close_log_file()
{
	fclose(log_file_p);
}

void pa_err(const char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};

	pa_get_time(buf);

	sprintf(ch, "[%s] error: %s\n", buf, str);
	fputs(ch, log_file_p);
}

void pa_errno(const char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};

	pa_get_time(buf);

	sprintf(ch, "[%s] error: %s\n", buf, str);
	fputs(ch, log_file_p);

	memset(ch, '\0', sizeof(ch));
	memset(buf, '\0', sizeof(buf));
	pa_get_time(buf);
	sprintf(ch, "%s error: %s\n", buf, strerror(errno));
	fputs(ch, log_file_p);
}


void pa_error(const char *str, const char *str1)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};

	pa_get_time(buf);

	sprintf(ch, "[%s] error: %s %s\n", buf, str, str1);
	fputs(ch, log_file_p);
}

void pa_errorno(const char *str, const char *str1)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};

	pa_get_time(buf);

	sprintf(ch, "[%s] error: %s %s\n", buf, str, str1);
	fputs(ch, log_file_p);

	memset(ch, '\0', sizeof(ch));
	memset(buf, '\0', sizeof(buf));
	pa_get_time(buf);
	sprintf(ch, "%s error: %s\n", buf, strerror(errno));
	fputs(ch, log_file_p);
}


void pa_warn(const char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};

	pa_get_time(buf);

	sprintf(ch, "[%s] warn: %s\n", buf, str);
	fputs(ch, log_file_p);
}

void pa_warns(const char *str, const char *str1)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	char buf[PA_BUF_SIZE] = {"\0"};
	
	pa_get_time(buf);

	sprintf(ch, "[%s] warn: %s %s\n", buf, str, str1);
	fputs(ch, log_file_p);
}


static void pa_get_time(char *str)
{
	time_t timep;
	time(&timep);
	char *s = ctime(&timep);
	strncpy(str, s, strlen(s) - 2);
	strncat(str, " ", 1);
}
