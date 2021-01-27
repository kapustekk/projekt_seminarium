#include "../mapa.h"
#include "../wpisanie.h"
int main()
{
    char* load="tests/macierz_wczytaj.txt";
    char* save="tests/macierz_zapisz.txt";
    wektor *w = malloc(sizeof(wektor));
    mapa *m = wczytaj(load, w);
    wypisz(m);
    printf("m->kierunek = %c\n",m->kierunek);
    printf("m->pozycja_x = %d\n",m->pozycja_x);
    printf("m->pozycja_y = %d\n",m->pozycja_y);
    printf("wektor x=%d; wektor y=%d\n",w->x,w->y);

    wyczysc_macierz(m);
    m->mapa[1][4]='O';
    m->kierunek='W';
    zapisz_macierz(save,m,w);
    m=wczytaj(save,w);
    wypisz(m);
    zwolnij_mape(m);
    free(w);

    return 0;
}