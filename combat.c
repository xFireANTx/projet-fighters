#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "combat.h"
#include "utilitaire.h"


int verif_portee(Combattant agresseur, Combattant victime){
    int portee = agresseur.portee;
    int xAgresseur = agresseur.position_x;
    int yAgresseur = agresseur.position_y;
    int xVictime = victime.position_x;
    int yVictime = victime.position_y;
return 0;
}

// Fonction attaque, modifie directement la victime (pointeur)
int attaquer(Combattant agresseur, Combattant* victime){
    if(verif_portee(agresseur, *victime)){
        if (nbAleatoire(20 - victime->agilite) != 1) {

            float degatsAgresseur = agresseur.attaque / 100.0;
            float reductionDegatsVictime = 1 - victime->defense / 100.0;
            float reduction = 1 - degatsAgresseur * reductionDegatsVictime;
            victime->pvCourant *= reduction;
            return 1;
        }
    return 0;
}
}

// Fonction pour effectuer un combat entre deux combattants
void combattre(Combattant combattant1, Combattant* combattant2){
    int reussite = attaquer(combattant1, combattant2);
    if (reussite == 1) {
        printf("Touché !\n");
    } else {
        printf("Raté !\n");
    }
}
