#ifndef _MAPA_H
#define _MAPA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"read_json.h"

// typedef struct _Macierz {
//     int r;
//     int c;
//     int **tab;
// }Macierz;

typedef struct _Mapa
{
    int **mapa;
    int rozmiar_x;
    int rozmiar_y;
    int pozycja_x;
    int pozycja_y;
    char kierunek;
} mapa;


mapa* wczytaj(FILE * fin);
void wypisz(mapa *m);
void zwolnij(mapa *m);
void zapisz_macierz(char nazwa[], mapa *m);
mapa *uzupelnij_macierz(mapa *m, Dane *dane);
mapa *wyczysc_macierz(mapa *m);
#endif