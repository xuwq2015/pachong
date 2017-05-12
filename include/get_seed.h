#ifndef _GET_SEED_H_
#define _GET_SEED_H_

#include <common.h>
#include <regex.h>
#include <mysql/mysql.h>

void pa_get_seed(MYSQL*, pa_seed_url*);
static int pa_match_str(char*, char*);
static int pa_get_article_link(MYSQL*, char*);

#endif