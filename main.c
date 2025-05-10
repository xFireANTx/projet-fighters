
// créer une boucle pour le déplacement de chaque combattant

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "map.h"
#include "combat.h"
#include "utilitaire.h"
#include "tours.h"

int main()
{
    //Initialisation de la carte
    char **carte = malloc(CARTE_TAILLE*sizeof(char*));
    int n_map=choix_map();
    generation_carte(n_map,carte);
    printf("Voici la carte choisie :\n");
    affiche_tableau(carte,CARTE_TAILLE);

    //Initialisation des combattants, des équipes et des positions de chaque perso sur la carte
    Equipe equipe1= creerEquipe(1,carte);
    Equipe equipe2= creerEquipe(2,carte);
    affiche_equipe(equipe1);
    affiche_equipe(equipe2);
    printf("\n");

    //Initialisation de l'ordre d'action des combattants
    Combattant tabCombattants[6];
    definirOrdreAttaque(equipe1,equipe2,tabCombattants);


    tours(equipe1,equipe2,tabCombattants,carte);

    for(int a=0;a<CARTE_TAILLE;a++)
	{
		free(carte[a]);
	}
	free(carte);

    return 0;

}
