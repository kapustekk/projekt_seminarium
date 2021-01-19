#ifndef _LOGIC_H
#define _LOGIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"connect.h"


char* move(char *token);
char* rotate(char *token, char *direction);
char* reset(char *token);
char* explore(char *token);
char* info(char *token);
#endif