#include "../mapa.h"
#include "../wpisanie.h"
int main()
{
    char *load = "tests/macierz_wczytaj.txt";
    char *save = "tests/macierz_zapisz.txt";

    mapa *m = malloc(sizeof(mapa));
    alokuj_mape(m, 100, 100);
    wczytaj(load, m);
    wypisz(m);
    printf("m->kierunek = %c\n", m->kierunek);
    printf("m->pozycja_x = %d\n", m->pozycja_x);
    printf("m->pozycja_y = %d\n", m->pozycja_y);
    printf("wektor x=%d; wektor y=%d\n", m->wektor_y, m->wektor_x);

    wyczysc_macierz(m);
    m->mapa[1][4] = 'O';
    m->kierunek = 'W';
    zapisz_macierz(save, m);
    wczytaj(save, m);
    wypisz(m);
    zwolnij(m);

    return 0;
}