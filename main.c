
// créer une boucle pour le déplacement de chaque combattant

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

EQUIPE creerEquipe(int num_equipe) {
    EQUIPE equipe;
    equipe.equipe = num_equipe;
    printf("Entrez le nom de l'équipe %d : ", num_equipe);
    scanf("%[^\n]\n", equipe.nom); // A RENFORCER
    return equipe;
}

int main()
{

    char **carte = malloc(CARTE_TAILLE*sizeof(char*));
    int n_map=choix_map();
    generation_carte(n_map,carte);
    affiche_tableau(carte,CARTE_TAILLE);
    EQUIPE equipe1;
    EQUIPE equipe2;
    equipe1.equipe = 1;
    equipe2.equipe = 2;
    equipe1.combattant1 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 0, 7);
    equipe1.combattant2 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 0, 9);
    equipe1.combattant3 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 0, 11);
    equipe2.combattant1 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 19, 7);
    equipe2.combattant2 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 19, 9);
    equipe2.combattant3 = creerCombattant(500, 500, 20, 50, 5, 1, 2, 19, 11);

    int x=equipe1.combattant1.position_x;
    int y=equipe1.combattant1.position_y;
    int portee=equipe1.combattant1.deplacement;
    carte[x][y]='.'; //On remet la case d'origine à vide
    deplacement(&x,&y,portee,carte);//On déplace le combattant
    equipe1.combattant1.position_x=x;
    equipe1.combattant1.position_y=y;

    carte[equipe1.combattant1.position_x][equipe1.combattant1.position_y]='1'; //On met à jour la carte avec la nouvelle position du combattant



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
