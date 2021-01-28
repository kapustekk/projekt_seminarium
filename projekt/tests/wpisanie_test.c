#include "../mapa.h"
#include "../wpisanie.h"

int main()
{
    mapa *map = (mapa *)malloc(sizeof(mapa));
    map = resetuj_mape(map);
    map->mapa[3][3] = 'X';
    map->mapa[4][3] = 'Y';
    map->kierunek = 'N';
    wypisz(map);
    map = wpisanie_do_mapy(map, 2, 2, 'F');
    printf("kierunek= %c\n", map->kierunek);
    map->mapa[4][4] = 'D';
    wypisz(map);
    map = wpisanie_do_mapy(map, -3, 2, 'C');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    map = wpisanie_do_mapy(map, -3, 8, 'G');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    map = wpisanie_do_mapy(map, 7, 2, 'I');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    zapisz_macierz("B.txt", map);
    wczytaj("B.txt", map);
    map = wpisanie_do_mapy(map, -3, -3, 'Q');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    zapisz_macierz("B.txt", map);
    map->mapa[3][3] = 'C';
    wypisz(map);
    map = wpisanie_do_mapy(map, 5, 2, 'F');
    printf("kierunek= %c\n", map->kierunek);
    map->mapa[4][4] = 'D';
    wypisz(map);
    map = wpisanie_do_mapy(map, 7, 2, 'C');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    map = wpisanie_do_mapy(map, -13, 8, 'G');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    map = wpisanie_do_mapy(map, 40, 2, 'I');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    zapisz_macierz("B.txt", map);
    wczytaj("B.txt", map);
    map = wpisanie_do_mapy(map, 0, -20, 'Q');
    printf("kierunek= %c\n", map->kierunek);
    wypisz(map);
    zapisz_macierz("B.txt", map);
    zwolnij(map);
    free(map);
}