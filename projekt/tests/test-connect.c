#include "../connect.h"
int main(int argc, char* argv[])
{
    char* _info="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_12";
    char* _reset="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_12";
    char* _move="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/qwerty_12";
    char* _explore="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/qwerty_12";
    char* _rotater="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_12/right";
    char* _rotatel="http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/qwerty_12/left";

    char* info=make_request(_info);
    char*reset=make_request(_reset);
    char*move = make_request(_move);
    char*explore = make_request(_explore);
    char* rotater=make_request(_rotater);
    char*rotatel=make_request(_rotatel);

    printf("answer for info: \n%s",info);
    printf("answer for reset: \n%s",reset);
    printf("answer for move: \n%s",move);
    printf("answer for explore: \n%s",explore);
    printf("answer for rotate right: \n%s",rotater);
    printf("answer for rotate left: \n%s",rotatel);

    if((info!=NULL)&&(reset!=NULL)&&(move!=NULL)&&(explore!=NULL)&&(rotater!=NULL)&&(rotatel!=NULL))
        printf("Success!\n");
    else
    {
        printf("Failed!\n");
    }
    free(info);
    free(reset);
    free(move);
    free(explore);
    free(rotater);
    free(rotatel);
}