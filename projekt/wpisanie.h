#ifndef _WPISANIE_H
#define _WPISANIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cjson.h"


typedef struct _Dane
{
    int x[3];
    int y[3];
    char *field[3];
    char *direction;
    int mess;
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

typedef struct _WEKTOR
{
    int x;
    int y;
} wektor;

mapa *doklejanie(mapa *wejscie, char kierunek, wektor *wektor);
mapa *wpisywanie_do_mapy(mapa *wejscie, int y, int x, char pole, wektor *wektor);
void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy);
void zero(int x, int y, mapa *source);
mapa *pamiec(int rozmiar_x, int rozmiar_y);
void zwolnij_mape(mapa *co);

#endif
