#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "mapa.h"
#include "read_json.h"
#include "connect.h"
#include "url.h"

int main(int argc, char **argv)
{
    char *swiat = "qwerty_13";
    // strcpy(swiat,"qwerty_12");
    Dane *dane = malloc(sizeof(Dane));
    char *nazwa_folderu = "A.txt";
    char *chunk = (char *)malloc(sizeof(char *));
    // Dane *dane=(Dane*)malloc(sizeof(Dane*));
    FILE *fin = fopen(nazwa_folderu, "r");
    //mapa *a = wczytaj(fin);
    wektor *wektor = malloc(sizeof(wektor));
    mapa *a = wczytaj(fin, wektor);
    //wektor->y = 0;
    //wektor->x = 0;
    //printf("inicjaliznazja (info request) stworzenie wektora wpisanie obecnej pozycji\n");
    //chunk = make_request(info(swiat));
    //dane = interpret_response(chunk, dane);
    //pierwsze_wczytanie(*dane->x, *dane->y, &wektor->x, &wektor->y, 2);
    //a = uzupelnij_macierz(a, dane, wektor);
    //printf("poczatkowa inicjalizacja sucess\n");
    //0-unknown field ; 1 - WALL; 2-GRASS; 3-SAND;
    //KONCOWA MACIERZ
    // 1 1 1 1 1 1 1 1 1
    // 1 2 2 2 2 1 2 2 1
    // 1 2 1 1 2 1 2 1 1
    // 1 2 2 1 2 1 2 2 1
    // 1 2 2 2 2 2 2 2 1
    // 1 2 1 1 2 1 2 2 1
    // 1 2 1 3 2 1 2 2 1
    // 1 2 1 1 2 1 2 1 1
    // 1 2 3 1 2 1 3 3 1
    // 1 2 3 2 2 1 2 2 1
    // 1 2 2 2 2 1 2 2 1
    // 1 1 1 1 1 1 1 1 1

    // char *url;
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
                // printf("%d, %d, %s",dane->x[0],dane->y[0],dane->field[0]);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else if (strcmp(argv[i], "reset") == 0)
            {
                chunk = make_request(reset(swiat));
                dane = interpret_response(chunk, dane);
                // printf("c323 tu %d %d\n", wektor->y, wektor->x);
                a = wyczysc_macierz(a);
                // printf("cso tu %d %d\n", wektor->y, wektor->x);
                a = uzupelnij_macierz(a, dane, wektor);
            }
            else
            {
                printf("podaj operacje!\n");
                printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
            }
            //a->mapa[0][1] = 'K';
            wypisz(a);
            printf("pozycja koncowa x %d, y %d, direction %c wektor koncowy y %d x %d\n", a->pozycja_y, a->pozycja_x, a->kierunek, wektor->y, wektor->x);
            zapisz_macierz(nazwa_folderu, a,wektor);
        }
    }
    //a = wyczysc_macierz(a);
    // a->mapa[3][3] = 'f';
    //zapisz_macierz("A.txt", a);
    //wczytaj(fin);
    //a->mapa[1][1] = 'b';
    //wypisz(a);
    //zapisz_macierz("A.txt", a);
    // char *url = argc < 2 ? "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_12" : argv[1];
    return 0;
}
