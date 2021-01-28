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

void wczytaj(char *nazwa, mapa *m);
void wypisz(mapa *m);
void zwolnij(mapa *m);
void zapisz_macierz(char nazwa[], mapa *m);
mapa *uzupelnij_macierz(mapa *m, Dane *dane);
mapa *wyczysc_macierz(mapa *m);
char zwroc_litere(Dane *dane, int i);
#endif