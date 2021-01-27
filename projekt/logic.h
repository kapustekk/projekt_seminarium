#ifndef LOGIC_H
#define LOGIC_H

#include "wpisanie.h"
#include"connect.h"
#include"url.h"
#include"read_json.h"
#include"mapa.h"
char *co_zrobic(mapa *stan_mapy, int *bilans_rotacji,int x_pocz,int y_pocz);
void wykonaj_ruch(char*odp,mapa*mapa,char*swiat,char*chunk,Dane*dane,char*nazwa_folderu,wektor *wektor,int *ile_ruchow);
void odkryj_mape(mapa *mapa,char* swiat,Dane *dane,char*chunk,char*nazwa_folderu,wektor *wektor);
mapa* uzupelnij_zapisz_wypisz_macierz(wektor *wektor,mapa*mapa,char*url,char*chunk,Dane*dane,char*nazwa_folderu);

#endif
