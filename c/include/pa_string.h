#ifndef _PA_STRING_H_
#define _PA_STRING_H_

#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <get_seed.h>

typedef struct pa_connec_a_st {
	char href[PA_BUF_SIZE];
	char title[PA_BUF_SIZE];
}pa_connec_a;

char *pa_strtok(char*, char*, char*, char*);
int pa_strtok_r(char *src, char *start, char *end, char *des);
int pa_strtok_link(char*, char*, char*);
int pa_get_img_link(char *src, char *href, char *title);
int pa_get_center(char *src, char *start, char *end, char *des);
int pa_strcpy(char *src, char *end, char *des);
int pa_strrep(char *str, char original, char new);
int pa_extract_domain(char *url, char *domain);
int pa_extract_next_addr(char *str, char *addr);
int gen_random_string(int length, char *ouput);
int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);
int pa_match_str(char *str,char *pa_rule, char *ret_str);
int pa_match_strs(char *str, char *pa_rule, pa_connec_a *ret_str);

#endif