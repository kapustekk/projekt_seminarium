#include "wpisanie.h"

void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy)
{
    *x_wektor = gdzie_zaczynamy - x_json;
    *y_wektor = gdzie_zaczynamy - y_json;
}

void wypiszx(mapa *m)
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

mapa *wpisywanie_do_mapy(mapa *wejscie, int y, int x, char pole, wektor *wektor)
{
    // printf("wejsciowy rozmiar mapy y %d x %d \nwejsciowy wektor y %d x %d\npole do wpisania y %d x %d pole %c\n", wejscie->rozmiar_y, wejscie->rozmiar_x, wektor->y, wektor->x, y, x, pole);
    // printf("pole do ktorego powinno byc zzapisane %c to y %d x %d\n", pole, y + wektor->y, x + wektor->x);
    mapa *wyjscie;
    if (x + wektor->x < wejscie->rozmiar_x && y + wektor->y < wejscie->rozmiar_y && x + wektor->x >= 0 && y + wektor->y >= 0)
    {
        // printf("wpisywanie sucess\n");
        wyjscie = wejscie;
        wyjscie->mapa[y + wektor->y][x + wektor->x] = pole;
        //wektor->x[0] = 1;
    }
    else
    {
        printf("za mala mapa rozpowczynam doklejanie \n");
        if (x + wektor->x >= wejscie->rozmiar_x)
        {
            //wyjscie = pamiec(wejscie->rozmiar_y, wejscie->rozmiar_x * 2);
            wyjscie = doklejanie(wejscie, 'E', wektor);
            wyjscie->mapa[y + wektor->y][x + wektor->x] = pole;
            wyjscie->rozmiar_y = wejscie->rozmiar_y;
            wyjscie->rozmiar_x = wejscie->rozmiar_x * 2;
            zwolnij_mape(wejscie);
            printf("wpisywanie sucess\n");
        }
        else if (y + wektor->y >= wejscie->rozmiar_y)
        {
            //wyjscie = pamiec(wejscie->rozmiar_y * 2, wejscie->rozmiar_x);

            wyjscie = doklejanie(wejscie, 'S', wektor);

            wyjscie->mapa[y + wektor->y][x + wektor->x] = pole;
            wyjscie->rozmiar_y = wejscie->rozmiar_y * 2;
            wyjscie->rozmiar_x = wejscie->rozmiar_x;
            zwolnij_mape(wejscie);
            printf("wpisywanie sucess\n");
        }
        else if (x + wektor->x < 0)
        {
            //wyjscie = pamiec(wejscie->rozmiar_y, wejscie->rozmiar_x * 2);

            wyjscie = doklejanie(wejscie, 'W', wektor);
            wyjscie->mapa[y + wektor->y][x + wektor->x] = pole;
            wyjscie->rozmiar_y = wejscie->rozmiar_y;
            wyjscie->rozmiar_x = wejscie->rozmiar_x * 2;
            zwolnij_mape(wejscie);
            printf("wpisywanie sucess\n");
        }
        else if (y + wektor->y < 0)
        {
            //wyjscie = pamiec(wejscie->rozmiar_y * 2, wejscie->rozmiar_x);
            wyjscie = doklejanie(wejscie, 'N', wektor);
            wyjscie->mapa[y + wektor->y][x + wektor->x] = pole;
            wyjscie->rozmiar_y = wejscie->rozmiar_y * 2;
            wyjscie->rozmiar_x = wejscie->rozmiar_x;
            zwolnij_mape(wejscie);
            printf("wpisywanie sucess\n");
        }
    }
    // printf("wyjsciowy wektor %d %d wysjciowy rozmiar y %d x %dwyjsciowa macierz\n", wektor->x, wektor->x, wyjscie->rozmiar_y, wyjscie->rozmiar_x);
    // wypiszx(wyjscie);
    return wyjscie;
}

void zero(int y, int x, mapa *source)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            source->mapa[i][j] = '_';
        }
    }
}

