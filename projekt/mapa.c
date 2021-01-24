#include "mapa.h"

mapa *wczytaj(FILE *fin, wektor *wektor)
{
    int i, j;
    mapa *m = (mapa *)malloc(sizeof(mapa));
    fscanf(fin, "%d ", &wektor->y);
    fscanf(fin, "%d\n", &wektor->x);
    fscanf(fin, "%d ", &m->rozmiar_y);
    fscanf(fin, "%d\n", &m->rozmiar_x);

    m->mapa = (char **)malloc(sizeof(char *) * m->rozmiar_y);
    for (i = 0; i < m->rozmiar_y; i++)
        m->mapa[i] = (char *)malloc(sizeof(char) * m->rozmiar_x);

    for (i = m->rozmiar_y - 1; i >= 0; i--)
    {
        for (j = 0; j < m->rozmiar_x; j++)
            fscanf(fin, "%c ", &m->mapa[i][j]);
        fscanf(fin, "\n");
    }
    return m;
}

void wypisz(mapa *m)
{
    int c, r;
    printf("       ");
    for (int x = 0; x < m->rozmiar_y; x++)
    {
        printf("%2d", x);
    }
    printf("\n       ");
    for (int x = 0; x < m->rozmiar_y; x++)
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
    fprintf(fout, "%d %d\n", wektor->y, wektor->x);
    fprintf(fout, "%d %d\n", m->rozmiar_y, m->rozmiar_x);
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

    printf("dane jakie otrzymalismy\ny %d x%d pole %s\ny %d x%d pole %s\ny %d x%d pole %s\n", dane->y[0], dane->x[0], dane->field[0], dane->y[1], dane->x[1], dane->field[1], dane->y[2], dane->x[2], dane->field[2]);
    printf("wektor jaki mamy przed wpisaniem y %d x %d\n", wektor->y, wektor->x);
    //int i = 0;
    //int wektor[2] = {0, 0};
    if (dane->field[1] == NULL)
    {
        printf("otrzyamna jedna dana do wpisania \n");
        m->kierunek = dane->direction[0];
        m->pozycja_x = dane->x[0];
        m->pozycja_y = dane->y[0];
        m = wpisywanie_do_mapy(m, dane->y[0], dane->x[0], zwroc_litere(dane, 0), wektor);
    }
    else
    {
        printf("otrzymane 3 dane do wpisania\n");
        m = wpisywanie_do_mapy(m, dane->y[0], dane->x[0], zwroc_litere(dane, 0), wektor);
        m = wpisywanie_do_mapy(m, dane->y[1], dane->x[1], zwroc_litere(dane, 1), wektor);
        m = wpisywanie_do_mapy(m, dane->y[2], dane->x[2], zwroc_litere(dane, 2), wektor);
    }

    /*/

    if (dane->field[1] != NULL) //czyli jesli mamy explore
    {
        for (int i = 0; i < 3; i++)
        {
            char a;
            if (strcmp(dane->field[i], "grass") == 0)
                a = 'G';
            else if (strcmp(dane->field[i], "sand") == 0)
                a = 'S';
            else if (strcmp(dane->field[i], "wall") == 0)
                a = 'W';

            m->mapa[dane->x[i]][dane->y[i]] = a;
        }
    }
    else //dla funkcji ruchu
    {
        int a;
        if (strcmp(dane->field[0], "grass") == 0)
            a = 'G';
        else if (strcmp(dane->field[0], "sand") == 0)
            a = 'S';
        else if (strcmp(dane->field[0], "wall") == 0)
            a = 'W';

        m->mapa[dane->x[0]][dane->y[0]] = a;
    }*/
    return m;
}

mapa *wyczysc_macierz(mapa *m)
{
    for (int i = 0; i < m->rozmiar_x; i++)
        for (int j = 0; j < m->rozmiar_y; j++)
        {
            m->mapa[i][j] = '_';
        }

    return m;
}