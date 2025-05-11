#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "map.h"
#include "combat.h"
#include "utilitaire.h"

void carre_portee(int *x_min, int *x_max,int *y_min, int *y_max, int portee){
    *x_max+=portee;
    *x_min-=portee;
    *y_max+=portee;
    *y_min-=portee;

    if(*x_min<0){
        *x_min=0;
    }
    if(*x_max>=CARTE_TAILLE){
        *x_max=CARTE_TAILLE-1;
    }
    if(*y_min<0){
        *y_min=0;
    }
    if(*y_max>=CARTE_TAILLE){
        *y_max=CARTE_TAILLE-1;
    }
}

// Fonction qui verifie quels combattant (allies ou ennemis) sont dans la portee de l'attaquant et qui les ajoute dans deux tableau respectif
void verif_combattant_portee(char **carte,int x, int y, int portee, int num_equipe, Combattant* cible, int* cible_atteignable,Combattant *allie, int *allie_atteignable){
// Initialisation du carre de recherche dependant de la portee
    int x_min=x;
    int x_max=x;
    int y_min=y;
    int y_max=y;
    carre_portee(&x_min,&x_max,&y_min,&y_max,portee);

    // recherche des combattants dans le carre
    for(int i=x_min;i<=x_max;i++){
        for(int j=y_min;j<=y_max;j++){

            if(carte[i][j] != '.' && carte[i][j] != 'X'){
                for(int k=0;k<3;k++){
                    if(carte[i][j] == cible[k].premierelettre && cible[k].equipe != num_equipe){
                        cible_atteignable[k]=1;
                    }
                }                   
                for(int k=0;k<3;k++){
                    if(carte[i][j] == allie[k].premierelettre && allie[k].equipe == num_equipe){
                         allie_atteignable[k]=1;
                    }
                }                   
            }

        }
    }
}

// Fonction attaque, modifie directement la victime (pointeur)
int  attaque_base_degat(Combattant agresseur, Combattant* victime){
    int reussite = rand() % 100;
    if (reussite < victime->agilite) {
        printf("Attaque ratée !\n");
        return 1;
    }

    float degatsAgresseur= agresseur.attaque;
    float reductionDegatsVictime = degatsAgresseur*((victime->defense)/100);
    float degatreduit = degatsAgresseur-reductionDegatsVictime;


    if(degatreduit < 0){
        degatreduit = 0;
    }
    victime->pvCourant -= degatreduit;

    if(victime->pvCourant <= 0){
        victime->vivant = 0;
        victime->pvCourant = 0;
        printf("%s a été tué !\n", victime->nom);
        return 0;
    }
    printf("%s a subi %.2f de degats !\n", victime->nom, degatreduit);
    printf("%s a %.2f PV restants !\n", victime->nom, victime->pvCourant);
    return 1;
    // Les return 1 et 0 donnent l'info de vie ou de mort de la victime
}

void attaque_base(Combattant agresseur, Combattant* ennemi, Combattant* allie,char **carte){
    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = agresseur.position_x;
    int y = agresseur.position_y;
    int portee = agresseur.portee;
    int num_equipe = agresseur.equipe;
    int choix;
    verif_combattant_portee(carte, x, y, portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
    int ennemi_vivant=0;
    for(int i=0;i<3;i++){
        if(cible_atteignable[i]){
            ennemi_vivant++;
        }
    }
    if(!ennemi_vivant){
        printf("Aucun ennemi n'est dans votre portee !\n");
        return;
    }

    do{
        printf("Choisissez votre cible :\n");
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
            }
        }
        scan_int(&choix);
    }while(choix < 1 || choix > 3 || cible_atteignable[choix-1] == 0);

    int vivant=attaque_base_degat(agresseur, &ennemi[choix-1]);
    if(!vivant){
        carte[ennemi[choix-1].position_x][ennemi[choix-1].position_y] = '.';
        ennemi[choix-1].vivant = 0;
    }
}
