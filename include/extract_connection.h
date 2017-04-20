#ifndef _EXTRACT_CONNECTION_H_
#define _EXTRACT_CONNECTION_H_

#include <stdio.h>
#include <common.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include <stdlib.h>
#include <err_warn.h>

int pa_extract_connection(char*, pa_link_st*);
static int pa_match_str(char*, char*);
static pa_link_st *pa_save_link(char*, pa_link_st*);

#endif
