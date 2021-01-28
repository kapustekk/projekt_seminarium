#include "logic.h"

mapa *znajdz_sciane(mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat, int *ile_ruchow)
{
    mapa = uzupelnij_zapisz_wypisz_macierz(mapa, info(swiat), chunk, dane, nazwa_folderu);
    ile_ruchow[0]++;
    int x = dane->x[0];
    int y = dane->y[0];
    while (x)
    {
        mapa = uzupelnij_zapisz_wypisz_macierz(mapa, move(swiat), chunk, dane, nazwa_folderu);
        ile_ruchow[0]++;
        if (x == dane->x[0] && y == dane->y[0])
        {

            if (mapa->kierunek == 'N')
            {
                if (mapa->mapa[mapa->pozycja_y + 1][mapa->pozycja_x] == '_')
                    mapa->mapa[mapa->pozycja_y + 1][mapa->pozycja_x] = 'W';
                else
                    break;
            }
            else if (mapa->kierunek == 'S')
            {
                if (mapa->mapa[mapa->pozycja_y - 1][mapa->pozycja_x] == '_')
                    mapa->mapa[mapa->pozycja_y - 1][mapa->pozycja_x] = 'W';
                else
                    break;
            }
            else if (mapa->kierunek == 'W')
            {
                if (mapa->mapa[mapa->pozycja_y][mapa->pozycja_x - 1] == '_')
                    mapa->mapa[mapa->pozycja_y][mapa->pozycja_x - 1] = 'W';
                else
                    break;
            }
            else if (mapa->kierunek == 'E')
            {
                if (mapa->mapa[mapa->pozycja_y][mapa->pozycja_x + 1] == '_')
                    mapa->mapa[mapa->pozycja_y][mapa->pozycja_x + 1] = 'W';
                else
                    break;
            }
            printf("JEST SCIANA!!\n");
            break;
        }
        x = dane->x[0];
        y = dane->y[0];
    }
    return mapa;
}
mapa *obroc_explore(mapa *mapa, char *chunk, Dane *dane, char *nazwa_folderu, char *swiat)
{
    mapa = uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
    mapa = uzupelnij_zapisz_wypisz_macierz(mapa, explore(swiat), chunk, dane, nazwa_folderu);
    return mapa;
}

