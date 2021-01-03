#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ingredienti.h"

struct ingrediente
{
    char *nome;
    float costo;
    float calorie;
};

static int num_ing;
int i;

ingredienti leggi_ingredienti(ingredienti ing)
{
    FILE* fp;
    char nome[31];

    fp= fopen("ingredienti.txt", "r"); //APERTURA + CONTROLLO FILE INGREDIENTI
    if(fp==NULL)
    {
        printf("Errore");
        exit(-1);
    }

    fscanf(fp, "%d", &num_ing); //LETTURA DIMENSIONE + LETTURA INGREDIENTI
    ing= malloc(num_ing*sizeof(*ing));
    for(i=0; i<num_ing; i++)
    {
        fscanf(fp, "%s%f%f", nome, &ing[i].costo, &ing[i].calorie);
        ing[i].nome= strdup(nome);
    }

    return ing;
}

int info_ingrediente(ingredienti ing, char *nome)
{
    for(i=0; i<num_ing; i++)
        if(strcmp(ing[i].nome, nome)==0)
        {
            printf("Costo ingrediente: %.2f\n", ing[i].costo);
            printf("Apporto calorico ingrediente: %.2f\n", ing[i].calorie);
            return 1;
        }

    return 0;
}

int ricerca_calorie_costo(ingredienti ing, char *nome, float *calorie, float *costo)
{
    for(i=0; i<num_ing; i++)
        if(strcmp(ing[i].nome, nome)==0)
        {
            *calorie= ing[i].calorie;
            *costo= ing[i].costo;
            return 1;
        }

    return 0;
}

void stampa_ingredienti(ingredienti ing)
{
    for(i=0; i<num_ing; i++)
        printf("%s %.2f$ %.2fg\n", ing[i].nome, ing[i].costo, ing[i].calorie);
}
