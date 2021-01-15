#include "wpisanie.h"

void pierwsze_wczytanie(int x_json, int y_json, int *x_wektor, int *y_wektor, int gdzie_zaczynamy)
{
    *x_wektor = gdzie_zaczynamy - x_json;
    *y_wektor = gdzie_zaczynamy - y_json;
}

void wpisywanie_do_mapy(mapa *wejscie, int x, int y, char pole, int wektor[2])
{
    if (x + wektor[0] < wejscie->rozmiar_x && y + wektor[1] < wejscie->rozmiar_y && x + wektor[0] >= 0 && y + wektor[1] >= 0)
    {
        wejscie->mapa[x + wektor[0]][y + wektor[y]] = pole;
    }
    else
    {
        //wejscie = doklejanie();
    }
}

mapa *doklejanie(mapa *wejscie, char kierunek, int *wektor[2])
{
    mapa *wyjscie = {->mapa = {0}};
    //wyjscie->mapa = malloc(sizeof(char) * wejscie->rozmiar_y * 2 * wejscie->rozmiar_x);
    //wyjscie->mapa = {0};
    if (kierunek == 'l')
    {
    }
    if (kierunek == 'p')
    {
        for (int i = 0; i < wejscie->rozmiar_x * 2; i++)
        {
            for (int j = 0; j < wejscie->rozmiar_y; j++)
            {
                wyjscie->mapa[i][j] = wejscie->mapa[i][j];
            }
        }
        wyjscie->pozycja_x = wejscie->pozycja_x;
        wyjscie->pozycja_y = wejscie->pozycja_y;
        wyjscie->rozmiar_x = 2 * wejscie->rozmiar_x;
        wyjscie->rozmiar_y = 2 * wejscie->rozmiar_y;
        wyjscie->kierunek = wejscie->kierunek;
    }
    if (kierunek == 'g')
    {
    }
    if (kierunek == 'd')
    {
    }
    return wyjscie;
}

int main()
{
    int a = 0, b = 0;
    pierwsze_wczytanie(7, 4, &a, &b, 50);
    printf("%d %d \n", a, b);
    int tab[8][2] = {0};
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d", tab[i][j]);
        }
    }
}