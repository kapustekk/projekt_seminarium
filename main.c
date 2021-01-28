#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "mapa.h"
#include "read_json.h"
#include "connect.h"
#include "url.h"
#include "logic.h"

int main(int argc, char **argv)
{
    char *swiat = "qwerty_13";
    Dane *dane = malloc(sizeof(Dane));
    char *nazwa_folderu = "A.txt";
    char *chunk = (char *)malloc(sizeof(char *));

    mapa *a = (mapa *)malloc(sizeof(mapa));
    alokuj_mape(a, 40, 40);

    if (argc == 1)
    {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "M") == 0)
            {

                wczytaj(nazwa_folderu, a);
                chunk = make_request(move(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane);
            }
            else if (strcmp(argv[i], "Rr") == 0)
            {

                wczytaj(nazwa_folderu, a);
                chunk = make_request(rotate(swiat, "right"));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane);
            }
            else if (strcmp(argv[i], "Rl") == 0)
            {

                wczytaj(nazwa_folderu, a);
                chunk = make_request(rotate(swiat, "left"));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane);
            }
            else if (strcmp(argv[i], "info") == 0)
            {

                wczytaj(nazwa_folderu, a);
                chunk = make_request(info(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane);
                printf("%s", chunk);
            }
            else if (strcmp(argv[i], "E") == 0)
            {
                wczytaj(nazwa_folderu, a);
                chunk = make_request(explore(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane);
            }
            else if (strcmp(argv[i], "reset") == 0)
            {
                wczytaj(nazwa_folderu, a);
                chunk = make_request(info(swiat));
                dane = interpret_response(chunk, dane);
                a->wektor_y = a->pozycja_y - dane->y[0];
                a->wektor_x = a->pozycja_x - dane->x[0];
                printf("wektor y %d x %d\n", a->wektor_y, a->wektor_x);
                zapisz_macierz(nazwa_folderu, a);
                wczytaj(nazwa_folderu, a);
                chunk = make_request(reset(swiat));
                dane = interpret_response(chunk, dane);
                a = wyczysc_macierz(a);
                a = uzupelnij_macierz(a, dane);
                zapisz_macierz(nazwa_folderu, a);
            }
            else if (strcmp(argv[i], "odkryj") == 0)
            {

                wczytaj(nazwa_folderu, a);
                a = odkryj_mape(a, swiat, dane, chunk, nazwa_folderu);
                while (odkrycie_mapy(*a) != 0)
                {

                    a = chodzenie_po_odkrytym(a, swiat, 1, a->pozycja_y, a->pozycja_x);
                    printf("odkrywanie\n");
                    uzupelnij_zapisz_wypisz_macierz(a, move(swiat), chunk, dane, nazwa_folderu);
                    uzupelnij_zapisz_wypisz_macierz(a, explore(swiat), chunk, dane, nazwa_folderu);
                    uzupelnij_zapisz_wypisz_macierz(a, rotate(swiat, "right"), chunk, dane, nazwa_folderu);
                }
            }
            else
            {
                printf("podaj operacje!\n");
                printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
            }
            printf("waielkosc mapy y %d x %d\n", a->rozmiar_y, a->rozmiar_x);
            wypisz(a);
            printf("pozycja koncowa x %d, y %d, direction %c wektor koncowy y %d x %d\n", a->pozycja_y, a->pozycja_x, a->kierunek, a->wektor_y, a->wektor_x);
            zapisz_macierz(nazwa_folderu, a);
        }
    }

    return 0;
}
