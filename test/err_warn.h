#ifndef _ERR_WARN_H_
#define _ERR_WARN_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"

void pa_err(char *);
void pa_warn(char *);
static char *pa_get_time(char*);

#endif