char *wykonaj_ruch(mapa *stan_mapy, int *bilans_rotacji, int y_pocz, int x_pocz)
{
    //printf("stan mapy->kierunek:%c\n", stan_mapy->kierunek);
    //printf("bilans rotacji=%d\n", bilans_rotacji[0]);
    //printf("pozycja y %d x %d\nrozmiar y %d x %d\nwektor y %d x %d\nbilans rotacji %d \n yw funkcji %i x w funkcji %c\n", stan_mapy->pozycja_y, stan_mapy->pozycja_x, stan_mapy->rozmiar_y, stan_mapy->rozmiar_x, stan_mapy->wektor_y, stan_mapy->wektor_x, y_pocz, x_pocz);
    if (stan_mapy->pozycja_y + 1 > stan_mapy->rozmiar_y)
    {
        doklejanie_gora(stan_mapy);
    }
    if (stan_mapy->pozycja_y - 1 < 0)
    {
        doklejanie_dol(stan_mapy);
    }
    if (stan_mapy->pozycja_x - 1 < 0)
    {
        doklejanie_lewo(stan_mapy);
    }
    if (stan_mapy->pozycja_x + 1 > stan_mapy->rozmiar_x)
    {
        doklejanie_prawo(stan_mapy);
    }
    //w prawo +1 w lewo -1
    if (bilans_rotacji[0] == 4 && stan_mapy->pozycja_y == y_pocz && stan_mapy->pozycja_x == x_pocz)
    {
        bilans_rotacji[0] = 0;
        printf("mam mam ścianę wewnetrzna!\n");
        return "rotate_left_seek";
    }
    if (bilans_rotacji[0] == -4 && stan_mapy->pozycja_y == y_pocz && stan_mapy->pozycja_x == x_pocz)
    {
        printf("mam przeszkodę zewnetrzna!\n");
    }
    if (stan_mapy->kierunek == 'N') //polnoc ,gora
    {

        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == '_')
        {

            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji[0]++;

            return "M_Rr_M";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {

            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji[0]--;

            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] != 'W')
        {

            return "move";
        }
        else
        {
            bilans_rotacji[0]--;

            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'S') //poludnie ,dol
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji[0]++;
            return "M_Rr_M";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] != 'W')
        {
            return "move";
        }
        else
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'E') //wschod , prawo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x + 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji[0]++;
            return "M_Rr_M";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x + 1] == 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] == 'W')
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x + 1] != 'W')
        {
            return "move";
        }
        else
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
    }
    if (stan_mapy->kierunek == 'W') //zachod , lewo
    {
        if (stan_mapy->mapa[stan_mapy->pozycja_y - 1][stan_mapy->pozycja_x - 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == '_' ||
            stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == '_')
        {
            return "explore";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W')
        {
            bilans_rotacji[0]++;
            return "M_Rr_M";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x - 1] == 'W' &&
                 stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W')
        {
            return "move";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y + 1][stan_mapy->pozycja_x] == 'W' && stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] == 'W')
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
        else if (stan_mapy->mapa[stan_mapy->pozycja_y][stan_mapy->pozycja_x - 1] != 'W')
        {
            return "move";
        }
        else
        {
            bilans_rotacji[0]--;
            return "rotate_left";
        }
    }
    return "wtf";
}
mapa *uzupelnij_zapisz_wypisz_macierz(mapa *mapa, char *url, char *chunk, Dane *dane, char *nazwa_folderu)
{
    chunk = make_request(url);
    dane = interpret_response(chunk, dane);
    mapa = uzupelnij_macierz(mapa, dane);
    zapisz_macierz(nazwa_folderu, mapa);
    wypisz(mapa);
    return mapa;
}
void co_zrobic(char *odp, mapa *mapa, char *swiat, char *chunk, Dane *dane, char *nazwa_folderu, int *ile_ruchow)
{
    if (strcmp(odp, "rotate_left") == 0)
    {
        uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "left"), chunk, dane, nazwa_folderu);
        ile_ruchow[0]++;
    }
    else if (strcmp(odp, "rotate_right") == 0)
    {
        uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
        ile_ruchow[0]++;
    }
    else if (strcmp(odp, "move") == 0)
    {
        uzupelnij_zapisz_wypisz_macierz(mapa, move(swiat), chunk, dane, nazwa_folderu);
        ile_ruchow[0]++;
    }
    else if (strcmp(odp, "explore") == 0)
    {
        uzupelnij_zapisz_wypisz_macierz(mapa, explore(swiat), chunk, dane, nazwa_folderu);
        ile_ruchow[0] + 3;
    }
    else if (strcmp(odp, "M_Rr_M") == 0)
    {
        ile_ruchow[0] + 6;
        uzupelnij_zapisz_wypisz_macierz(mapa, move(swiat), chunk, dane, nazwa_folderu);
        uzupelnij_zapisz_wypisz_macierz(mapa, explore(swiat), chunk, dane, nazwa_folderu);
        uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
        uzupelnij_zapisz_wypisz_macierz(mapa, move(swiat), chunk, dane, nazwa_folderu);
    }
    else if (strcmp(odp, "rotate_left_seek") == 0)
    {
        ile_ruchow[0]++;
        uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "left"), chunk, dane, nazwa_folderu);
        mapa = znajdz_sciane(mapa, chunk, dane, nazwa_folderu, swiat, ile_ruchow);
    }
    else if (strcmp(odp, "wtf") == 0)
        printf("MAMY PROBLEM(funckja wykonaj_ruch)!\n");
}
mapa *odkryj_mape(mapa *mapa, char *swiat, Dane *dane, char *chunk, char *nazwa_folderu)
{
    int *ile_ruchow = malloc(sizeof(int));
    ile_ruchow[0] = 0;
    int *bilans_rotacji = malloc(sizeof(int) * 2);
    bilans_rotacji[0] = 0;
    int w = 0;
    for (w; w < 3; w++)
    {
        ile_ruchow[0] + 4;
        mapa = obroc_explore(mapa, chunk, dane, nazwa_folderu, swiat);
        if (strcmp(dane->field[1], "wall") == 0)
            break;
    }
    wypisz(mapa);

    if (w == 2)
    {
        mapa = uzupelnij_zapisz_wypisz_macierz(mapa, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
        ile_ruchow[0]++;
        mapa = znajdz_sciane(mapa, chunk, dane, nazwa_folderu, swiat, ile_ruchow);
    }
    printf("mapa pozycja y %d x %d\n", mapa->pozycja_y, mapa->pozycja_x);
    int x_pocz = mapa->pozycja_x;
    int y_pocz = (int)mapa->pozycja_y;

    for (int i = 0; i < 100; i++)
    {

        char *co = wykonaj_ruch(mapa, bilans_rotacji, y_pocz, x_pocz);

        co_zrobic(co, mapa, swiat, chunk, dane, nazwa_folderu, ile_ruchow);

        if (mapa->pozycja_y == y_pocz && mapa->pozycja_x == x_pocz && bilans_rotacji[0] == -4)
            break;
    }
    printf("wykonano w %d ruchach!", ile_ruchow[0]);

    wypisz(mapa);
    return mapa;
}
