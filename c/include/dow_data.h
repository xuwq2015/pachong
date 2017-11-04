#ifndef _DOW_DATA_H_
#define _DOW_DATA_H_

#include <sys/types.h>

int pa_init_curl();
int pa_cleanup_curl();
int pa_dow_data(char *url, char *down_file);
size_t callback_get_head(void*, size_t, size_t, void*);

#endif