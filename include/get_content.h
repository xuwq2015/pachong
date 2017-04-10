#ifndef _GET_CONTENT_H_
#define _GET_CONTENT_H_

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pa_start(char*);
static size_t pa_rec( char*, size_t, size_t, void*);
static void print_err(int);

#endif
