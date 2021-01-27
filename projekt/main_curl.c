#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "logic.h"

int main(int argc, char **argv)
{
    char *swiat = "qwerty_13";
    Dane *dane = malloc(sizeof(Dane));
    char *nazwa_folderu = "A.txt";
    char *chunk = (char *)malloc(sizeof(char *));
    wektor *wektor = malloc(sizeof(wektor));
    mapa *a = wczytaj(nazwa_folderu, wektor);

    if (argc == 1)
    {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
    }
    else
    {
        //printf("4co tu %d %d\n", wektor->y, wektor->x);
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "M") == 0)
            {
                chunk = make_request(move(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "Rr") == 0)
            {
                chunk = make_request(rotate(swiat, "right"));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "Rl") == 0)
            {
                chunk = make_request(rotate(swiat, "left"));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "info") == 0)
            {
                chunk = make_request(info(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane, wektor);
                printf("%s", chunk);
            }
            else if (strcmp(argv[i], "E") == 0)
            {
                chunk = make_request(explore(swiat));
                dane = interpret_response(chunk, dane);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "reset") == 0)
            {
                chunk = make_request(reset(swiat));
                dane = interpret_response(chunk, dane);
                a = wyczysc_macierz(a);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "odkryj") == 0)
            {
                odkryj_mape(a, swiat, dane, chunk, nazwa_folderu, wektor);
            }
            else
            {
                printf("podaj operacje!\n");
                printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
            }
            //a->mapa[0][1] = 'K';
            printf("waielkosc mapy y %d x %d\n", a->rozmiar_y, a->rozmiar_x);
            wypisz(a);
            printf("pozycja koncowa x %d, y %d, direction %c wektor koncowy y %d x %d\n", a->pozycja_y, a->pozycja_x, a->kierunek, wektor->y, wektor->x);
            zapisz_macierz(nazwa_folderu, a, wektor);
        }
    }
    zwolnij_mape(a);

    return 0;
}
