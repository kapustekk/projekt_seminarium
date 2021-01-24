#include "logic.h"

char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int *poczatek_sciany)
{
    
    //w prawo +1 w lewo -1
    if (bilans_rotacji[0] == 4 && stan_mapy->pozycja_y == poczatek_sciany[0] && stan_mapy->pozycja_x == poczatek_sciany[1])
    {
        bilans_rotacji[0] = 0;
        //szukaj_wew_przeszkod(&stan_mapy);
        poczatek_sciany[0] = NULL;
        poczatek_sciany[1] = NULL;
        return "rotate_left";
    }
    if (bilans_rotacji[0] == - 4 && stan_mapy->pozycja_y == poczatek_sciany[0] && stan_mapy->pozycja_x == poczatek_sciany[1])
    {
        //mapa jest zamknieta;
    }
    if (stan_mapy->kierunek == 'N') //polnoc ,gora
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == ' ')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            if (poczatek_sciany[0] == NULL)
            {
                poczatek_sciany[0] = stan_mapy->pozycja_y - 1;
                poczatek_sciany[1] = stan_mapy->pozycja_x + 1;
            }
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'S') //poludie ,dol
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == ' ')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'E') //wschod , prawo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == ' ')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W')
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'W') //zachod , lewo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == ' ' || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == ' ')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W')
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    return "wtf";
}
