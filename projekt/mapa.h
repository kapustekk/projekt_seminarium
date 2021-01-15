#ifndef _MAPA_H
#define _MAPA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"read_json.h"
typedef struct _Macierz {
    int r;
    int c;
    int **tab;
}Macierz;


Macierz* wczytaj(FILE * fin);
void wypisz(Macierz *m);
void zwolnij(Macierz *m);
void zapisz_macierz(char nazwa[], Macierz *m);
Macierz *uzupelnij_macierz(Macierz *m, Dane *dane);
Macierz *wyczysc_macierz(Macierz *m);
#endif