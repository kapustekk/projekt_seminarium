#include "mapa.h"

mapa *wczytaj(char *nazwa, wektor *wektor)
{
    FILE *fin = fopen(nazwa, "r");
    int i, j;
    mapa *m = (mapa *)malloc(sizeof(mapa));
    fscanf(fin, "wektor: %d ", &wektor->y);
    fscanf(fin, "%d\n", &wektor->x);
    fscanf(fin, "rozmiar: %d ", &m->rozmiar_y);
    fscanf(fin, "%d\n", &m->rozmiar_x);
    fscanf(fin, "pozycja: %d ", &m->pozycja_y);
    fscanf(fin, "%d\n", &m->pozycja_x);
    fscanf(fin, "kierunek: %c\n", &m->kierunek);
    m->mapa = (char **)malloc(sizeof(char *) * m->rozmiar_y);
    for (i = 0; i < m->rozmiar_y; i++)
        m->mapa[i] = (char *)malloc(sizeof(char) * m->rozmiar_x);

    for (i = m->rozmiar_y - 1; i >= 0; i--)
    {
        for (j = 0; j < m->rozmiar_x; j++)
            fscanf(fin, "%c ", &m->mapa[i][j]);
        fscanf(fin, "\n");
    }
    fclose(fin);
    return m;
}

void wypisz(mapa *m)
{
    int c, r;
    printf("       ");
    for (int x = 0; x < m->rozmiar_x; x++)
    {
        printf("%2d", x);
    }
    printf("\n       ");
    for (int x = 0; x < m->rozmiar_x; x++)
        printf("--");
    printf("\n");
    for (c = m->rozmiar_y - 1; c >= 0; c--)
    {
        printf("%3d | [ ", c);
        for (r = 0; r < m->rozmiar_x; r++)
        {
            // for (r=m->rozmiar_x -1; r >=0; r--) {
            printf("%c ", m->mapa[c][r]);
        }
        printf("]\n");
    }
    printf("\n");
}

void zwolnij(mapa *m)
{
    for (int i = 0; i < m->rozmiar_x; i++)
        free(m->mapa[i]);
    free(m->mapa);
    free(m);
}

void zapisz_macierz(char nazwa[], mapa *m, wektor *wektor)
{
    FILE *fout = fopen(nazwa, "w");
    int i, j;
    fprintf(fout, "wektor: %d %d\n", wektor->y, wektor->x);
    fprintf(fout, "rozmiar: %d %d\n", m->rozmiar_y, m->rozmiar_x);
    fprintf(fout, "pozycja: %d %d\n", m->pozycja_y, m->pozycja_x);
    fprintf(fout, "kierunek: %c\n", m->kierunek);
    for (i = m->rozmiar_y - 1; i >= 0; i--)
    {
        for (j = 0; j < m->rozmiar_x; j++)
            fprintf(fout, "%c ", m->mapa[i][j]);
        fprintf(fout, "\n");
    }
    fclose(fout);
}

char zwroc_litere(Dane *dane, int i)
{

    if (strcmp(dane->field[i], "grass") == 0)
        return 'G';
    else if (strcmp(dane->field[i], "sand") == 0)
        return 'S';
    else if (strcmp(dane->field[i], "wall") == 0)
        return 'W';
}

mapa *uzupelnij_macierz(mapa *m, Dane *dane, wektor *wektor)
{
    if (dane->mess == 1)
    {
        m->kierunek = dane->direction[0];
        m->pozycja_x = dane->x[0] + wektor->x;
        m->pozycja_y = dane->y[0] + wektor->y;
        m = wpisywanie_do_mapy(m, dane->y[0], dane->x[0], zwroc_litere(dane, 0), wektor);
        dane->mess = 0;
    }
    else if (dane->mess == 3)
    {
        printf("otrzymane 3 dane do wpisania\n");
        m = wpisywanie_do_mapy(m, dane->y[0], dane->x[0], zwroc_litere(dane, 0), wektor);
        m = wpisywanie_do_mapy(m, dane->y[1], dane->x[1], zwroc_litere(dane, 1), wektor);
        m = wpisywanie_do_mapy(m, dane->y[2], dane->x[2], zwroc_litere(dane, 2), wektor);
        dane->mess = 0;
    }
    return m;
}

mapa *wyczysc_macierz(mapa *m)
{
    for (int i = 0; i < m->rozmiar_y; i++)
        for (int j = 0; j < m->rozmiar_x; j++)
        {
            m->mapa[i][j] = '_';
        }

    return m;
}