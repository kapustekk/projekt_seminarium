#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "mapa.h"
#include "read_json.h"

#define A 1024

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *) userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

char * make_request(char *url)
{
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        /* to jest funkcja 'callback', która będzie wywołana przez curl gdy odczyta on kawałek danych
       ta funkcja musi mieć wywołanie zgodne z wymaganiami, które możesz sprawdzić tutaj:
       https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html */
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        /* to jest adress struktury, który będzie przekazywany do naszej funkcji 'callback',
       do tej struktury nasz funkcja 'callback' będzie dopisywać wynik */
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        /* Wykonaj zapytanie 'synchronicznie', to znaczy następna linijka kodu nie wykona się
       dopóki nie nadejdzie odpowiedź z serwera. */
        res = curl_easy_perform(curl);

        /* Sprawdzamy czy wystapił jakis błąd? */
        if (res != CURLE_OK)
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
        else
        {
            printf("%s", chunk.response);
        }
        /* zawsze po sobie sprzątaj */
        // interpret_response(chunk.response);
        // free(chunk.response);
        // curl_easy_cleanup(curl);
    }
    return chunk.response;
}
char* info(char *token) {
    
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* explore(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*A);
    
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* reset(char *token) {
    
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}


char* move(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/token
    char *url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* rotate(char *token, char *direction)
{
    char*chunk= (char*)malloc(sizeof(char)*A);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/token/direction
    char*url = (char*)malloc(sizeof(char)*A);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate");
    strcat(url,"/");
    strcat(url,token);
    strcat(url,"/");
    strcat(url,direction);
    chunk = make_request(url);
    // printf("chunk funkcja: %s",chunk);
    free(url);
    return chunk;
}


int main(int argc, char **argv)
{
    char *swiat="qwerty_12";
    // strcpy(swiat,"qwerty_12");
    Dane *dane=malloc(sizeof(Dane));
    char* nazwa_folderu="A.txt";
    char*chunk=(char*)malloc(sizeof(char*));
    // Dane *dane=(Dane*)malloc(sizeof(Dane*));
    FILE *fin=fopen(nazwa_folderu,"r");
    Macierz *a;
    a=wczytaj(fin);
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
    if (argc==1)
    {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
    }
    else
    for (int i=1;i<argc;i++)
    {
        if(strcmp(argv[i],"M")==0)
        {
            chunk = move(swiat);
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"Rr")==0)
        {
            chunk = rotate(swiat,"right");
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"Rl")==0)
        {
            chunk = rotate(swiat,"left");
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i],"info")==0)
        {
            chunk = info(swiat);
            dane = interpret_response(chunk,dane);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i], "E")==0)
        {
            chunk = explore(swiat);
            dane = interpret_response(chunk,dane);
            printf("%d, %d, %s",dane->x[0],dane->y[0],dane->field[0]);
            a=uzupelnij_macierz(a,dane);
        }
        else if(strcmp(argv[i], "reset")==0)
        {
            chunk = reset(swiat);
            dane = interpret_response(chunk,dane);
            a = wyczysc_macierz(a);
            a=uzupelnij_macierz(a,dane);
        }
        else
        {
        printf("podaj operacje!\n");
        printf("Move - \"M\"; Rotate - \"Rr/Rl\"; Info - \"info\"; Explore - \"E\"; Reset - \"reset\";\n");
        }
        wypisz(a);
        zapisz_macierz(nazwa_folderu,a);   

    }
    // char *url = argc < 2 ? "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/qwerty_12" : argv[1];
    return 0;
}
