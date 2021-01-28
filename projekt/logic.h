#ifndef LOGIC_H
#define LOGIC_H

#include "wpisanie.h"
#include "connect.h"
#include "url.h"
#include "read_json.h"
#include "mapa.h"
char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int x_pocz, int y_pocz);
void co_zrobic(char *odp, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu, int *ile_ruchow);
mapa *odkryj_mape(mapa *mapa, char *swiat, Dane *dane, char *chunk, char *nazwa_folderu);
mapa *uzupelnij_zapisz_wypisz_macierz(mapa *mapa, char *url, char *chunk, Dane *dane, char *nazwa_folderu);
mapa *chodzenie_po_odkrytym(mapa *mapa, char *swiat, int kierunek, int koniecx, int koniecy);
int odkrycie_mapy(mapa m);

#endif
