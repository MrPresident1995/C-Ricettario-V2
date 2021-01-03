#include "ingredienti.h"

#ifndef RICETTE_H
#define RICETTE_H

typedef struct ricette *ricetta;

ricetta leggi_ricette();
ricetta newnode(char *nome, int tempo, int num_ing_ric, ricetta next, FILE* fp, int tipo);
ricetta instail(ricetta h, char *nome, int tempo, int num_ing_ric, FILE* fp, int tipo);
int info_ricetta(ricetta h, char *nome);
float calcolo_costo(ingredienti ing, ricetta h, char *nome);
float calcolo_calorie(ingredienti ing, ricetta head, char *nome);
void stampa_ricette(ricetta h);
int ricerca_ingrediente(ricetta h, char *nome);
ricetta aggiunta_ricetta(ricetta h);

#endif

