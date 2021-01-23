#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../connect.h"
int main(int argc, char* argv[])
{
    char* _info="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_12";
    char* _reset="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_12";
    char* _move="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_12";
    char* _explore="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_12";
    char* _rotater="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_12/right";
    char* _rotatel="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_12/left";
    
    printf("answer for info: \n%s",make_request(_info));
    printf("answer for reset: \n%s",make_request(_reset));
    printf("answer for move: \n%s",make_request(_move));
    printf("answer for explore: \n%s",make_request(_explore));
    printf("answer for rotate right: \n%s",make_request(_rotater));
    printf("answer for rotate left: \n%s",make_request(_rotatel));

    if((make_request(_info)!=NULL)&&(make_request(_reset)!=NULL)&&(make_request(_move)!=NULL)&&(make_request(_explore)!=NULL)&&(make_request(_rotater)!=NULL)&&(make_request(_rotatel)!=NULL))
    printf("Success!\n");
    else
    {
        printf("Failed!\n");
    }
    
}