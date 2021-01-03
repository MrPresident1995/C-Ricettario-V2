#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingredienti.h"
#include "ricette.h"

int main()
{
    int op, fine;
    char nome[256];
    ingredienti ing= NULL;
    ricetta head;

    ing= leggi_ingredienti(ing);
    head= leggi_ricette();

    fine= 0;
    printf("Opzioni disponibili\n");
    printf("1- Informazioni su una ricetta\n");
    printf("2- Informazioni su un ingrediente\n");
    printf("3- Calcolo costo di una ricetta\n");
    printf("4- Calcolo apporto calorico di una ricetta\n");
    printf("5- Stampa dell'elenco delle ricette presenti in memoria\n");
    printf("6- Stampa dell'elenco degli ingredienti presenti in memoria\n");
    printf("7- Stampa dell'elenco delle ricette contenenti un dato ingrediente\n");
    printf("8- Aggiunta di una nuova ricetta\n");
    printf("9- Fine\n");
    while(fine!=1)
    {
        printf("\nOpzione: ");
        scanf("%d", &op);
        switch(op)
        {
            case 1:     printf("Inserire il nome della ricetta da cercare: ");
                        scanf("%s", nome);
                        if(info_ricetta(head, nome)!=1)
                            printf("Ricetta non trovata\n");
                        break;

            case 2:     printf("Inserire il nome dell'ingrediente da cercare: ");
                        scanf("%s", nome);
                        if(info_ingrediente(ing, nome)!=1)
                            printf("Ingrediente non trovato\n");
                        break;

            case 3:     printf("Inserire il nome della ricetta da calcolare: ");
                        scanf("%s", nome);
                        printf("Il costo della ricetta e' pari a: %.2f\n", calcolo_costo(ing, head, nome));
                        break;

            case 4:     printf("Inserire il nome della ricetta da calcolare: ");
                        scanf("%s", nome);
                        printf("L'apporto calorico della ricetta e' pari a: %.2f\n", calcolo_calorie(ing, head, nome));
                        break;

            case 5:     stampa_ricette(head);
                        break;

            case 6:     stampa_ingredienti(ing);
                        break;

            case 7:     printf("Inserire il nome dell'ingrediente da cercare: ");
                        scanf("%s", nome);
                        if(ricerca_ingrediente(head, nome)==0)
                            printf("Ingrediente non trovato\n");
                        break;

            case 8:     head= aggiunta_ricetta(head);
                        break;

            case 9:     fine= 1;
                        break;

            default:    printf("Opzione non disponibile\n");
        }
    }

    return 0;
}
