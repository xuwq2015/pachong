#ifndef _EXTRACT_CONNECTION_H_
#define _EXTRACT_CONNECTION_H_

#include <stdio.h>
#include <common.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

typedef struct link_struct
{
	char link[BUF_SIZE];
	struct link_struct *next;
}pa_link_st;

int pa_extract_connection(char*);
static int pa_match_str(char*, char*);

#endif
