#ifndef _WPISANIE_H
#define _WPISANIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int wektor_y;
    int wektor_x;
} mapa;

#define N 5
void alokuj_mape(mapa *m, int y, int x);
void kopiuj_mape(mapa *m1, mapa *m, int wektor_x, int wektor_y);
mapa *doklejanie_gora(mapa *m);
mapa *doklejanie_dol(mapa *m);
mapa *doklejanie_prawo(mapa *m);
mapa *doklejanie_lewo(mapa *m);
void wypisz(mapa *x);
void zapisz(char *fnazwa, mapa *x);
//void wczytaj(char *fnazwa, mapa *x);
mapa *resetuj_mape(mapa *nowa);
void zwolnij(mapa *x);
mapa *wpisanie_do_mapy(mapa *gdzie, int y, int x, char co);

#endif
