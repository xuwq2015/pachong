#ifndef _GET_CONTENT_H_
#define _GET_CONTENT_H_

#include <string.h>
#include <stdio.h>
#include <curl/curl.h>
#include <common.h>

int pa_start(char*);

void get_head_thread(char*);
size_t callback_get_head(void*, size_t, size_t, void*);

#endif
