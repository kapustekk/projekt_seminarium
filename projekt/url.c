#include"url.h"
#define A 255

char* info(char *token) {
    
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url,"/");
    strcat(url,token);
    return url;
}

char* explore(char *token) {
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore");
    strcat(url,"/");
    strcat(url,token);
    return url;
}

char* reset(char *token) {
    
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset");
    strcat(url,"/");
    strcat(url,token);
    return url;
}


char* move(char *token) {
    // char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url,"/");
    strcat(url,token);
    return url;
}

char* rotate(char *token, char *direction)
{
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/token/direction
    char*url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate");
    strcat(url,"/");
    strcat(url,token);
    strcat(url,"/");
    strcat(url,direction);
    return url;
}
