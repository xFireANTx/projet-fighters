#include <stdio.h>
#include <stdlib.h>

#include "combat.h"
#include "utilitaire.h"
#include "map.h"
#include "tours.h"

//void verif_combattant_portee(char **carte,int x, int y, int portee, int num_equipe, Combattant* cible, int* cible_atteignable,Combattant *allie, int *allie_atteignable)
void application_effet(Combattant *victime, Combattant *agresseur,int effet,int num_competence) {
    if(victime->effetActif ==0){
        victime->effetActif = effet;
        victime->dureeEffet = agresseur->competences[num_competence].nbTourActifs;
    }
}

int Mage(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {

    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = joueur->position_x;
    int y = joueur->position_y; 
    int num_equipe = joueur->equipe;

    if(choix == 1) {

        //Verification des cibles atteignables par la competence
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
            ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }

        //Choix de la cible
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);


        //Application des degats
        ennemi[choix_cible-1].pvCourant -= joueur->competences[0].valeur;
        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }

        //Application de l'effet (1: brulure, 2: gel, 3: poison, 4: antisoin)
        application_effet(&ennemi[choix_cible-1], joueur, 1, 0); 

    }

    else if(choix == 2) {
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi_vivant++;           
            }
        }
        int choix_cible;
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;//Signale que l'attaque n'a pas pu être effectuée renvoie au choix d'attaque
        }
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);
        float reduction_def = ennemi[choix_cible-1].defense * 0.4;
        ennemi[choix_cible-1].defense -= reduction_def;
    }


    else if(choix == 3) {
        for(int i=0;i<3;i++){
            if(ennemi[i].vivant && ennemi[i].effetActif != 0){
                ennemi[i].pvCourant -= 200;
                if(ennemi[i].pvCourant <= 0){
                    carte[ennemi[i].position_x][ennemi[i].position_y] = '.';
                    ennemi[i].vivant = 0;
                }
            }
        }
    }
    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
    return 0; // L'action a été effectuée avec succès
}

int Tank(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {
    
    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = joueur->position_x;
    int y = joueur->position_y; 
    int num_equipe = joueur->equipe;
    
    if(choix == 1) {
        float boost=joueur->defense *0.3;
        joueur->defense += boost;
        if(joueur->defense > 60){
            joueur->defense = 60;
        }
    }


    else if(choix == 2) {
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
            ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }

        //Choix de la cible
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);


        //Application des degats
        ennemi[choix_cible-1].pvCourant -= joueur->competences[0].valeur;
        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }

        //Application de l'effet (1: brulure, 2: gel, 3: poison, 4: antisoin)
            application_effet(&ennemi[choix_cible-1], joueur, 4, 0); 
    }


    else if(choix == 3) {
        for(int i=0;i<3;i++){
            if(allie[i].vivant){
                float boost_defense=allie[i].defense *0.3;
                allie[i].defense += boost_defense;
                if(allie[i].defense > 60){
                    allie[i].defense = 60;
                }
            }
        }
    }
    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
    return 0; // L'action a été effectuée avec succès
}

int Archer(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {

    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = joueur->position_x;
    int y = joueur->position_y; 
    int num_equipe = joueur->equipe;

    if(choix == 1) {
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi[i].pvCourant -= joueur->competences[0].valeur;
                if(ennemi[i].pvCourant <= 0){
                    carte[ennemi[i].position_x][ennemi[i].position_y] = '.';
                    ennemi[i].vivant = 0;
                }
            }
        }
    }



    else if(choix == 2) {
       verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }

        //Choix de la cible
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);

        ennemi[choix_cible-1].pvCourant -= joueur->competences[0].valeur;
        
        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }

        //Application de l'effet
        application_effet(&ennemi[choix_cible-1], joueur, 2, 1);

    }


    else if(choix == 3) {
        int choix_cible;
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(ennemi[i].vivant){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || ennemi[choix_cible-1].vivant == 0);

        ennemi[choix_cible-1].pvCourant -= joueur->competences[0].valeur;

        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }
    }
    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
    return 0; // L'action a été effectuée avec succès
}


int Ninja(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {
    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = joueur->position_x;
    int y = joueur->position_y; 
    int num_equipe = joueur->equipe;

    if(choix == 1) {
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }

        //Choix de la cible
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);

        ennemi[choix_cible-1].pvCourant -= joueur->competences[0].valeur;
        
        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }

        //Application de l'effet
        application_effet(&ennemi[choix_cible-1], joueur, 3, 0);

    }
    else if(choix == 2) {
        float boost=joueur->agilite *0.3;
        joueur->agilite += boost;

        if(joueur->agilite > 60){
            joueur->agilite = 60;
        }
    }
    else if(choix == 3) {
        int choix_cible;
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(ennemi[i].vivant){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || ennemi[choix_cible-1].vivant == 0);

        // Echange de position entre le joueur et l'ennemi
        int x_temp = ennemi[choix_cible-1].position_x;
        int y_temp = ennemi[choix_cible-1].position_y;
        carte[x_temp][y_temp] = '.';

        ennemi[choix_cible-1].position_x = joueur->position_x;
        ennemi[choix_cible-1].position_y = joueur->position_y;
        carte[joueur->position_x][joueur->position_y] = ennemi[choix_cible-1].premierelettre;
        
        joueur->position_x = x_temp;
        joueur->position_y = y_temp;
        carte[x_temp][y_temp] = joueur->premierelettre;
        
        //Application des degats
        ennemi[choix_cible-1].pvCourant -= joueur->competences[2].valeur;
        
        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }
    }
    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
    return 0; // L'action a été effectuée avec succès
}

