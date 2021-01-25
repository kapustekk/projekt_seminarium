#ifndef LOGIC_H
#define LOGIC_H

#include "wpisanie.h"
#include "connect.h"
#include "url.h"
#include "read_json.h"
#include "mapa.h"
char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int **poczatek_sciany);
mapa *co_zrobic(char *odp, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu, wektor *wektor);
mapa *odkryj_mape(mapa *mapa, char *swiat, Dane *dane, char *chunk, char *nazwa_folderu, wektor *wektor);
mapa *uzupelnij_zapisz_wypisz_macierz(wektor *wektor, mapa *mapa, char *url, char *chunk, Dane *dane, char *nazwa_folderu);
mapa* alortym(wektor *wektor, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu,int** poczatek_sciany);
void znajdz_sciane(wektor *wektor, mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat);
mapa* obroc_explore(wektor *wektor, mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat);

#endif
