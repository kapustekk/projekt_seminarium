#include "logic.h"

char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int *poczatek_sciany)
{
    printf("stan mapy->kierunek:%c\n",stan_mapy->kierunek);
    //w prawo +1 w lewo -1
    if (bilans_rotacji[0] == 4 && stan_mapy->pozycja_y == poczatek_sciany[0] && stan_mapy->pozycja_x == poczatek_sciany[1])
    {
        bilans_rotacji[0] = 0;
        printf("mam mam ścianę zewnętrzną!\n");
        //szukaj_wew_przeszkod(&stan_mapy);
        poczatek_sciany[0] = NULL;
        poczatek_sciany[1] = NULL;
        return "rotate_left";
    }
    if (bilans_rotacji[0] == -4 && stan_mapy->pozycja_y == poczatek_sciany[0] && stan_mapy->pozycja_x == poczatek_sciany[1])
    {
        printf("mam przeszkodę wewnętrzną!\n");
    }
    if (stan_mapy->kierunek='N') //polnoc ,gora
    {
        printf("wszedlem w N");
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 0)
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 1)
        {
            if (poczatek_sciany[0] == NULL)
            {
                poczatek_sciany[0] = stan_mapy->pozycja_y - 1;
                poczatek_sciany[1] = stan_mapy->pozycja_x + 1;
            }
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 1 && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 1)
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 1)
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 1)
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek='S') //poludnie ,dol
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 0)
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 1)
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 1 && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 1)
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 1)
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 1)
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek='E') //wschod , prawo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 0)
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 1)
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 1)
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 1)
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 1)
        {
            return "move";
        }
        else
        {
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek='W') //zachod , lewo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 0 || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 0)
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 1)
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 1 && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 1)
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 1 && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 1)
        {
            bilans_rotacji--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 1)
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
mapa* uzupelnij_zapisz_wypisz_macierz(mapa*mapa,char*url,char*chunk,Dane*dane,char*nazwa_folderu)
{
        chunk = make_request(url);
        dane = interpret_response(chunk,dane);
        mapa = uzupelnij_macierz(mapa,dane);
        zapisz_macierz(nazwa_folderu,mapa);
        // wypisz(mapa);
        return(mapa);
}
void co_zrobic(char*odp,mapa*mapa,char*swiat,char*chunk,Dane*dane,char*nazwa_folderu)
{
    if(strcmp(odp,"rotate_left")==0)
        uzupelnij_zapisz_wypisz_macierz(mapa,rotate(swiat,"left"),chunk,dane,nazwa_folderu);
    else if(strcmp(odp,"rotate_right")==0)
        uzupelnij_zapisz_wypisz_macierz(mapa,rotate(swiat,"right"),chunk,dane,nazwa_folderu);
    else if(strcmp(odp,"move")==0)
        uzupelnij_zapisz_wypisz_macierz(mapa,move(swiat),chunk,dane,nazwa_folderu);
    else if(strcmp(odp,"explore")==0)
        uzupelnij_zapisz_wypisz_macierz(mapa,explore(swiat),chunk,dane,nazwa_folderu);
}
void odkryj_mape(mapa *mapa,char* swiat,Dane *dane,char*chunk,char*nazwa_folderu)
{
    int* bilans_rotacji=malloc(sizeof(int)*2);
    bilans_rotacji[0]=0;
    int* poczatek_sciany=malloc(sizeof(int)*2);
    
    uzupelnij_zapisz_wypisz_macierz(mapa,explore(swiat),chunk,dane,nazwa_folderu);
    printf("dane: direction:%s\n,mapa direction:%c\n",dane->direction,mapa->kierunek);
    wypisz(mapa);
    while (strcmp(dane->field[1],"wall")!=0)
    {
        uzupelnij_zapisz_wypisz_macierz(mapa,move(swiat),chunk,dane,nazwa_folderu);
        uzupelnij_zapisz_wypisz_macierz(mapa,explore(swiat),chunk,dane,nazwa_folderu);
        printf("dane: x[1]= %d y[1]= %d direction:%s\n,mapa direction:%c\n",dane->x[1],dane->y[1],dane->direction,mapa->kierunek);
        wypisz(mapa);
    }
    poczatek_sciany[0]=dane->y[1];
    poczatek_sciany[1]=dane->x[1];
    printf("po znalzezieniu pocz sciany:\n");
    for(int i=0;i<10;i++)
    {
    printf("wchodze do for\n");
    co_zrobic(wykonaj_ruch(mapa, bilans_rotacji, poczatek_sciany),mapa,swiat,chunk,dane,nazwa_folderu);
    printf("%s\n",wykonaj_ruch(mapa, bilans_rotacji, poczatek_sciany));
    }

    wypisz(mapa);
    
}
