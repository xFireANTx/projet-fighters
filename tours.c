#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

void afficherCompetence(Combattant *perso){
    printf("Competences de %s :\n", perso->nom);
    for(int i=0;i<3;i++){
        printf("%d : %s\n",i+1,perso->competences[i].nom);
        printf("Description : %s\n",perso->competences[i].description);
        printf("Portee : %d| Degat/Soin : %d| Nombre de tours actifs : %d | Nombre de tours de rechargement : %d\n",perso->competences[i].portee,perso->competences[i].valeur,perso->competences[i].nbTourActifs,perso->competences[i].nbTourRechargement);
        printf("\n");
    }
}

// Affiche les stats d’un combattant
void afficherStats( Combattant *tabCombattants) {
    printf("Stats de l'equipe 1 :\n");
    for(int k=0;k<6;k++)
    {
        if(tabCombattants[k].equipe == 1){
            printf("Nom : %s\n", tabCombattants[k].nom);
            printf("PV : %.2f / %.2f\n", tabCombattants[k].pvCourant, tabCombattants[k].pvMax);
            printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Portee : %d, Lettre : %c, Effet : %d, Etat : %s\n", 
                   tabCombattants[k].attaque, tabCombattants[k].defense, 
                   tabCombattants[k].agilite, tabCombattants[k].portee, tabCombattants[k].premierelettre,
                   tabCombattants[k].effetActif, tabCombattants[k].vivant ? "Vivant" : "Mort");
        }
    }
    printf("\nStats de l'equipe 2 :\n");
    for(int k=0;k<6;k++)
    {
        if(tabCombattants[k].equipe == 2){
            printf("Nom : %s\n", tabCombattants[k].nom);
            printf("PV : %.2f / %.2f\n", tabCombattants[k].pvCourant, tabCombattants[k].pvMax);
            printf("Attaque : %.2f, Defense : %.2f, Agilite : %.2f, Portee : %d, Lettre : %c, Effet : %d, Etat : %s\n", 
                   tabCombattants[k].attaque, tabCombattants[k].defense, 
                   tabCombattants[k].agilite, tabCombattants[k].portee, tabCombattants[k].premierelettre,
                   tabCombattants[k].effetActif, tabCombattants[k].vivant ? "Vivant" : "Mort");
        }
    }
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
            printf("Erreur, veuillez choisir une action entre 1 et 4.\n\n");
        }
    }while(choix <1 || choix > 4);
    return choix;
}

void verifEffet(Combattant* perso){
    if(perso->dureeEffet == 0){
        perso->effetActif == 0;
    }
    else if(perso->effetActif == 1){
        perso->pvCourant -= perso->pvMax* 0.12 ; // brulure
        perso->dureeEffet -= 1;
    }
    else if(perso->effetActif == 2){            // dague poison
        perso->pvCourant -= 50;
        perso->dureeEffet -= 1;
    }
    else if(perso->effetActif == 4)
    {
        perso->dureeEffet -= 1;
    }

}

void cooldown(Combattant* perso)
{
    for(int i=0;i<3;i++){
        perso->competences[i].nbTourRechargement--;
        if(perso->competences[i].nbTourRechargement<=0)
        {
            perso->competences[i].nbTourRechargement = 0;
        }
    }
}

int tours(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants, char **carte){ 
    
    int c=0;
    Combattant tab_equipe1[3] ;
    Combattant tab_equipe2[3] ;
    Combattant tab_equipe1_copie[3] ;
    Combattant tab_equipe2_copie[3] ;

    int indice_1=0;
    int indice_2=0;
    for(int i=0;i<6;i++)
    {
        if(tabCombattants[i].equipe == 1){
            tab_equipe1[indice_1] = tabCombattants[i];
            tab_equipe1_copie[indice_1] = tabCombattants[i];
            indice_1++;
        }
        else{
            tab_equipe2[indice_2] = tabCombattants[i];
            tab_equipe2_copie[indice_2] = tabCombattants[i];
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
                if(tabCombattants[i].effetActif != 3)
                deplacement_bis(&tabCombattants[i].position_x,&tabCombattants[i].position_y,tabCombattants[i].deplacement,carte,lettre);
                
                int retour=0;
                do{ 
                        choix = choix_attaque();
                        if(choix==1){
                            if(tabCombattants[i].equipe == 2){
                                attaque_base(tabCombattants[i],tab_equipe1,tab_equipe2,carte);
                            }
                            else{
                                attaque_base(tabCombattants[i],tab_equipe2,tab_equipe1,carte);
                            }
                            retour =0;
                        }      
                    else if(choix==2){
                      
                        if(tabCombattants[i].equipe == 2)
                        {
                            retour =choix_competence(tabCombattants[i],tab_equipe2,tab_equipe2_copie,tab_equipe1,carte);
                        }
                        else
                        {
                            retour =choix_competence(tabCombattants[i],tab_equipe1,tab_equipe1_copie,tab_equipe2,carte);
                        }
                      
                    }
                    else if(choix==3){
                      
                        afficherStats(equipe1,equipe2,tabCombattants);
                        retour=1;
                    }
                    else if(choix==4){
                        printf("Vous avez choisi de ne rien faire (?)\n");
                        retour =0;
                    }


                }while(retour);
                
            }
            c=est_vivant(equipe1,equipe2);
            if(c!=0){
                break;
            }
            
        }
        for(int i=0;i<6;i++)
        {  
            if(tabCombattants[i].vivant)
            {
                verifEffet(&tabCombattants[i]);
                cooldown(&tabCombattants[i]);
            }
        }
        
        c=est_vivant(equipe1,equipe2);
    }while(!c);
    return 1;
}



