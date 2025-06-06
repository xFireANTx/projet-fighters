///TODO : ajouter le système de compétence

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>

#include "map.h"
#include "combat.h"
#include "utilitaire.h"

// Premier ligne de competence dans competence.txt = ligne 3
// Saut de 5 lignes entre chaque competence de personnages
void assignation_competence(Combattant *perso,int num)
{
    Competence tableau_competence[3];
    FILE *competence=NULL;
    competence = fopen("competences.txt", "r");
    if (competence == NULL) {
        printf("Erreur d'ouverture du fichier competences.txt\n");
        exit(1);
    }
    char poubelle[300];

    fgets(poubelle, sizeof(poubelle), competence); 
    fgets(poubelle, sizeof(poubelle), competence); // On lit la premiere et deuxième ligne
    int ligne = (num-1)*5; // Ligne de la competence 1 du perso choisi 
    for(int i=0;i<ligne;i++){
        fgets(poubelle, sizeof(poubelle), competence); // On lit les lignes jusqu'à la ligne du personnage choisi
    }

    
    /*for(int i=0;i<3;i++){
        fgetc(competence); //On lit le numero de la competence
        fscanf(competence, "%s %d %s %d %d %d",perso->competences[i].nom,&perso->competences[i].valeur,perso->competences[i].description,&perso->competences[i].nbTourActifs,&perso->competences[i].nbTourRechargement,&perso->competences[i].portee);
        fgetc(competence); // On lit le retour à la ligne
    }*/
    for (int i = 0; i < 3; i++) {
        for(int j=0;j<5;j++){
            fgetc(competence);
        }
         // On lit le numéro de la compétence
        fscanf(competence, "%s %d ",perso->competences[i].nom,&perso->competences[i].valeur);
        char a;
        a=fgetc(competence);
        while(a==' ')
        {
            a=fgetc(competence); // On lit les espaces
        }
        fgets(perso->competences[i].description, sizeof(perso->competences[i].description), competence); // On lit la description
        fscanf(competence, "%d %d %d", &perso->competences[i].nbTourActifs, &perso->competences[i].nbTourRechargement, &perso->competences[i].portee);
    }
    fclose(competence); 
}

Combattant creerCombattant(int perso,int num_equipe) {
    Combattant c;

    FILE * fichier = fopen("personnage.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier personnage\n");
        exit(1);
    }

    char poubelle[100];
    fgets(poubelle, sizeof(poubelle), fichier); // On lit la première ligne pour l'ignorer car elle contient le nom des colonnes
    for (int i = 1; i < perso; i++) {
        fgets(poubelle, sizeof(poubelle), fichier); // On lit les lignes jusqu'à la ligne du personnage choisi
    }

    // Récupération des données du personnage depuis le fichier personnage.txt
    fscanf(fichier, "%11s %f %f %f %f %f %f %d %d",c.nom, &c.pvMax, &c.pvCourant, &c.attaque, &c.defense, &c.agilite, &c.vitesse, &c.deplacement, &c.portee);
    c.premierelettre = c.nom[0];
    if(num_equipe == 2){
        c.premierelettre = tolower(c.premierelettre);
    }

    c.effetActif = 0; // On initialise l'effet actif à 0(pas d'effet)
    c.dureeEffet = 0; 
    c.vivant = 1;
    c.equipe = num_equipe; 
    assignation_competence(&c,perso); // On assigne les compétences du personnage

    fclose(fichier); // On ferme le fichier
    return c;
}

Combattant choix_perso(int num_equipe,int deja_pris[]) {
    bool a=false;
    Combattant combattant;
    int choix ;
    do{
        printf("Choississer un personnage:\n1 : Mage\n2 : Tank\n3 : Archer\n4 : Ninja\n5 : Guerrier\n6 : Soigneur\n");
        scan_int(&choix);
        if(choix <1 || choix > 6){
            printf("Erreur, veuillez choisir un personnage entre 1 et 6.\n\n");
        }
        else if (deja_pris[choix-1] == 1) {
            printf("Ce personnage a deja ete choisi, choisissez un autre personnage.\n\n");
        } else {
            deja_pris[choix-1] = 1;
            combattant = creerCombattant(choix,num_equipe);
            a=true;
        }
    } while (!a || choix <1 || choix > 6);
    return combattant;
}

Equipe creerEquipe(int num_equipe, char **carte) {
    Equipe equipe;
    equipe.equipe = num_equipe;
    printf("Entrez le nom de l'equipe %d : ", num_equipe);
    scanf("%10[^\n]", equipe.nom); // Sert à lire une ligne de texte de 10 caractere jusqu'à un retour à la ligne
    vider_tampon();

    
    int choix ;
    int deja_pris[6] = {0, 0, 0, 0, 0, 0};
    // C'est le même code trois fois on se sert du tableau au dessus pour être sûr qu'un perso ne soit pas pris deux fois dans la même équipe
    equipe.combattant1 = choix_perso(num_equipe,deja_pris);
    equipe.combattant2 = choix_perso(num_equipe,deja_pris);
    equipe.combattant3 = choix_perso(num_equipe,deja_pris);

    // Initialisation des positions des combattants selon l'equipe
    if(num_equipe ==1){
        equipe.combattant1.position_x = 0;
        equipe.combattant1.position_y = 7;
        carte[equipe.combattant1.position_x][equipe.combattant1.position_y] = equipe.combattant1.premierelettre;
        equipe.combattant2.position_x = 0;
        equipe.combattant2.position_y = 9;
        carte[equipe.combattant2.position_x][equipe.combattant2.position_y] = equipe.combattant2.premierelettre;
        equipe.combattant3.position_x = 0;
        equipe.combattant3.position_y = 11;
        carte[equipe.combattant3.position_x][equipe.combattant3.position_y] = equipe.combattant3.premierelettre;
    }
    else if(num_equipe ==2){
        equipe.combattant1.position_x = 19;
        equipe.combattant1.position_y = 7;
        carte[equipe.combattant1.position_x][equipe.combattant1.position_y] = equipe.combattant1.premierelettre;
        equipe.combattant2.position_x = 19;
        equipe.combattant2.position_y = 9;
        carte[equipe.combattant2.position_x][equipe.combattant2.position_y] = equipe.combattant2.premierelettre;
        equipe.combattant3.position_x = 19;
        equipe.combattant3.position_y = 11;
        carte[equipe.combattant3.position_x][equipe.combattant3.position_y] = equipe.combattant3.premierelettre;
    }
    
    return equipe;
}

void affiche_equipe(Equipe equipe) {
    printf("Equipe %d : %s\n", equipe.equipe, equipe.nom);
    printf("Combattant 1 : %s\n", equipe.combattant1.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant1.pvCourant, equipe.combattant1.pvMax);
    printf("Combattant 2 : %s\n", equipe.combattant2.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant2.pvCourant, equipe.combattant2.pvMax);
    printf("Combattant 3 : %s\n", equipe.combattant3.nom);
    printf("PV : %.2f / %.2f\n", equipe.combattant3.pvCourant, equipe.combattant3.pvMax);
    printf("\n");
}
