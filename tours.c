#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "combat.h"
#include "utilitaire.h"
#include "tours.h"


void triABullesOptimise(Combattant tableau[], int taille) {
    int i, j;
    Combattant temp;
    int echange;
    for (i = 0; i < taille - 1; i++) {
        echange = 0;
        for (j = 0; j < taille - i - 1; j++) {
            if (tableau[j].vitesse < tableau[j + 1].vitesse) {
                temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;
                echange = 1;
            }
        }
        if (echange == 0) {
            break; // Si aucun échange n'a eu lieu, le tableau est déjà trié
        }
    }
}

int verifATT(Combattant* perso, int i){
    int x,y =0;
    int t=0;
    while(t==0){
        printf("entrez la coordonée x de l adversaire \n");
        scan_int(&x);
        printf("entrez la coordonée y de l adversaire \n");
        scan_int(&y);
        for(int j = 0; i<6; i++){
            if(x == perso[j].position_x && y == perso[j].position_y){
                if(perso[i].equipe != perso[j].equipe){
                    return j;
                }
            }
        }
    }
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


void definirOrdreAttaque(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants) {
    tabCombattants[0]=equipe1.combattant1;
    tabCombattants[1]=equipe1.combattant2;
    tabCombattants[2]=equipe1.combattant3;
    tabCombattants[3]=equipe2.combattant1;
    tabCombattants[4]=equipe2.combattant2;
    tabCombattants[5]=equipe2.combattant3;
    triABullesOptimise(tabCombattants,6);
}

int est_vivant(Equipe equipe1, Equipe equipe2){
    if(equipe1.combattant1.vivant == 0 && equipe1.combattant2.vivant == 0 && equipe1.combattant3.vivant == 0){
        printf("L'equipe 2 a gagne !\nEquipe vainqueur :\n");
        affiche_equipe(equipe2);
        return 1;
    }
    else if(equipe2.combattant1.vivant == 0 && equipe2.combattant2.vivant == 0 && equipe2.combattant3.vivant == 0){
        printf("L'equipe 1 a gagne !\nEquipe vainqueur :\n");
        affiche_equipe(equipe1);
        return 1;
    }
    return 0;
}

int choix_attaque_deplacement(){
    int choix;
    do{
        printf("Que voulez-vous faire ?\n1 : Attaquer\n2 : Deplacer\n3: Vérifier les stats\n");
        scan_int(&choix);
        if(choix <1 || choix > 3){
            printf("Erreur, veuillez choisir une action entre 1 et 3.\n\n");
        }
    }while(choix <1 || choix > 3);
    return choix;
}

int tours(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants, char **carte) { 
    
    int c=0;
    do{
        for(int i=0;i<6;i++)
        {
            int choix;
            int equipe = tabCombattants[i].equipe;
            char lettre = tabCombattants[i].premierelettre;
            if(tabCombattants[i].vivant){
                printf("Au tour de %s de l'equipe %d\n",tabCombattants[i].nom,equipe);
                choix=choix_attaque_deplacement();
                if(choix == 2){
                    /*int x=tabCombattants[i].position_x;
                    int y=tabCombattants[i].position_y;
                    int portee=tabCombattants[i].deplacement;
                    carte[x][y]='.';
                    deplacement(&x,&y,portee,carte);//On déplace le combattant
                    tabCombattants[i].position_x=x;
                    tabCombattants[i].position_y=y;
                    carte[tabCombattants[i].position_x][tabCombattants[i].position_y]=lettre; //On met à jour la carte avec la nouvelle position du combattant
                    affiche_tableau(carte,CARTE_TAILLE);*/
                }
                
            }
            c=est_vivant(equipe1,equipe2);
            if(c){
                break;
            }
        }
        
    }while(!c);
    return 1;
}



