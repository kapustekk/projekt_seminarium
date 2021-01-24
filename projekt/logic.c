#include "logic.h"

void znajdz_sciane(wektor *wektor, mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat)
{
    mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, info(swiat), chunk, dane, nazwa_folderu);
    int x = dane->x[0];
    int y = dane->y[0];
    while (x)
    {
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
        if (x == dane->x[0] && y == dane->y[0])
        {
            mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
            printf("JEST SCIANA!!\n");
            break;
        }
        x = dane->x[0];
        y = dane->y[0];
    }
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

    int bilans_rotacji = 0;
    int *poczatek_sciany = malloc(sizeof(int) * 2);

    mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
    printf("dane: direction:%s\n,mapa direction:%c\n", dane->direction, mapa->kierunek);
    wypisz(mapa);
    int i = 0;
    /*while (strcmp(dane->field[1], "wall") != 0)
    {
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, move(swiat), chunk, dane, nazwa_folderu);
        printf("dane move: x[1]= %d y[1]= %d direction:%s\n,mapa direction:%c\n", dane->x[1], dane->y[1], dane->direction, mapa->kierunek);
        printf("pozycja po move y %d x%d\n", mapa->pozycja_y, mapa->pozycja_x);
        mapa = uzupelnij_zapisz_wypisz_macierz(wektor, mapa, explore(swiat), chunk, dane, nazwa_folderu);
        printf("dane explore: x[1]= %d y[1]= %d direction:%s\n,mapa direction:%c\n ruch nr %d\n", dane->x[1], dane->y[1], dane->direction, mapa->kierunek, i);
        printf("pozycja po explore y %d x%d\n\n", mapa->pozycja_y, mapa->pozycja_x);
        i++;
        //wypisz(mapa);
    }*/
    poczatek_sciany[0] = dane->y[1];
    poczatek_sciany[1] = dane->x[1];
    printf("po znalzezieniu pocz sciany:\nstan mapy: rozmiar: y %d x %d \nkierunek %c\npolozenie y %d x %d\n", mapa->rozmiar_y, mapa->rozmiar_x, mapa->kierunek, mapa->pozycja_y, mapa->pozycja_x);
    for (int i = 0; i < 5; i++)
    {
        printf("wchodze do for\nruch nr %d\n\n\n", i);
        printf(" ruch-> %s\n", wykonaj_ruch(mapa, &bilans_rotacji, &poczatek_sciany));
        mapa = co_zrobic(wykonaj_ruch(mapa, &bilans_rotacji, &poczatek_sciany), mapa, swiat, chunk, dane, nazwa_folderu, wektor);
    }

    wypisz(mapa);
    return mapa;
}
