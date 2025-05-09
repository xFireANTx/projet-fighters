
// créer une boucle pour le déplacement de chaque combattant

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

int main()
{

    char **carte = malloc(CARTE_TAILLE*sizeof(char*));
    int n_map=choix_map();
    generation_carte(n_map,carte);
    affiche_tableau(carte,CARTE_TAILLE);
    Equipe equipe1= creerEquipe(1);
    Equipe equipe2= creerEquipe(2);
    affiche_equipe(equipe1);
    affiche_equipe(equipe2);
    printf("\n");
    Combattant tableau[6];
    int vivant[6]={1,1,1,1,1,1};
	
    definirOrdreAttaque(equipe1,equipe2,tableau);
    /*for(int k=0;k<6;k++)
    {
	printf("%s",tableau[k].nom);
    }*/

   
    /*int x=equipe1.combattant1.position_x;
    int y=equipe1.combattant1.position_y;
    int portee=equipe1.combattant1.deplacement;
    carte[x][y]='.'; //On remet la case d'origine à vide
    deplacement(&x,&y,portee,carte);//On déplace le combattant
    equipe1.combattant1.position_x=x;
    equipe1.combattant1.position_y=y;

    carte[equipe1.combattant1.position_x][equipe1.combattant1.position_y]='1'; //On met à jour la carte avec la nouvelle position du combattant*/



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