int Guerrier(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {
    
    if(choix == 1) {
        float boost=joueur->attaque *0.2;
        joueur->attaque += boost;
    }


    else if(choix == 2) {   
        for(int i=0;i<3;i++){
            if(allie[i].vivant){
                float boost_attaque=allie[i].attaque *0.15;
                float boost_defense=allie[i].defense *0.15;

                allie[i].defense += boost_defense;
                allie[i].attaque += boost_attaque;
                if(allie[i].defense > 60){
                    allie[i].defense = 60;
                }
            }   
        }
    }

    else if(choix == 3) {
        joueur->effetActif = 0;
        float boost_attaque=joueur->attaque *0.2;
        joueur->attaque += boost_attaque;

        float boost_defense=joueur->defense *0.2;
        joueur->defense += boost_defense;

        float boost_agilite=joueur->agilite *0.2;
        joueur->agilite += boost_agilite;

        if(joueur->defense > 60){
            joueur->defense = 60;
        }
        if(joueur->agilite > 60){
            joueur->agilite = 60;
        }
    }

    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
}

int Soigneur(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix) {
    
    int cible_atteignable[3] = {0,0,0};
    int allie_atteignable[3] = {0,0,0};
    int x = joueur->position_x;
    int y = joueur->position_y; 
    int num_equipe = joueur->equipe;
    
    if(choix == 1) {
        int choix_allie;
        do{
            printf("Choisissez un allie a soigner :\n");
            for(int i=0;i<3;i++){

                if(allie[i].vivant){
                    printf("%d : %s pv:%2f/%2f \n",i+1,allie[i].nom,allie[i].pvCourant,allie[i].pvMax);
                }

            }
            scan_int(&choix_allie);
            if(choix_allie < 1 || choix_allie > 3 || allie[choix_allie-1].vivant == 0){

                printf("Choix invalide. Veuillez choisir un allie valide.\n");
                continue;
            }

            if(allie[choix_allie-1].effetActif !=4){

                allie[choix_allie-1].pvCourant += 200;
            }

            if(allie[choix_allie-1].pvCourant > allie[choix_allie-1].pvMax){

                allie[choix_allie-1].pvCourant = allie[choix_allie-1].pvMax;
            }
        }while(choix_allie < 1 || choix_allie > 3 || allie[choix_allie-1].vivant == 0);
    }


    else if(choix == 2) {
        verif_combattant_portee(carte, x, y, joueur->competences[0].portee, num_equipe, ennemi, cible_atteignable, allie, allie_atteignable);
        int ennemi_vivant=0;
        for(int i=0;i<3;i++){
            if(cible_atteignable[i]){
                ennemi_vivant++;           
            }
        }

        int choix_cible;

        //Verification si il y a des cibles ennemies en vie
        if(!ennemi_vivant){
            printf("Aucun ennemi n'est dans votre portee !\n");
            return 1;
        }

        //Choix de la cible
        do{
            printf("Choisissez votre cible :\n");
            for(int i=0;i<3;i++){
                if(cible_atteignable[i]){
                    printf("%d : %s pv:%2f/%2f \n",i+1,ennemi[i].nom,ennemi[i].pvCourant,ennemi[i].pvMax);
                }
            }
            scan_int(&choix_cible);
        }while(choix_cible < 1 || choix_cible > 3 || cible_atteignable[choix_cible-1] == 0);

        ennemi[choix_cible-1].pvCourant -= 200;

        // 4 Represente le statut antisoin 
        if(joueur->effetActif != 4){
            joueur->pvCourant += 200;
        }
        

        if(ennemi[choix_cible-1].pvCourant <= 0){
            carte[ennemi[choix_cible-1].position_x][ennemi[choix_cible-1].position_y] = '.';
            ennemi[choix_cible-1].vivant = 0;
        }

        if(joueur->pvCourant > joueur->pvMax){
            joueur->pvCourant = joueur->pvMax;
        }
    }


    else if(choix == 3) {
        for(int i=0; i<3; i++)
        {
            if(allie[i].vivant){
                allie[i].pvCourant += 250;
                allie[i].effetActif = 0;
                if(allie[i].pvCourant > allie[i].pvMax){
                    allie[i].pvCourant = allie[i].pvMax;
                }
            }
        }
    }

    joueur->competences[choix-1].nbTourRechargement = joueur_copie.competences[choix-1].nbTourRechargement;
    return 0; // L'action a été effectuée avec succès
}
