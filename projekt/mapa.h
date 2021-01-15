#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Macierz {
    int r;
    int c;
    int **tab;
}Macierz;

typedef struct _Dane{
    int x[3];
    int y[3];
    char* field[3];
}Dane;

Macierz* wczytaj(FILE * fin);
void wypisz(Macierz *m);
void zwolnij(Macierz *m);
void zapisz_macierz(char nazwa[], Macierz *m);
Macierz *uzupelnij_macierz(Macierz *m, Dane *dane);
Macierz *wyczysc_macierz(Macierz *m);