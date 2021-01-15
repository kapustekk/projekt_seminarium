#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

#define A 1024

typedef struct _Dane
{
    int x[3];
    int y[3];
    char *field[3];
} Dane;

typedef struct _Mapa
{
    char **mapa;
    int rozmiar_x;
    int rozmiar_y;
    int pozycja_x;
    int pozycja_y;
    char kierunek;
} mapa;
