#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../url.h"
main()
{
    char* token="qwerty_12";
    char* _info=info(token);
    char* _reset=reset(token);
    char* _move=move(token);
    char* _explore= explore(token);
    char* _rotater=rotate(token,"right");
    char* _rotatel=rotate(token,"left");
    printf("info:%s\n",_info);
    printf("reset:%s\n",_reset);
    printf("move:%s\n",_move);
    printf("explore:%s\n",_explore);
    printf("rotater:%s\n",_rotater);
    printf("rotatel:%s\n",_rotatel);
}