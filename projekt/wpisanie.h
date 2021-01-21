#ifndef _WPISANIE_H
#define _WPISANIE_H

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

void doklejanie(mapa *wejscie, char kierunek, int wektor[1][2],mapa*wyjscie);
mapa *wpisywanie_do_mapy(mapa *wejscie, int y, int x, char pole, int wektor[1][2]);
void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy);
void zero(int x, int y, mapa *source);
mapa *pamiec(int rozmiar_x, int rozmiar_y);
void zwolnij_mape(mapa *co);

#endif
