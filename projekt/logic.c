#include "logic.h"

mapa* znajdz_sciane(wektor *wektor, mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat)
{
    int x=dane->x[0];
    int y=dane->y[0];
    while(x)
    {
        mapa=uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
        if(x==dane->x[0]&&y==dane->y[0])
        {
            mapa=uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
            printf("JEST SCIANA!!\n");
            break;
        }
        x=dane->x[0];
        y=dane->y[0];
    }
    return mapa;
}
    // dane->field[1]="cyk";
    // while (strcmp(dane->field[1],"wall")!=0)
    // {
    //     mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
    //     mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    // }
    // return mapa;

// }
mapa* obroc_explore(wektor *wektor, mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat)
{
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat,"right"), chunk, dane, nazwa_folderu);
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
}

char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int **poczatek_sciany)
{
    printf("stan mapy->kierunek:%c\n", stan_mapy->kierunek);
    //w prawo +1 w lewo -1
    if (bilans_rotacji[0] == 4 && stan_mapy->pozycja_y == *poczatek_sciany[0] && stan_mapy->pozycja_x == *poczatek_sciany[1])
    {
        bilans_rotacji[0] = 0;
        printf("mam mam ścianę zewnętrzną!\n");
        //szukaj_wew_przeszkod(&stan_mapy);
        *poczatek_sciany[0] = -1;
        *poczatek_sciany[1] = -1;
        return "rotate_left";
    }
    if (bilans_rotacji[0] == -4 && stan_mapy->pozycja_y == *poczatek_sciany[0] && stan_mapy->pozycja_x == *poczatek_sciany[1])
    {
        printf("mam przeszkodę wewnętrzną!\n");
    }
    if (stan_mapy->kierunek == 'N') //polnoc ,gora
    {
        printf("wszedlem w N\n");
        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {
            if (*poczatek_sciany[0] == -1)
            {
                *poczatek_sciany[0] = stan_mapy->pozycja_y + 1;
                *poczatek_sciany[1] = stan_mapy->pozycja_x + 1;
            }
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
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
    if (stan_mapy->kierunek == 'S') //poludnie ,dol
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W')
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
    if (stan_mapy->kierunek == 'E') //wschod , prawo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
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
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == '_' || stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W' && stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji++;
            return "rotate_right";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
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
mapa* move_explore(wektor *wektor, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu)
{
    int dd=0;
    if(mapa->kierunek=='N'||mapa->kierunek=='S')
    dd=2;
    else
    {
        dd=0;
    }
    mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
    mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    return mapa;

}

mapa* alortym(wektor *wektor, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu,int** poczatek_sciany,int currx,int curry,int*bilans_rotacji)
{
    int dd=0;
    if((mapa->kierunek=='N')||(mapa->kierunek=='S'))
    dd=2;
    else
    {
        dd=0;
    }
    
    wypisz(mapa);
    printf("mapa x:%d y:%d dir%c\n",mapa->pozycja_x,mapa->pozycja_y,mapa->kierunek);
    for (int i=0;i<3;i++)
    printf("DANE:x[%d]=%d,y[%d]=%d,field[%d]=%s\n",i,dane->x[i],i,dane->y[i],i,dane->field[i]);
    printf("%s",dane->field[dd]);
    if(strcmp(dane->field[dd],"wall")!=0&&strcmp(dane->field[1],"wall")!=0)
    {
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat, "left"), chunk, dane, nazwa_folderu);
        bilans_rotacji--;
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
        for (int i=0;i<3;i++)
        printf("DANE:x[%d]=%d,y[%d]=%d,field[%d]=%s\n",i,dane->x[i],i,dane->y[i],i,dane->field[i]);
    }
    else if(strcmp(dane->field[1],"wall")==0)
    {
        printf("if(strcmp(dane->field[1],wall)==0)\n");
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
        bilans_rotacji++;
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    }
    
    else if(strcmp(dane->field[dd],"wall")==0&&strcmp(dane->field[1],"wall")==0)
    {
        printf("else if(strcmp(dane->field[0],wall)==0&&strcmp(dane->field[1],wall)==0)\n");
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
        bilans_rotacji++;
        mapa=move_explore(wektor,mapa,swiat,chunk,dane,nazwa_folderu);
    }
    else if(strcmp(dane->field[dd],"wall")==0&&strcmp(dane->field[1],"wall")!=0)
    { 
        printf("else if(strcmp(dane->field[0],wall)==0&&strcmp(dane->field[1],wall)!=0)\n");
        mapa=move_explore(wektor,mapa,swiat,chunk,dane,nazwa_folderu);
    }
    if((mapa->pozycja_x==currx)&&(mapa->pozycja_y=curry))
    {
        // mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
        printf("mam sciane zewnetrzna! break;\n");
        return mapa;
    }
    alortym(wektor, mapa, swiat, chunk, dane, nazwa_folderu, poczatek_sciany,currx,curry,bilans_rotacji);
    
    return mapa;
}
mapa *uzupelnij_zapisz_wypisz_macierz(wektor *wektor, mapa *mapa, char *url, char *chunk, Dane *dane, char *nazwa_folderu)
{

    mapa = wczytaj(nazwa_folderu, wektor);
    chunk = make_request(url);
    dane = interpret_response(chunk, dane);
    mapa = uzupelnij_macierz(mapa, dane, wektor);
    zapisz_macierz(nazwa_folderu, mapa, wektor);
    // wypisz(mapa);
    return mapa;
}
mapa *co_zrobic(char *odp, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu, wektor *wektor)
{
    if (strcmp(odp, "rotate_left") == 0)
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat, "left"), chunk, dane, nazwa_folderu);
    else if (strcmp(odp, "rotate_right") == 0)
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
    else if (strcmp(odp, "move") == 0)
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
    else if (strcmp(odp, "explore") == 0)
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    return mapa;
}
mapa *odkryj_mape(mapa *mapa, char *swiat, Dane *dane, char *chunk, char *nazwa_folderu, wektor *wektor)
{
    int currx;
    int curry;
    int bilans_rotacji = 0;
    int *poczatek_sciany = malloc(sizeof(int) * 2);
    // int w=0;
    // for(w;w<3;w++)
    // {
    //     mapa = obroc_explore(wektor,mapa,chunk,dane,nazwa_folderu,swiat);
    //     if(strcmp(dane->field[1],"wall")==0)
    //     {
    //         printf("Ściana z przodu!");
    //         break;
    //     }
    // }
    // mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    printf("dane: direction:%s\n,mapa direction:%c\n", dane->direction, mapa->kierunek);
    wypisz(mapa);
    // if(w==2)
    mapa=znajdz_sciane(wektor,mapa,chunk,dane,nazwa_folderu,swiat);
    int i = 0;
    poczatek_sciany[0] = dane->y[1];
    poczatek_sciany[1] = dane->x[1];
    currx=mapa->pozycja_x;
    curry=mapa->pozycja_y;
    // printf("po znalzezieniu pocz sciany:\nstan mapy: rozmiar: y %d x %d \nkierunek %c\npolozenie y %d x %d\n", mapa->rozmiar_y, mapa->rozmiar_x, mapa->kierunek, mapa->pozycja_y, mapa->pozycja_x);
    for (int i = 0; i < 10; i++)
    {
        printf("wchodze do for\nruch nr %d\n\n\n", i);
        // printf(" ruch-> %s\n", wykonaj_ruch(mapa, &bilans_rotacji, &poczatek_sciany));
        // mapa = co_zrobic(wykonaj_ruch(mapa, &bilans_rotacji, &poczatek_sciany), mapa, swiat, chunk, dane, nazwa_folderu, wektor);
        mapa = alortym(wektor,mapa,swiat,chunk,dane,nazwa_folderu,&poczatek_sciany,currx,curry,&bilans_rotacji);
    }

    wypisz(mapa);
    return mapa;
}
