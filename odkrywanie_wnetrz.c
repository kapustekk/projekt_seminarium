#include "wpisanie.h"
#include "mapa.h"
#include "logic.h"

mapa *chodzenie_po_odkrytym(mapa *mapa, char *swiat, int kierunek, int koniecx, int koniecy)
{
    char *chunk = (char *)malloc(sizeof(char *));
    Dane *dane = malloc(sizeof(Dane));
    int koncowy_x, koncowy_y;
    printf("dziala??\n");
    chunk = make_request(move(swiat));
    dane = interpret_response(chunk, dane);
    mapa->pozycja_y = dane->y[0] + mapa->wektor_y;
    mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
    printf("dziala??\n");
    mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
    int poczatkowy_y = mapa->pozycja_y;
    int poczatkowy_x = mapa->pozycja_x;
    koncowy_x = -11;
    koncowy_y = -11;
    printf("dziala??\n");
    //wypisz(mapa);
    while (poczatkowy_x != koncowy_x || poczatkowy_y != koncowy_y)
    {
        chunk = make_request(move(swiat));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        if (koniecx == mapa->pozycja_x && koniecy == mapa->pozycja_y)
            return mapa;
        mapa->pozycja_y = dane->y[0] + mapa->wektor_y;
        mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
        wypisz(mapa);
        poczatkowy_x = koncowy_x;
        poczatkowy_y = koncowy_y;
        koncowy_x = dane->y[0];
        koncowy_y = dane->x[0];
        printf("poczatkowy x %d,poczatkowy y %d, koncowy y %d x %d\n", poczatkowy_y, poczatkowy_x, koncowy_y, koncowy_x);
    }
    chunk = make_request(explore(swiat));
    dane = interpret_response(chunk, dane);
    mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
    printf("jest sciana!!!!!!!\n");
    if (kierunek == 1 && poczatkowy_x != mapa->pozycja_x && poczatkowy_y != mapa->pozycja_y)
    {
        printf("prawo\n");
        chunk = make_request(rotate(swiat, "right"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        chunk = make_request(move(swiat));
        dane = interpret_response(chunk, dane);
        mapa->pozycja_y = dane->y[0];
        mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        if (koniecx == mapa->pozycja_x && koniecy == mapa->pozycja_y)
            return mapa;
        wypisz(mapa);
        chunk = make_request(rotate(swiat, "right"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
    }
    else if (kierunek == -1 && poczatkowy_x != mapa->pozycja_x && poczatkowy_y != mapa->pozycja_y)
    {
        printf("lewo\n");
        chunk = make_request(rotate(swiat, "left"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        chunk = make_request(move(swiat));
        mapa->pozycja_y = dane->y[0] + mapa->wektor_y;
        mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        if (koniecx == mapa->pozycja_x && koniecy == mapa->pozycja_y)
            return mapa;
        wypisz(mapa);
        chunk = make_request(rotate(swiat, "left"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
    }
    printf("poczatkowy y %d x %d,mapa pozycja y %d x %d\n", poczatkowy_y, poczatkowy_x, mapa->pozycja_y, mapa->pozycja_x);
    while (kierunek == 1 && poczatkowy_x == mapa->pozycja_x && poczatkowy_y == mapa->pozycja_y)
    {
        printf("waruneczek\n");
        chunk = make_request(rotate(swiat, "left"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        chunk = make_request(move(swiat));

        mapa->pozycja_y = dane->y[0] + mapa->wektor_y;
        mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        if (koniecx == mapa->pozycja_x && koniecy == mapa->pozycja_y)
            return mapa;
        wypisz(mapa);
    }
    while (kierunek == -1 && poczatkowy_x == mapa->pozycja_x && poczatkowy_y == mapa->pozycja_y)
    {
        printf("waruneczek\n");
        chunk = make_request(rotate(swiat, "right"));
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        chunk = make_request(move(swiat));

        mapa->pozycja_y = dane->y[0] + mapa->wektor_y;
        mapa->pozycja_x = dane->x[0] + mapa->wektor_x;
        dane = interpret_response(chunk, dane);
        mapa = wpisanie_do_mapy(mapa, dane->y[0], dane->x[0], zwroc_litere(dane, 0));
        if (koniecx == mapa->pozycja_x && koniecy == mapa->pozycja_y)
            return mapa;
        wypisz(mapa);
    }
    printf("pozycja koncowa y %d, x %d, direction %c koniecy %d koniecx %d\n", mapa->pozycja_y, mapa->pozycja_x, mapa->kierunek, koniecy, koniecx);
    //mapa = chodzenie_po_odkrytym(mapa, swiat, -kierunek, koniecx, koniecy);
    //}
    return mapa;
}