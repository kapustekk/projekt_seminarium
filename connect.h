#ifndef _CONNECT_H
#define _CONNECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include"read_json.h"

char * make_request(char *url);

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp);


#endif