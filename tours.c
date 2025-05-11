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
void afficherStats(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants) {
    printf("Stats de l'equipe 1 :\n");
    printf("Nom : %s\n", equipe1.nom);
    printf("Combattant 1 : %s\n", equipe1.combattant1.nom);
    printf("PV : %.2f / %.2f\n", equipe1.combattant1.pvCourant, equipe1.combattant1.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe1.combattant1.attaque, equipe1.combattant1.defense, 
           equipe1.combattant1.agilite, equipe1.combattant1.effetActif,
           equipe1.combattant1.vivant ? "Vivant" : "Mort");

    printf("Combattant 2 : %s\n", equipe1.combattant2.nom);
    printf("PV : %.2f / %.2f\n", equipe1.combattant2.pvCourant, equipe1.combattant2.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe1.combattant2.attaque, equipe1.combattant2.defense, 
           equipe1.combattant2.agilite, equipe1.combattant2.effetActif,
           equipe1.combattant2.vivant ? "Vivant" : "Mort");

    printf("Combattant 3 : %s\n", equipe1.combattant3.nom);
    printf("PV : %.2f / %.2f\n", equipe1.combattant3.pvCourant, equipe1.combattant3.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe1.combattant3.attaque, equipe1.combattant3.defense, 
           equipe1.combattant3.agilite, equipe1.combattant3.effetActif,
           equipe1.combattant3.vivant ? "Vivant" : "Mort");

    printf("\nStats de l'equipe 2 :\n");
    printf("Nom : %s\n", equipe2.nom);
    printf("Combattant 1 : %s\n", equipe2.combattant1.nom);
    printf("PV : %.2f / %.2f\n", equipe2.combattant1.pvCourant, equipe2.combattant1.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe2.combattant1.attaque, equipe2.combattant1.defense, 
           equipe2.combattant1.agilite, equipe2.combattant1.effetActif,
           equipe2.combattant1.vivant ? "Vivant" : "Mort");

    printf("Combattant 2 : %s\n", equipe2.combattant2.nom);
    printf("PV : %.2f / %.2f\n", equipe2.combattant2.pvCourant, equipe2.combattant2.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe2.combattant2.attaque, equipe2.combattant2.defense, 
           equipe2.combattant2.agilite, equipe2.combattant2.effetActif,
           equipe2.combattant2.vivant ? "Vivant" : "Mort");

    printf("Combattant 3 : %s\n", equipe2.combattant3.nom);
    printf("PV : %.2f / %.2f\n", equipe2.combattant3.pvCourant, equipe2.combattant3.pvMax);
    printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Effet : %d, Etat : %s\n", 
           equipe2.combattant3.attaque, equipe2.combattant3.defense, 
           equipe2.combattant3.agilite, equipe2.combattant3.effetActif,
           equipe2.combattant3.vivant ? "Vivant" : "Mort");

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
        return 2;
    }
    else if(equipe2.combattant1.vivant == 0 && equipe2.combattant2.vivant == 0 && equipe2.combattant3.vivant == 0){
        printf("L'equipe 1 a gagne !\nEquipe vainqueur :\n");
        affiche_equipe(equipe1);
        return 1;
    }
    return 0;
}

int choix_attaque(){
    int choix;
    do{
        printf("Que voulez-vous faire ?\n1 : Attaquer\n2 : Attaque Special\n3: Verifier les stats\n4: Rien(passe un tour)\n");
        scan_int(&choix);
        if(choix <1 || choix > 4){
            printf("Erreur, veuillez choisir une action entre 1 et 3.\n\n");
        }
    }while(choix <1 || choix > 4);
    return choix;
}

int tours(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants, char **carte) { 
    
    int c=0;
    Combattant tab_equipe1[3] ;
    Combattant tab_equipe2[3] ;
    int indice_1=0;
    int indice_2=0;
    for(int i=0;i<6;i++)
    {
        if(tabCombattants[i].equipe == 1){
            tab_equipe1[indice_1] = tabCombattants[i];
            indice_1++;
        }
        else{
            tab_equipe2[indice_2] = tabCombattants[i];
            indice_2++;
        }
    }
    do{
        for(int i=0;i<6;i++)
        {
            int choix;
            int num_equipe = tabCombattants[i].equipe;
            char lettre = tabCombattants[i].premierelettre;
            if(tabCombattants[i].vivant){
                printf("Au tour de %s de l'equipe %d\n",tabCombattants[i].nom,num_equipe);
                printf("Utilisez les touches z,s,q,d (minuscules) pour vous deplacer et la touche a pour mettre fin a vos deplacements\n");
                affiche_tableau(carte,CARTE_TAILLE);
                printf("Vous avez %d deplacements\n",tabCombattants[i].deplacement);
                deplacement_bis(&tabCombattants[i].position_x,&tabCombattants[i].position_y,tabCombattants[i].deplacement,carte,lettre);
                
                do{ 
                    choix = choix_attaque();
                    if(choix==1){
                        attaque_base(tabCombattants[i],tab_equipe1,tab_equipe2,carte);
                    }
                    else if(choix==2){

                    }
                    else if(choix==3){
                        afficherStats(equipe1,equipe2,tabCombattants);
                    }
                    else if(choix==4){
                        printf("Vous avez choisi de ne rien faire (?)\n");
                    }

                }while(choix==3);

                
            }
            c=est_vivant(equipe1,equipe2);
            if(c!=0){
                break;
            }
        }
        
    }while(!c);
    return 1;
}



