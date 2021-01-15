#include "mapa.h"

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

Macierz *uzupelnij_macierz(Macierz *m, Dane *dane)
{

    if(dane->field[1]!= NULL)//czyli jesli mamy explore
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