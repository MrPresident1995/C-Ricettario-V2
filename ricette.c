#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ricette.h"

struct ricette
{
    char *nome;
    int tempo;
    int num_ing_ric;
    char **lista;
    int *grammi;
    ricetta next;
};

ricetta leggi_ricette()
{
    FILE* fp;
    int i, num, tempo, num_ing_ric;
    char nome[31];
    ricetta head;

    fp= fopen("ricette.txt", "r"); //APERTURA + CONTROLLO FILE RICETTE
    if(fp==NULL)
    {
        printf("Errore");
        exit(-2);
    }

    head= malloc(sizeof(*head)); //ALLOCAZIONE TESTA DELLA LISTA RICETTE
    head->next= NULL;

    fscanf(fp, "%d", &num); //ACQUISIZIONE RICETTE
    for(i=0; i<num; i++)
    {
        fscanf(fp, "%s%d%d", nome, &tempo, &num_ing_ric);
        head= instail(head, nome, tempo, num_ing_ric, fp, 0);
    }

    return head;
}

ricetta newnode(char *nome, int tempo, int num_ing_ric, ricetta next, FILE* fp, int tipo)
{
    int j;
    char text[31];
    ricetta x= malloc(sizeof(*x));

    if(x==NULL)
        return NULL;
    else
    {
        x->nome= strdup(nome);
        x->tempo= tempo;
        x->num_ing_ric= num_ing_ric;
        x->grammi= malloc(num_ing_ric*sizeof(int));
        x->lista= malloc(num_ing_ric*sizeof(char*));
        if(tipo==0) //INPUT INGREDIENTI RICETTA DA FILE
            for(j=0; j<num_ing_ric; j++)
            {
                fscanf(fp, "%s%d", text, &x->grammi[j]);
                x->lista[j]= strdup(text);
            }
        else //INPUT INGREDIENTI RICETTA DA TASTIERA
            for(j=0; j<num_ing_ric; j++)
            {
                printf("%d: ", j+1);
                scanf("%s%d", text, &x->grammi[j]);
                x->lista[j]= strdup(text);
            }
        x->next= next;
    }
    return x;
}

ricetta instail(ricetta h, char *nome, int tempo, int num_ing_ric, FILE* fp, int tipo)
{
    ricetta x;

    if(h==NULL) //CONTROLLA CHE NON SIA LA TESTA
        return newnode(nome, tempo, num_ing_ric, NULL, fp, tipo);

    for(x=h; x->next!=NULL; x=x->next); //SCORRE LA LISTA FINO ALLA CODA

    x->next = newnode(nome, tempo, num_ing_ric, NULL, fp, tipo); //AGGIUNGE IL NUOVO NODO

    return h;
}

int info_ricetta(ricetta h, char *nome)
{
    ricetta x;

    for(x=h->next; x!=NULL; x=x->next)
        if(strcmp(nome, x->nome)==0)
        {
            printf("Tempo di preparazione: %d\n", x->tempo);
            printf("Numero ingredienti necessari: %d\n", x->num_ing_ric);
            return 1;
        }

    return 0;
}

float calcolo_costo(ingredienti ing, ricetta h, char *nome)
{
    int j, trovato= 0;
    float calorie, costo, costo_tot= 0;
    ricetta x;

    for(x=h->next; x!=NULL; x=x->next) //SCORRE LA LISTA RICETTE ALLA RICERCA DELLA RICETTA DESIDERATA
        if(strcmp(nome, x->nome)==0)
        {
            trovato= 1;
            break;
        }

    if(trovato==0) //FALLIMENTO RICERCA
        return -1;

    for(j=0; j<x->num_ing_ric; j++) //SCORRIMENTO LISTA INGREDIENTI DELLA RICETTA
        if(ricerca_calorie_costo(ing, x->lista[j], &calorie, &costo)==1)
        {
            calorie= calorie/1000;
            if(calorie<1)
                calorie= 1;
            costo_tot= costo_tot + calorie*costo;
        }

    return costo_tot;
}

float calcolo_calorie(ingredienti ing, ricetta h, char *nome)
{
    int j, trovato= 0;
    float costo, calorie, calorie_tot= 0;
    ricetta x;

    for(x=h->next; x!=NULL; x=x->next) //SCORRE LA LISTA RICETTE ALLA RICERCA DELLA RICETTA DESIDERATA
        if(strcmp(nome, x->nome)==0)
        {
            trovato= 1;
            break;
        }

    if(trovato==0) //FALLIMENTO RICERCA
        return -1;

    for(j=0; j<x->num_ing_ric; j++) //SCORRIMENTO LISTA INGREDIENTI DELLA RICETTA
        if(ricerca_calorie_costo(ing, x->lista[j], &calorie, &costo)==1)
            calorie_tot= calorie_tot + calorie*x->grammi[j];

    return calorie_tot;
}

int ricerca_ingrediente(ricetta h, char *nome)
{
    int j, trovato= 0;
    ricetta x;

    for(x=h->next; x!=NULL; x=x->next)
        for(j=0; j<x->num_ing_ric; j++)
            if(strcmp(nome, x->lista[j])==0)
            {
                printf("%s\n", x->nome);
                trovato= 1;
            }

    if(trovato==1)
        return 1;
    else
        return 0;
}

void stampa_ricette(ricetta h)
{
    ricetta x;

    for(x=h->next; x!=NULL; x=x->next)
        printf("%s\n", x->nome);
}

ricetta aggiunta_ricetta(ricetta h)
{
    char nome[31];
    int tempo, num_ing_ric;

    printf("Inserire il nome della ricetta: ");
    scanf("%s", nome);
    printf("Inserire il tempo di preparazione: ");
    scanf("%d", &tempo);
    printf("Inserire il numero di ingredienti necessari: ");
    scanf("%d", &num_ing_ric);
    h= instail(h, nome, tempo, num_ing_ric, 0, 1);

    return h;
}
