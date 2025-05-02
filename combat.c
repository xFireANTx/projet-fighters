#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

// Fonction pour créée un combattant
Combattant creerCombattant(int equipe, float pvCourant, float pvMax, float attaque, float defense, float agilite, float vitesse,int deplacement,int x,int y) {
    Combattant c;
    c.pvCourant = pvCourant;
    c.pvMax = pvMax;
    c.attaque = attaque;
    c.defense = defense;
    c.agilite = agilite;
    c.vitesse = vitesse;
    c.effetActif = 0;
    c.deplacement = deplacement;
    c.position_x = x;
    c.position_y = y;
    return c;
}

// Affiche les stats d’un combattant
void afficherStats(Combattant combattants[], int nbCombattants){
    printf("combattant 1 : %f pv\n", combattants[0].pvCourant);
    printf("combattant 2 : %f pv\n", combattants[1].pvCourant);
    /*
    for (int i=1; i <= nbCombattants; i++) {
        printf("pvCourant du combattant %d : %f pv\n", i, combattants[i-1].pvCourant);
    }*/
}


// Fonction attaque, modifie directement la victime (pointeur)
int attaquer(Combattant agresseur, Combattant* victime) {

    if (nbAleatoire(20 - victime->agilite) != 1) {

        float degatsAgresseur = agresseur.attaque / 100.0;
        float reductionDegatsVictime = 1 - victime->defense / 100.0;
        float reduction = 1 - degatsAgresseur * reductionDegatsVictime;
        victime->pvCourant *= reduction;
        return 1;
    }
    return 0;
}

// Fonction pour effectuer un combat entre deux combattants
void combattre(Combattant combattant1, Combattant* combattant2) {
    int reussite = attaquer(combattant1, combattant2);
    if (reussite == 1) {
        printf("Touché !\n");
    } else {
        printf("Raté !\n");
    }
}