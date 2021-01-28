#include "wpisanie.h"

void alokuj_mape(mapa *m, int y, int x)
{
    m->rozmiar_y = y;
    m->rozmiar_x = x;

    m->mapa = (char **)malloc(sizeof(char *) * y);
    for (int i = y - 1; i >= 0; i--)
    {
        m->mapa[i] = (char *)malloc(sizeof(char) * x);
        for (int j = 0; j < x; j++)
            m->mapa[i][j] = '_';
    }
}

void kopiuj_macierz(mapa *m1, mapa *m, int wektor_y, int wektor_x)
{

    for (int i = m->rozmiar_y - 1; i >= 0; i--)
    {
        for (int j = 0; j < m->rozmiar_x; j++)
        {

            m1->mapa[i + wektor_y][j + wektor_x] = m->mapa[i][j];
        }
    }
    m1->wektor_y = m->wektor_y + wektor_y;
    m1->wektor_x = m->wektor_x + wektor_x;
    m1->kierunek = m->kierunek;
    m1->pozycja_y = m->pozycja_y + wektor_y;
    m1->pozycja_x = m->pozycja_x + wektor_x;
}

mapa *doklejanie_gora(mapa *m)
{
    mapa *nowa = (mapa *)malloc(sizeof(mapa));
    alokuj_mape(nowa, m->rozmiar_y + m->rozmiar_y, m->rozmiar_x);

    kopiuj_macierz(nowa, m, 0, 0);

    zwolnij(m);

    return nowa;
}

mapa *doklejanie_dol(mapa *m)
{
    int w = m->rozmiar_y;
    mapa *nowa = (mapa *)malloc(sizeof(mapa));
    alokuj_mape(nowa, m->rozmiar_y + m->rozmiar_y, m->rozmiar_x);

    kopiuj_macierz(nowa, m, w, 0);

    nowa->rozmiar_y = m->rozmiar_y + m->rozmiar_y;
    zwolnij(m);

    return nowa;
}

mapa *doklejanie_prawo(mapa *m)
{
    mapa *nowa = (mapa *)malloc(sizeof(mapa));

    alokuj_mape(nowa, m->rozmiar_y, m->rozmiar_x + m->rozmiar_x);

    kopiuj_macierz(nowa, m, 0, 0);

    zwolnij(m);

    return nowa;
}

mapa *doklejanie_lewo(mapa *m)
{
    int w = m->rozmiar_x;
    mapa *nowa = (mapa *)malloc(sizeof(mapa));
    alokuj_mape(nowa, m->rozmiar_y, m->rozmiar_x + m->rozmiar_x);

    kopiuj_macierz(nowa, m, 0, w);

    nowa->rozmiar_x = w + w;
    zwolnij(m);

    return nowa;
}

void zapisz(char *fnazwa, mapa *x)
{
    int i, j;
    FILE *fin = fopen(fnazwa, "w+");
    fprintf(fin, "%d\n%d\n", x->rozmiar_y, x->rozmiar_x);
    for (i = x->rozmiar_y - 1; i >= 0; i--)
    {
        for (j = 0; j < x->rozmiar_x; j++)
        {
            fprintf(fin, "%c", x->mapa[i][j]);
        }
        fprintf(fin, "\n");
    }
    fclose(fin);
}

mapa *resetuj_mape(mapa *nowa)
{
    nowa = (mapa *)malloc(sizeof(mapa));
    alokuj_mape(nowa, N, N);
    nowa->pozycja_y = 3;
    nowa->pozycja_x = 3;

    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < N; j++)
            nowa->mapa[i][j] = '_';
    }
    return nowa;
}

mapa *wpisanie_do_mapy(mapa *gdzie, int y, int x, char co)
{
    if (y + gdzie->wektor_y < gdzie->rozmiar_y && y + gdzie->wektor_y >= 0 && x + gdzie->wektor_x < gdzie->rozmiar_x && x + gdzie->wektor_x >= 0)
    {
        gdzie->mapa[y + gdzie->wektor_y][x + gdzie->wektor_x] = co;
    }
    else
    {
        mapa *nowa;
        if (y + gdzie->wektor_y >= gdzie->rozmiar_y)
        {
            printf("doklejanie w gore\n");
            nowa = doklejanie_gora(gdzie);
            printf("rozmiar nowej mapy %d %d\n", nowa->rozmiar_y, nowa->rozmiar_x);
            nowa = wpisanie_do_mapy(nowa, y, x, co);
            free(gdzie);
            return nowa;
        }
        if (y + gdzie->wektor_y < 0)
        {
            printf("doklejanie w dol\n");
            nowa = doklejanie_dol(gdzie);
            printf("rozmiar nowej mapy %d %d\n", nowa->rozmiar_y, nowa->rozmiar_x);
            nowa = wpisanie_do_mapy(nowa, y, x, co);
            free(gdzie);
            return nowa;
        }
        if (x + gdzie->wektor_x >= gdzie->rozmiar_x)
        {
            printf("doklejanie w prawo\n");
            nowa = doklejanie_prawo(gdzie);
            printf("rozmiar nowej mapy %d %d\n", nowa->rozmiar_y, nowa->rozmiar_x);
            nowa = wpisanie_do_mapy(nowa, y, x, co);
            free(gdzie);
            return nowa;
        }
        if (x + gdzie->wektor_x < 0)
        {
            printf("doklejanie w lewo\n");
            nowa = doklejanie_lewo(gdzie);
            printf("rozmiar nowej mapy %d %d\n", nowa->rozmiar_y, nowa->rozmiar_x);
            nowa = wpisanie_do_mapy(nowa, y, x, co);
            free(gdzie);
            return nowa;
        }
    }
    return gdzie;
}
