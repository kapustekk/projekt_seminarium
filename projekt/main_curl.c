#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "mapa.h"
#include "read_json.h"
#include "connect.h"
#include "url.h"



int main(int argc, char **argv)
{
    char *swiat="qwerty_12";
    // strcpy(swiat,"qwerty_12");
    Dane *dane=malloc(sizeof(Dane));
    char* nazwa_folderu="A.txt";
    char*chunk=(char*)malloc(sizeof(char*));
    // Dane *dane=(Dane*)malloc(sizeof(Dane*));
    FILE *fin=fopen(nazwa_folderu,"r");
    mapa *a;
    a=wczytaj(fin);
    //0-unknown field ; 1 - WALL; 2-GRASS; 3-SAND;
    //KONCOWA MACIERZ
    // 1 1 1 1 1 1 1 1 1
    // 1 2 2 2 2 1 2 2 1
    // 1 2 1 1 2 1 2 1 1
    // 1 2 2 1 2 1 2 2 1
    // 1 2 2 2 2 2 2 2 1
    // 1 2 1 1 2 1 2 2 1
    // 1 2 1 3 2 1 2 2 1
    // 1 2 1 1 2 1 2 1 1
    // 1 2 3 1 2 1 3 3 1
    // 1 2 3 2 2 1 2 2 1
    // 1 2 2 2 2 1 2 2 1
    // 1 1 1 1 1 1 1 1 1

    // char *url;
    if (argc==1)
    {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
    }
    else
    for (int i=1;i<argc;i++)
    {
        if(strcmp(argv[i],"M")==0)
        {
            chunk = make_request(move(swiat));
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"Rr")==0)
        {
            chunk = make_request(rotate(swiat,"right"));
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"Rl")==0)
        {
            chunk = make_request(rotate(swiat,"left"));
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"info")==0)
        {
            chunk = make_request(info(swiat));
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
            printf("%s",chunk);
        }
        else if(strcmp(argv[i], "E")==0)
        {
            chunk = make_request(explore(swiat));
            dane = interpret_response(chunk,dane);
            // printf("%d, %d, %s",dane->x[0],dane->y[0],dane->field[0]);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i], "reset")==0)
        {
            chunk = make_request(reset(swiat));
            dane = interpret_response(chunk,dane);
            a = wyczysc_macierz(a);
            a=uzupelnij_macierz(a,dane);
        }
        else
        {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
        }
        wypisz(a);
        zapisz_macierz(nazwa_folderu,a);   

    }
    // char *url = argc < 2 ? "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_12" : argv[1];
    return 0;
}
