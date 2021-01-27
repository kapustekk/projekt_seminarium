#include "logic.h"
#include "wpisanie.h"

void niby_ruch(mapa *mapa, char *ruch)
{
    if (strcmp(ruch, "move") == 0)
    {
        if (mapa->kierunek == 'N')
        {
            mapa->pozycja_y--;
        }
        if (mapa->kierunek == 'S')
        {
            mapa->pozycja_y++;
        }
        if (mapa->kierunek == 'E')
        {
            mapa->pozycja_x++;
        }
        if (mapa->kierunek == 'W')
        {
            mapa->pozycja_x--;
        }
    }
    else if (strcmp(ruch, "rotate_left") == 0)
    {
        if (mapa->kierunek == 'N')
        {
            mapa->kierunek = 'W';
        }
        if (mapa->kierunek == 'S')
        {
            mapa->kierunek = 'E';
        }
        if (mapa->kierunek == 'E')
        {
            mapa->kierunek = 'N';
        }
        if (mapa->kierunek == 'W')
        {
            mapa->kierunek = 'S';
        }
    }
    else if (strcmp(ruch, "rotate_right") == 0)
    {
        if (mapa->kierunek == 'N')
        {
            mapa->kierunek = 'E';
        }
        if (mapa->kierunek == 'S')
        {
            mapa->kierunek = 'W';
        }
        if (mapa->kierunek == 'E')
        {
            mapa->kierunek = 'S';
        }
        if (mapa->kierunek == 'W')
        {
            mapa->kierunek = 'N';
        }
    }
}

int main()
{
    mapa *test = pamiec(5, 5);
    test->rozmiar_y = 5;
    test->rozmiar_x = 5;
    test->pozycja_x = 3;
    test->pozycja_y = 3;
    test->kierunek = 'N';
    zero(5, 5, test);
    test->mapa[0][0] = 'G';
    test->mapa[0][1] = 'G';
    test->mapa[0][2] = 'G';
    test->mapa[0][3] = 'G';
    test->mapa[0][4] = 'W';
    test->mapa[1][0] = 'W';
    test->mapa[1][1] = 'G';
    test->mapa[1][2] = 'W';
    test->mapa[1][3] = 'G';
    test->mapa[1][4] = 'W';
    test->mapa[2][0] = 'W';
    test->mapa[2][1] = 'G';
    test->mapa[2][2] = 'W';
    test->mapa[2][3] = 'G';
    test->mapa[2][4] = 'W';
    test->mapa[3][0] = 'W';
    test->mapa[3][1] = 'G';
    test->mapa[3][2] = 'W';
    test->mapa[3][3] = 'G';
    test->mapa[3][4] = 'W';
    test->mapa[4][0] = 'W';
    test->mapa[4][1] = 'G';
    test->mapa[4][2] = 'W';
    test->mapa[4][3] = 'G';
    test->mapa[4][4] = 'W';
    int sciana[2] = {3, 4};
    //printf("cojset\n");
    int rotacje = 0;
    char *wynik;
    printf("%s\n", wynik);
    for (int i = 0; i < 10; i++)
    {
        char *wynik = wykonaj_ruch(test, &rotacje, sciana);
        printf("%s\n", wynik);
        niby_ruch(test, wynik);
    }
}