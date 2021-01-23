#include "logic.h"

char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int *poczatek_sciany)
{
    //w prawo +1 w lewo -1
    if (bilans_rotacji == 4 &&stan_mapy->pozycja_y == poczatek_sciany[0] && stan_mapy->pozycja_x == poczatek_sciany[1])
    {
        bilans_rotacji = 0;
        szukaj_wew_przeszkod(&stan_mapy);
        return "rotate_left";
    }
    if (stan_mapy->kierunek == 'N')
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == ' ')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if(stan_mapy->mapa[stan_mapy->pozycja_y-1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x ] == 'W')
        {
            return "rotate_left";
        }
           
    }
}