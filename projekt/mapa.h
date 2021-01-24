#ifndef _MAPA_H
#define _MAPA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_json.h"
#include "wpisanie.h"

// typedef struct _Macierz {
//     int r;
//     int c;
//     int **tab;
// }Macierz;

mapa *wczytaj(FILE *fin);
void wypisz(mapa *m);
void zwolnij(mapa *m);
void zapisz_macierz(char nazwa[], mapa *m);
mapa *uzupelnij_macierz(mapa *m, Dane *dane, wektor *wektor);
mapa *wyczysc_macierz(mapa *m);
#endif