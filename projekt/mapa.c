#include "mapa.h"

mapa *wczytaj(FILE *fin)
{
    int i, j;
    mapa *m = (mapa *)malloc(sizeof(mapa));
    fscanf(fin, "%d\n", &m->rozmiar_x);
    fscanf(fin, "%d\n", &m->rozmiar_y);

    m->mapa = (char **)malloc(sizeof(char *) * m->rozmiar_x);
    for (i = 0; i < m->rozmiar_x; i++)
        m->mapa[i] = (char *)malloc(sizeof(char) * m->rozmiar_y);

    for (i = 0; i < m->rozmiar_x; i++)
        for (j = 0; j < m->rozmiar_y; j++)
            fscanf(fin, "%c\n", &m->mapa[i][j]);
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
            printf("%c ", m->mapa[r][c]);
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

void zapisz_macierz(char nazwa[], mapa *m)
{
    FILE *fout = fopen(nazwa, "w");
    int i, j;

    fprintf(fout, "%d\n%d\n", m->rozmiar_x, m->rozmiar_y);
    for (i = 0; i < m->rozmiar_x; i++)
    {
        for (j = 0; j < m->rozmiar_y; j++)
            fprintf(fout, "%c\n", m->mapa[i][j]);
        //fprintf(fout, "\n");
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

mapa *uzupelnij_macierz(mapa *m, Dane *dane)
{

    int i = 0;
    int wektor[2] = {0, 0};
    while (dane->field[i])
    {
        wpisywanie_do_mapy(m, dane->x[i], dane->y[i], zwroc_litere(dane, i), &wektor);
        i++;
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