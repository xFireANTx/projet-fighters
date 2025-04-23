#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nom[10];
    int valeur;
    char description[10];
    int nbTourActifs;
    int nbTourRechargement;
} Competence;

typedef struct {
    float pvCourant;
    float pvMax;
    float attaque;
    float defense;
    float agilite;
    float vitesse;
    Competence competences[5];
    int effetActif;
} Combattant;

// Renvoie un nombre aléatoire entre 0 et max - 1
int nombreAleatoire(int max) {
    if (max <= 0) return 0;
    return rand() % max;
}

// Fonction pour créée un combattant
Combattant creerCombattant(float pvCourant, float pvMax, float attaque, float defense, float agilite, float vitesse) {
    Combattant combattant;
    combattant.pvCourant = pvCourant;
    combattant.pvMax = pvMax;
    combattant.attaque = attaque;
    combattant.defense = defense;
    combattant.agilite = agilite;
    combattant.vitesse = vitesse;
    combattant.effetActif = 0;
    return combattant;
}

// Affiche les stats d’un combattant
void afficherStats(Combattant combattants[], int nbCombattants) {
    printf("combattant 1 : %f pv\n", combattants[0].pvCourant);
    printf("combattant 2 : %f pv\n", combattants[1].pvCourant);
    /*
    for (int i=1; i <= nbCombattants; i++) {
        printf("pvCourant du combattant %d : %f pv\n", i, combattants[i-1].pvCourant);
    }*/
}


// Fonction attaque, modifie directement la victime (pointeur)
int attaquer(Combattant agresseur, Combattant* victime) {
    if (nombreAleatoire(20 - victime->agilite) != 1) {
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

int main() {
    srand(time(NULL));


    Combattant chevalier1 = creerCombattant(500, 500, 20, 50, 5, 1);
    Combattant chevalier2 = creerCombattant(500, 500, 20, 50, 5, 1);
    Combattant combattants[2] = {chevalier1, chevalier2};

    while(chevalier1.pvCourant > 0.0001 && chevalier2.pvCourant > 0.0001) {
        combattre(chevalier1, &chevalier2);

        printf("\n--- Stats après attaque ---\n");
        afficherStats(combattants, 2);

    }



    return 0;
}
