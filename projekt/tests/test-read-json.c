#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../read_json.h"
#define A 1024
int check_info(Dane *dane)
{
    if((dane->x[0]==1)&&(dane->y[0]==1)&&(strcmp(dane->field[0],"grass")==0))
    return 0;
    else
    return 1;
}
int check_explore(Dane *dane)
{
    if((dane->x[0]==2)&&(dane->y[0]==2)&&(strcmp(dane->field[0],"sand")==0))
    if((dane->x[1]==2)&&(dane->y[1]==1)&&(strcmp(dane->field[1],"grass")==0))
    if((dane->x[2]==2)&&(dane->y[2]==0)&&(strcmp(dane->field[2],"wall")==0))
    return 0;
    else
    return 1;

}
int printf_data_info(Dane *dane)
{
    printf("current_x = %d\n",dane->x[0]);
    printf("current_y = %d\n",dane->y[0]);  
    printf("field = %s\n",dane->field[0]);
}
int printf_data_explore(Dane*dane)
{
    for (int i=0;i<3;i++)
    {
        printf("x[%d] = %d\n",i,dane->x[i]);
        printf("y[%d] = %d\n",i,dane->y[i]);  
        printf("field[%d] = %s\n",i,dane->field[i]);
    }

}
int main(int argc, char **argv)
{
    char explore_json[A];
    char info_json[A];
    Dane *dane=malloc(sizeof(Dane));
    FILE *fin1=fopen("tests/info.json","r");
    FILE *fin2=fopen("tests/explore.json","r");
    fread(explore_json,1,1023,fin2);
    fread(info_json,1,1023,fin1);
    fclose(fin2);
    fclose(fin1);

    printf("reading json:\n%s\n",info_json);
    dane = interpret_response(info_json,dane);
    if(check_info(dane)==0)
    printf("SUCCESS! messgae 1 - info is correct!\n");
    else if(check_info(dane)==1)
    printf("FAILED! messgae 1 - info is not correct!\n");
    printf_data_info(dane);
    
    printf("----------------\n");
    printf("reading json:\n%s\n",explore_json);
    dane = interpret_response(explore_json,dane);
    if(check_explore(dane)==0)
    printf("SUCCESS! messgae 2 - explore is correct!\n");
    else if(check_explore(dane)==1)
    printf("FAILED! messgae 2 - explore is not correct!\n");
    printf_data_explore(dane);

    free(dane);
    free(explore_json);
}