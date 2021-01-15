#ifndef _READJSON_H
#define _READJSON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

typedef struct _Dane{
    int x[3];
    int y[3];
    char* field[3];
}Dane;

Dane* interpret_response(const char* const chunk,Dane *dane);

#endif