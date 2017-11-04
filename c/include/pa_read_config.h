#ifndef _PA_READ_CONFIG_H_
#define _PA_READ_CONFIG_H_

#include <stdio.h>
#include <common.h>
#include <db_option.h>
#include <err_warn.h>

#define PA_CONFIG_DIR "./config"
#define PA_CONFIG_FILE "pachong.config"
#define PA_LOG_FILE "./log/pachong.log"
#define PA_WEB_CONFIG_PATH "conf.d"
#define PA_DOWN_BUF_PATH "./buf"

int pa_init_config();

static int init_default_config();
static int read_main_config(FILE *fp);
static int rep_main_config_info(char *key_name, char *key_value);
static int get_conf_value(char *conf, char *key_name, char *key_value);

static int read_web_config(FILE *fp, web_config *p);
static int rep_web_config(char *key_name, char *key_value, web_config *p);

#endif