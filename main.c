#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"


int main()
{

    char **carte = malloc(CARTE_TAILLE*sizeof(char*));
    int n_map=choix_map();
    generation_carte(n_map,carte);
    affiche_tableau(carte,CARTE_TAILLE);
    /*Combattant chevalier1 = creerCombattant(500, 500, 20, 50, 5, 1);
    Combattant chevalier2 = creerCombattant(500, 500, 20, 50, 5, 1);
    Combattant combattants[2] = {chevalier1, chevalier2};
    while(chevalier1.pvCourant > 0.0001 && chevalier2.pvCourant > 0.0001) {
        combattre(chevalier1, &chevalier2);

        printf("\n--- Stats après attaque ---\n");
        afficherStats(combattants, 2);

    }
    */
    for(int a=0;a<CARTE_TAILLE;a++)
	{
		free(carte[a]);
	}
	free(carte);
    return 0;

}
