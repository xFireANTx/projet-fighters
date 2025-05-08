///TODO : ajouter le système de compétence

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

Combattant creerCombattant(int perso) {
    Combattant c;
    FILE * fichier = fopen("personnage.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier personnage\n");
        exit(1);
    }
    char poubelle[100];
    fgets(poubelle, sizeof(poubelle), fichier); // On lit la première ligne pour l'ignorer
    for (int i = 1; i < perso; i++) {
        fgets(poubelle, sizeof(poubelle), fichier); // On lit les lignes jusqu'à la ligne du personnage choisi
    }
    fgets(c.nom, 12, fichier); // On lit le nom du personnage (11 caractères avec les espaces avant la premiere stat)
    fscanf(fichier, "%f %f %f %f %f %f %d", &c.pvMax, &c.pvCourant, &c.attaque, &c.defense, &c.agilite, &c.vitesse, &c.deplacement);
    c.effetActif = 0; // On initialise l'effet actif à 0
    fclose(fichier); // On ferme le fichier
    return c;
}



EQUIPE creerEquipe(int num_equipe) {
    EQUIPE equipe;
    equipe.equipe = num_equipe;
    printf("Entrez le nom de l'equipe %d : ", num_equipe);
    scanf("%10s", equipe.nom); // A RENFORCER
    vider_tampon();

    
    int choix ;
    int deja_pris[6] = {0, 0, 0, 0, 0, 0};
    do{
        printf("Choississer un premier personnage:\n1 : Mage\n2 : Tank\n3 : Archer\n4 : Assassin\n5 : Guerrier\n6 : Soigneur\n");
        scan_int(&choix);
        if(choix <1 || choix > 6){
            printf("Erreur, veuillez choisir un personnage entre 1 et 6.\n\n");
        }
        else{
            deja_pris[choix-1] = 1;
            equipe.combattant1 = creerCombattant(choix);
        }
    }while (choix <1 || choix > 6);
     

    bool a=false;
    do{
        printf("Choississer un deuxieme personnage:\n1 : Mage\n2 : Tank\n3 : Archer\n4 : Assassin\n5 : Guerrier\n6 : Soigneur\n");
        scan_int(&choix);
        if(choix <1 || choix > 6){
            printf("Erreur, veuillez choisir un personnage entre 1 et 6.\n\n");
        }
        else if (deja_pris[choix-1] == 1) {
            printf("Ce personnage a deja ete choisi, choisissez un autre personnage.\n\n");
        } else {
            deja_pris[choix-1] = 1;
            equipe.combattant2 = creerCombattant(choix);
            a=true;
        }
    } while (!a || choix <1 || choix > 6);
    a=false;
    do{
        printf("Choississer un dernier personnage:\n1 : Mage\n2 : Tank\n3 : Archer\n4 : Assassin\n5 : Guerrier\n6 : Soigneur\n");
        scan_int(&choix);
        if(choix <1 || choix > 6){
            printf("Erreur, veuillez choisir un personnage entre 1 et 6.\n\n");
        }
        else if (deja_pris[choix-1] == 1) {
            printf("Ce personnage a deja ete choisi, choisissez un autre personnage.\n\n");
        } else {
            deja_pris[choix-1] = 1;
            equipe.combattant3 = creerCombattant(choix);
            a=true;
        }
    } while (!a || choix <1 || choix > 6);

    // Initialisation des positions des combattants selon l'equipe
    if(num_equipe ==1){
        equipe.combattant1.position_x = 0;
        equipe.combattant1.position_y = 7;
        equipe.combattant2.position_x = 0;
        equipe.combattant2.position_y = 9;
        equipe.combattant3.position_x = 0;
        equipe.combattant3.position_y = 11;
    }
    else if(num_equipe ==2){
        equipe.combattant1.position_x = 19;
        equipe.combattant1.position_y = 7;
        equipe.combattant2.position_x = 19;
        equipe.combattant2.position_y = 9;
        equipe.combattant3.position_x = 19;
        equipe.combattant3.position_y = 11;
    }
    
    return equipe;
}

void affiche_equipe(EQUIPE equipe) {
    printf("Equipe %d : %s\n", equipe.equipe, equipe.nom);
    printf("Combattant 1 : %s\n", equipe.combattant1.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant1.pvCourant, equipe.combattant1.pvMax);
    printf("Combattant 2 : %s\n", equipe.combattant2.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant2.pvCourant, equipe.combattant2.pvMax);
    printf("Combattant 3 : %s\n", equipe.combattant3.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant3.pvCourant, equipe.combattant3.pvMax);
    printf("\n");
}
