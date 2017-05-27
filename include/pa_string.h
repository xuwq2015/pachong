#ifndef _PA_STRING_H_
#define _PA_STRING_H_

char *pa_strtok(char*, char*, char*, char*);
int pa_strtok_r(char *src, char *start, char *end, char *des);
int pa_strtok_link(char*, char*, char*);
int pa_get_img_link(char *src, char *href, char *title);
int pa_get_center(char *src, char *start, char *end, char *des);

#endif