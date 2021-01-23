#include "wpisanie.h"

void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy)
{
    *x_wektor = gdzie_zaczynamy - x_json;
    *y_wektor = gdzie_zaczynamy - y_json;
}

mapa *wpisywanie_do_mapy(mapa *wejscie, int y, int x, char pole, int wektor[1][2])
{
    mapa *wyjscie;
    if (x + wektor[0][1] < wejscie->rozmiar_x && y + wektor[0][0] < wejscie->rozmiar_y && x + wektor[0][0] >= 0 && y + wektor[0][1] >= 0)
    {
        wyjscie = wejscie;
        wyjscie->mapa[x + wektor[0][0]][y + wektor[0][1]] = pole;
        //wektor[0][0] = 1;
    }
    else
    {
        if (x + wektor[0][1] >= wejscie->rozmiar_x)
        {
            wyjscie = pamiec(wejscie->rozmiar_y, wejscie->rozmiar_x * 2);
            doklejanie(wejscie, 'E', &wektor[0], wyjscie);
            printf("%d %d \n", y + wektor[0][0], x + wektor[0][1]);
            wyjscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
            zwolnij_mape(wejscie);
        }
        else if (y + wektor[0][0] >= wejscie->rozmiar_y)
        {
            wyjscie = pamiec(wejscie->rozmiar_y * 2, wejscie->rozmiar_x);
            printf(" xd %d %d \n", y + wektor[0][0], x + wektor[0][1]);
            doklejanie(wejscie, 'S', wektor, wyjscie);
            printf("%d %d \n", y + wektor[0][0], x + wektor[0][1]);
            wyjscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
            zwolnij_mape(wejscie);
        }
        else if (x + wektor[0][1] < 0)
        {
            wyjscie = pamiec(wejscie->rozmiar_y, wejscie->rozmiar_x * 2);

            doklejanie(wejscie, 'W', wektor, wyjscie);
            printf("1\n");
            wyjscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
            zwolnij_mape(wejscie);
        }
        else if (y + wektor[0][0] < 0)
        {
            wyjscie = pamiec(wejscie->rozmiar_y * 2, wejscie->rozmiar_x);
            doklejanie(wejscie, 'N', &wektor[0], wyjscie);
            printf("2\n");
            wyjscie->mapa[y + wektor[0][0]][x + wektor[0][1]] = pole;
            zwolnij_mape(wejscie);
        }
    }
    return wyjscie;
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

void doklejanie(mapa *wejscie, char kierunek, int wektor[1][2], mapa *wyjscie)
{
    //mapa *wyjscie;
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
        wektor[0][1] = wektor[0][1] + wejscie->rozmiar_x;
    }
    else if (kierunek == 'E')
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
        wektor[0][0] = wektor[0][0] + wejscie->rozmiar_y;
    }
    else if (kierunek == 'S')
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
    //zwolnij_mape(wejscie);
    //return wyjscie;
}

mapa *pamiec(int rozmiar_y, int rozmiar_x)
{
    mapa *cos = malloc(sizeof(mapa *));
    cos->mapa = malloc(sizeof(char *) * rozmiar_y);
    for (int i = 0; i < rozmiar_y; i++)
    {

        cos->mapa[i] = malloc(sizeof(char) * rozmiar_x);
    }
    cos->rozmiar_x = 0;
    cos->rozmiar_y = 0;
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
