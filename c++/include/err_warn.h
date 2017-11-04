#ifndef _ERR_WARN_H_
#define _ERR_WARN_H_

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <common.h>

using namespace std;

#define ERR_LOG_FILE "./log/err.log"
#define WARN_LOG_FILE "./log/warn.log"

class PaErrWarn {
public:
	PaErrWarn();
	PaErrWarn(char *err_log_file, char *warn_log_file);
	~PaErrWarn();
	
	void pa_err(char *);
	void pa_warn(char *);
private:
	ofstream *err_file;
	ofstream *warn_file;

	char err_file_name[PA_BUF_SIZE];
	char warn_file_name[PA_BUF_SIZE];
	void pa_get_time(char*);
};

#endif