mapa *doklejanie(mapa *wejscie, char kierunek, wektor *wektor)
{
    printf("doklejanie mapy w kierunku %c\n", kierunek);
    mapa *wyjscie;
    if (kierunek == 'W')
    {
        wyjscie = pamiec(wejscie->rozmiar_y, wejscie->rozmiar_x * 2);
        zero(wejscie->rozmiar_y, 2 * wejscie->rozmiar_x, wyjscie);
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i][wejscie->rozmiar_x + j] = wejscie->mapa[i][j];
            }
        }
        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = 2 * wejscie->rozmiar_x;
        wyjscie->rozmiar_y = wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
        wektor->x = wektor->x + wejscie->rozmiar_x;
        printf("doklejanie sucess\ndane mapy wyjsciowej rozmiar y %d x %d wektor y %d x %d\n", wyjscie->rozmiar_y, wyjscie->rozmiar_x, wektor->y, wektor->x);
    }
    else if (kierunek == 'E')
    {
        wyjscie = pamiec(wejscie->rozmiar_y, 2 * wejscie->rozmiar_x);
        zero(wejscie->rozmiar_y, 2 * wejscie->rozmiar_x, wyjscie);
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i][j] = wejscie->mapa[i][j];
            }
        }
        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = 2 * wejscie->rozmiar_x;
        wyjscie->rozmiar_y = wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
        printf("doklejanie sucess\ndane mapy wyjsciowej rozmiar y %d x %d wektor y %d x %d\n", wyjscie->rozmiar_y, wyjscie->rozmiar_x, wektor->y, wektor->x);
    }
    else if (kierunek == 'N')
    {
        wyjscie = pamiec(wejscie->rozmiar_y * 2, wejscie->rozmiar_x);
        zero(wejscie->rozmiar_y * 2, wejscie->rozmiar_x, wyjscie);
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i + wejscie->rozmiar_y][j] = wejscie->mapa[i][j];
            }
        }
        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = wejscie->rozmiar_x;
        wyjscie->rozmiar_y = 2 * wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
        wektor->y = wektor->y + wejscie->rozmiar_y;
        printf("doklejanie sucess\ndane mapy wyjsciowej rozmiar y %d x %d wektor y %d x %d\n", wyjscie->rozmiar_y, wyjscie->rozmiar_x, wektor->y, wektor->x);
    }
    else if (kierunek == 'S')
    {

        wyjscie = pamiec(2 * wejscie->rozmiar_y, wejscie->rozmiar_x);

        zero(2 * wejscie->rozmiar_y, wejscie->rozmiar_x, wyjscie);
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i][j] = wejscie->mapa[i][j];
            }
        }

        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = wejscie->rozmiar_x;
        wyjscie->rozmiar_y = 2 * wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
        printf("doklejanie sucess\ndane mapy wyjsciowej rozmiar y %d x %d wektor y %d x %d\n", wyjscie->rozmiar_y, wyjscie->rozmiar_x, wektor->y, wektor->x);
    }
    printf(" rozmiar wyjsciowy %d %d \n wyjsciowa macierz\n", wyjscie->rozmiar_y, wyjscie->rozmiar_x);
    wypiszx(wyjscie);
    // zwolnij_mape(wejscie);
    return wyjscie;
}

mapa *pamiec(int rozmiar_y, int rozmiar_x)
{
    mapa *cos = malloc(sizeof(mapa *));
    cos->mapa = malloc(sizeof(char *) * rozmiar_y);
    for (int i = 0; i < rozmiar_y; i++)
    {

        cos->mapa[i] = malloc(sizeof(char) * rozmiar_x);
    }
    cos->rozmiar_x = rozmiar_x;
    cos->rozmiar_y = rozmiar_y;
    cos->pozycja_x = 0;
    cos->pozycja_y = 0;
    cos->kierunek = '0';
    return cos;
}

void zwolnij_mape(mapa *co)
{
    for (int i = 0; i < co->rozmiar_y; i++)
    {

        free(co->mapa[i]);
    }
    free(co->mapa);
    free(co);
}
