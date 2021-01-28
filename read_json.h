#ifndef _READJSON_H
#define _READJSON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "wpisanie.h"
#include"mapa.h"

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

Dane *interpret_response(const char *const chunk, Dane *dane);

#endif