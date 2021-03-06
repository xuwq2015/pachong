#include "err_warn.h"

void pa_err(char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"}; 
	pa_get_time(ch);

	strncat(ch, str, strlen(str));
	printf("%s\n", ch);
}

void pa_warn(char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	pa_get_time(ch);

	strncat(ch, str, strlen(str));
	printf("%s\n", ch);
}

static char *pa_get_time(char *str)
{
	time_t timep;
	time(&timep);
	char *s = ctime(&timep);
	strncpy(str, s, strlen(s));
	strncat(str, " ", 1);
	return str;
}
