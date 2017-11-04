#include <err_warn.h>
#include <time.h>
#include <string.h>
#include <common.h>

using namespace std;

PaErrWarn::PaErrWarn()
{
	strncpy(err_file_name, ERR_LOG_FILE, strlen(ERR_LOG_FILE));
	strncpy(warn_file_name, WARN_LOG_FILE, strlen(WARN_LOG_FILE));

	err_file = new ofstream;
	warn_file = new ofstream;

	err_file->open(err_file_name, std::ifstream::in | std::ifstream::out | std::ifstream::app);
	warn_file->open(warn_file_name, std::ifstream::in | std::ifstream::out | std::ifstream::app);
}


PaErrWarn::PaErrWarn(char *err_log_file, char *warn_log_file)
{
	strncpy(err_file_name, err_log_file, strlen(err_log_file));
	strncpy(warn_file_name, warn_log_file, strlen(warn_log_file));

	err_file = new ofstream;
	warn_file = new ofstream;
	
	err_file->open(err_file_name, std::ifstream::in | std::ifstream::out | std::ifstream::app);
	warn_file->open(warn_file_name, std::ifstream::in | std::ifstream::out | std::ifstream::app);
}

PaErrWarn::~PaErrWarn() 
{
	err_file->close();
	warn_file->close();
	
	//delete err_file;
	//delete warn_file;
}

void PaErrWarn::pa_err(char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	pa_get_time(ch);

	strncat(ch, str, strlen(str));
	strncat(ch, "\n", strlen("\n"));
	err_file->write(ch, strlen(ch));
}

void PaErrWarn::pa_warn(char *str)
{
	char ch[PA_BUF_SIZE] = {"\0"};
	pa_get_time(ch);

	strncat(ch, str, strlen(str));
	strncat(ch, "\n", strlen("\n"));
	this->warn_file->write(ch, strlen(ch));
}

void PaErrWarn::pa_get_time(char *str)
{
	time_t timep;
	time(&timep);
	char *s = ctime(&timep);
	strncpy(str, s, strlen(s) - 2);
	strncat(str, ":", 1);
}
