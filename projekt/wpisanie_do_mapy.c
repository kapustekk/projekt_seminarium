#include "wpisanie.h"

void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy)
{
    *x_wektor = gdzie_zaczynamy - x_json;
    *y_wektor = gdzie_zaczynamy - y_json;
}

mapa *wpisywanie_do_mapy(mapa *wejscie, int y, int x, char pole, int wektor[1][2])
{
    if (x + wektor[0][1] < wejscie->rozmiar_x && y + wektor[0][0] < wejscie->rozmiar_y && x + wektor[0][0] >= 0 && y + wektor[0][1] >= 0)
    {
        wejscie->mapa[x + wektor[0][0]][y + wektor[0][1]] = pole;
        //wektor[0][0] = 1;
    }
    else
    {

        if (x + wektor[0][1] >= wejscie->rozmiar_x)
        {
            wejscie = doklejanie(wejscie, 'p', &wektor[0]);
            //printf("%d %d \n", y + wektor[0][0], x + wektor[0][1]);
            wejscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
        }
        else if (y + wektor[0][0] >= wejscie->rozmiar_y)
        {
            //(" xd %d %d \n", y + wektor[0][0], x + wektor[0][1]);
            wejscie = doklejanie(wejscie, 'd', wektor);
            //printf("%d %d \n", y + wektor[0][0], x + wektor[0][1]);
            wejscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
        }
        else if (x + wektor[0][1] < 0)
        {
            wejscie = doklejanie(wejscie, 'l', wektor);
            wejscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
        }
        else if (y + wektor[0][0] < 0)
        {
            wejscie = doklejanie(wejscie, 'g', &wektor[0]);
            wejscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
        }
    }
    return wejscie;
}

void zero(int y, int x, mapa *source)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            source->mapa[i][j] = ' ';
        }
    }
}

mapa *doklejanie(mapa *wejscie, char kierunek, int wektor[1][2])
{
    mapa *wyjscie;
    if (kierunek == 'l')
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
        wektor[0][1] = wektor[0][1] + wejscie->rozmiar_x;
    }
    else if (kierunek == 'p')
    {
        wyjscie = pamiec(wejscie->rozmiar_y, 2 * wejscie->rozmiar_x);
        printf("costam2\n");
        zero(wejscie->rozmiar_y, 2 * wejscie->rozmiar_x, wyjscie);
        printf("costam2.5\n");
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i][j] = wejscie->mapa[i][j];
            }
        }
        printf("costam3\n");
        wyjscie->pozycja_x = wejscie->pozycja_x;
        printf("costam4\n");
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = 2 * wejscie->rozmiar_x;
        wyjscie->rozmiar_y = wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
        printf("costam5\n");
    }
    else if (kierunek == 'g')
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
        wektor[0][0] = wektor[0][0] + wejscie->rozmiar_y;
    }
    else if (kierunek == 'd')
    {
        printf("costam1\n");
        wyjscie = pamiec(2 * wejscie->rozmiar_y, wejscie->rozmiar_x);
        printf("costam2\n");
        zero(2 * wejscie->rozmiar_y, wejscie->rozmiar_x, wyjscie);
        printf("costam3\n");
        for (int i = 0; i < wejscie->rozmiar_y; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_x; j++)
            {
                wyjscie->mapa[i][j] = wejscie->mapa[i][j];
            }
        }
        printf("costam4\n");
        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = wejscie->rozmiar_x;
        wyjscie->rozmiar_y = 2 * wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
    }
    printf("costam6\n");
    printf("%d %d \n", wektor[0][0], wektor[0][1]);
    return wyjscie;
}

mapa *pamiec(int rozmiar_y, int rozmiar_x)
{
    mapa *cos = malloc(sizeof(mapa *));
    cos->mapa = malloc(sizeof(char *) * rozmiar_y);
    for (int i = 0; i < rozmiar_x; i++)
    {
        cos->mapa[i] = malloc(sizeof(char));
    }
    cos->rozmiar_x = 0;
    cos->rozmiar_y = 0;
    cos->pozycja_x = 0;
    cos->pozycja_y = 0;
    cos->kierunek = '0';
    return cos;
}
