#include "wpisanie.h"

int main()
{
    mapa *start = pamiec(5, 5);
    zero(5, 5, start);
    //mapa *koniec = pamiec(5, 5);
    //zero(5, 5, koniec);
    start->rozmiar_x = 5;
    start->rozmiar_y = 5;
    start->mapa[2][2] = 'p';
    start->mapa[2][3] = 'z';
    start->mapa[0][0] = 'U';
    //int *wektor = malloc(sizeof(int ) * 2);
    wektor *wektor = malloc(sizeof(wektor));
    wektor->x = 0;
    wektor->y = 0;
    start = wpisywanie_do_mapy(start, -2, 2, 'W', wektor);
    printf("costam\n");
    wypisz(start);
    start = wpisywanie_do_mapy(start, -2, -3, 'A', wektor);
    wypisz(start);
    start = wpisywanie_do_mapy(start, 7, 2, 'S', wektor);
    wypisz(start);
    start = wpisywanie_do_mapy(start, 2, 8, 'D', wektor);
    wypisz(start);
    printf("wartosc %c\n", start->mapa[2][7]);
    wypisz(start);
    printf("%d %d\n", wektor->y, wektor->x);
    printf("%d %d \n", start->rozmiar_y, start->rozmiar_x);
    printf("koniec!!\n");
    zwolnij_mape(start);
    // free(start);
    // int *ptr = malloc(sizeof(int) * 15);
}