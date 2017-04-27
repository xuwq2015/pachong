#ifndef _DOWNLOAD_PAGE_H_
#define _DOWNLOAD_PAGE_H_

#include <stdlib.h>

int pa_download_page(char*, char*);
size_t pa_curl_callback(void*, size_t, size_t, void*);

#endif
