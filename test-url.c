#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../url.h"
int main(int argc, char* argv[])
{
    char* token="qwerty_12";
    char* _info=info(token);
    char* _reset=reset(token);
    char* _move=move(token);
    char* _explore= explore(token);
    char* _rotater=rotate(token,"right");
    char* _rotatel=rotate(token,"left");

    printf("info:\n%s\n",_info);
    printf("reset:\n%s\n",_reset);
    printf("move:\n%s\n",_move);
    printf("explore:\n%s\n",_explore);
    printf("rotate right:\n%s\n",_rotater);
    printf("rotate left:\n%s\n",_rotatel);
    
    if((_info!=NULL)&&(_reset!=NULL)&&(_move!=NULL)&&(_explore!=NULL)&&(_rotater!=NULL)&&(_rotatel!=NULL))
        printf("Success!\n");

    else
    {
        printf("Failed!\n");
    }
    free(_info);
    free(_reset);
    free(_move);
    free(_explore);
    free(_rotater);
    free(_rotatel);

return 0;

}