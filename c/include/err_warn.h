#ifndef _ERR_WARN_H_
#define _ERR_WARN_H_

#include <stdio.h>
#include <stdlib.h>

void open_log_file();
void close_log_file();

void pa_err(const char *);
void pa_errno(const char *str);
void pa_error(const char *str, const char *str1);
void pa_errorno(const char *str, const char *str1);

void pa_warn(const char *);
void pa_warns(const char *str, const char *str1);
static void pa_get_time(char*);

#endif
