#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../cJSON/cJSON.h"

typedef struct _Dane{
    int x[3];
    int y[3];
    char* field[3];
}Dane;

typedef struct _Macierz {
    int r;
    int c;
    int **tab;
}Macierz;


Macierz* wczytaj(FILE * fin) {
    int i,j;
    Macierz *m=(Macierz*) malloc(sizeof(Macierz));
    fscanf(fin, "%d", &m->r);
    fscanf(fin, "%d", &m->c);

    m->tab = (int**) malloc(sizeof(int*) * m->r);
    for (i=0;i<m->r;i++)
        m->tab[i] = (int*) malloc(sizeof(int) * m->c);
    
    for (i=0; i < m->r; i++)
        for (j=0; j < m->c; j++)
            fscanf(fin, "%d", &m->tab[i][j]);
    return m;
}

void wypisz(Macierz *m) {
    int c,r;
    printf("       ");
    for(int x=0; x<m->c; x++)
    {
        printf("%2d",x);
    }
    printf("\n       ");
    for(int x=0; x<m->c; x++)
    printf("---");
    printf("\n");
    for (c = m->c; c >= 0 ; c--) {
    printf("%3d | [ ",c);
        for (r=0; r < m->r; r++) {
        // for (r=m->r -1; r >=0; r--) {
            printf("%d ", m->tab[r][c]);
        }
            printf("]\n");
    }
    printf("\n");
}

void zwolnij(Macierz *m){
    for (int i = 0; i <m->r; i++) 
    free(m->tab[i]);
    free(m->tab);
    free(m);
}

void zapisz_macierz(char nazwa[], Macierz *m) {
    FILE * fout = fopen(nazwa, "w");
    int i,j;

    fprintf(fout, "%d\n%d\n", m->r, m->c);
    for (i = 0; i < m->r; i++)
        for (j=0; j < m->c; j++) 
            fprintf(fout, "%d\n", m->tab[i][j]);

    fclose(fout);
}

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
Dane* interpret_response(const char* const chunk,Dane *dane)
{
    // printf("json::: %s",chunk);
    const cJSON *payload = NULL;
    // const cJSON *status = NULL;

    // printf("zainicjowalem payload\n");
    cJSON *game_json = cJSON_Parse(chunk);
    // printf("parse\n");
    if (game_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
    else {
        payload = cJSON_GetObjectItemCaseSensitive(game_json, "payload");
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *list =  cJSON_GetObjectItemCaseSensitive(payload, "list");
        if(list!=NULL)
        {
            
                cJSON *object = NULL;
                int i=0;
                // printf("inicjuje obiekt\n");
                cJSON_ArrayForEach(object,list)
                {
                    cJSON *x = cJSON_GetObjectItemCaseSensitive(object, "x");
                    cJSON *y = cJSON_GetObjectItemCaseSensitive(object, "y");
                    cJSON *type = cJSON_GetObjectItemCaseSensitive(object, "type");
                    dane->x[i]=x->valueint;
                    dane->y[i]=y->valueint;
                    dane->field[i] =(char*)malloc(sizeof(char)*strlen((type->valuestring)+1));
                    strcpy(dane->field[i], type->valuestring);
                    i++;
                }
        }           
            
        else if (current_x != NULL) {
            cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
            cJSON *field_type =  cJSON_GetObjectItemCaseSensitive(payload, "field_type");
            dane->x[0]=current_x->valueint;
            dane->y[0]=current_y->valueint;
            dane->field[0] =field_type->valuestring;
        }
        
    }
    return dane;
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
    
    char*chunk= (char*)malloc(sizeof(char)*1024);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info/token
    char *url = (char*)malloc(sizeof(char)*1024);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/info");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* explore(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*1024);
    
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*1024);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* reset(char *token) {
    
    char*chunk= (char*)malloc(sizeof(char)*1024);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/explore/token
    char *url = (char*)malloc(sizeof(char)*1024);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/reset");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}


char* move(char *token) {
    char*chunk= (char*)malloc(sizeof(char)*1024);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move/token
    char *url = (char*)malloc(sizeof(char)*1024);
    strcpy(url,"http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/move");
    strcat(url,"/");
    strcat(url,token);
    chunk = make_request(url);
    free(url);
    return chunk;
}

char* rotate(char *token, char *direction)
{
    char*chunk= (char*)malloc(sizeof(char)*1024);
    // http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/rotate/token/direction
    char*url = (char*)malloc(sizeof(char)*1024);
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

Macierz *uzupelnij_macierz(Macierz *m, Dane *dane)
{

    if(dane->x[1]!= NULL)//czyli jesli mamy explore
    {
        for(int i=0; i<3; i++)
        {
        int a;
        if(strcmp(dane->field[i],"grass")==0)
        a=2;
        else if(strcmp(dane->field[i],"sand")==0)
        a=3;
        else if(strcmp(dane->field[i],"wall")==0)
        a=1;
        
        m->tab[dane->x[i]][dane->y[i]] = a;
        }
    }
    else    //dla funkcji ruchu 
    {
        int a;
        if(strcmp(dane->field[0],"grass")==0)
        a=2;
        else if(strcmp(dane->field[0],"sand")==0)
        a=3;
        else if(strcmp(dane->field[0],"wall")==0)
        a=1;

        m->tab[dane->x[0]][dane->y[0]] = a;
    }
    return m;

}
Macierz *wyczysc_macierz(Macierz *m)
{
    for(int i = 0; i<m->r;i++)
    for(int j=0; j<m->c;j++)
    {
        m->tab[i][j] = 0; 
    }
    
    return m;
}

int main(int argc, char **argv)
{
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

    char *swiat=(char*)malloc(sizeof(char*));
    strcpy(swiat,"qwerty_12");
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
