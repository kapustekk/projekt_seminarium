#include "wpisanie.h"

int main()
{
    mapa *start = pamiec(5, 5);
    zero(5, 5, start);
    start->rozmiar_x = 5;
    start->rozmiar_y = 5;
    start->mapa[2][2] = 'p';
    start->mapa[2][3] = 'z';
    start->mapa[0][0] = 'U';
    //int *wektor = malloc(sizeof(int ) * 2);
    int wektor[2] = {0, 0};
    printf("costam\n");
    start = wpisywanie_do_mapy(start, 2, 5, 'x', &wektor);
    start = wpisywanie_do_mapy(start, 5, 5, 'x', &wektor);
    start = wpisywanie_do_mapy(start, 5, -10, 'a', &wektor);
    start = wpisywanie_do_mapy(start, -10, -10, 's', &wektor);
    //start = doklejanie(start, 'p', &wektor);
    //start->mapa[3][8] = 'c';
    //start = doklejanie(start, 'd', &wektor);
    //start->mapa[8][3] = 'c';
    //start = doklejanie(start, 'l', &wektor);
    //start->mapa[1][3] = 'c';
    //start = doklejanie(start, 'g', &wektor);
    //start->mapa[1][3] = 'c';
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            printf("|%c |", start->mapa[i][j]);
        }
        printf("\n");
    }
    printf("%d %d\n", wektor[0], wektor[1]);
    printf("%d %d \n", start->rozmiar_y, start->rozmiar_x);
    zwolnij_mape(start);
    //free(start);
    //int *ptr = malloc(sizeof(int) * 15);
}