#ifndef INGREDIENTI_H
#define INGREDIENTI_H

typedef struct ingrediente *ingredienti;

ingredienti leggi_ingredienti(ingredienti ing);
int info_ingrediente(ingredienti ing, char *nome);
int ricerca_calorie_costo(ingredienti ing, char *nome, float *calorie, float *costo);
void stampa_ingredienti(ingredienti ing);

#endif


