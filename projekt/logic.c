#include"logic.h"
#define A 1024
char* info(char *token) {
    
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* explore(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*A);
    
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* reset(char *token) {
    
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}


char* move(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* rotate(char *token, char *direction)
{
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/token/direction
    char*url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate");
    strcat(url,"/");
    strcat(url,token);
    strcat(url,"/");
    strcat(url,direction);
    chunk = make_request(url);
    // printf("chunk funkcja: %s",chunk);
    free(url);
    return chunk;
}