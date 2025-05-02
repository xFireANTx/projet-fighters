

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

#define TEAM_SIZE 3

typedef struct {
    char nom[10];
    int valeur;
    char description[10];
    int nbTourActifs;
    int nbTourRechargement;
} Competence;

void vider_tampon()
{
    char c;
    while (c = getchar() != '\n' && c!=EOF); // Vide le tampon d'entrée
  // on vérifie EOF car dans certain cas particulier getchar() renvoie EOF ce qui peut créer une boucle infinie car EOF marque la fin du flux entrant
}

void scan_int(int *valeur)
{
    int resultat = 0;
    do{
        resultat = scanf("%d", valeur);
        if (resultat != 1) 
        {
            printf("Valeur entree incorrect, reessayez:\n");
            vider_tampon();
        
        }
        else
        {
            char c = getchar();
            if (c != '\n') 
            {
                printf("Trop de valeur entree, reessayez.\n");
                vider_tampon();
                resultat = 0; // Réinitialiser result pour continuer la boucle
            }
        }
    }while(resultat != 1);
}


typedef struct {
    float pvCourant;
    float pvMax;
    float attaque;
    float defense;
    float agilite;
    float vitesse;
    int deplacement;
    Competence competences[5];
    int effetActif;
} Combattant;

void triParSelection(int *tableau, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int indiceMin = i; // on suppose que le premier element est le plus petit
        for (int j = i + 1; j < taille; j++) {
            if (tableau[j] < tableau[indiceMin]) {
                indiceMin = j; // trouver l indice du plus petit element
            }
        }
        // echanger les valeurs
        int temp = tableau[i];
        tableau[i] = tableau[indiceMin];
        tableau[indiceMin] = temp;
    }
}


void tours(Combattant *equipe1,Combattant *equipe2){
    int ordre_cmb[2*TEAM_SIZE];
    for(int i = 0 ; i < TEAM_SIZE ; i ++){
        ordre_cmb[i] = equipe1[i].deplacement;
        ordre_cmb[i+TEAM_SIZE] = equipe2[i].deplacement;
    }
    for(int i = 0 ; i < TEAM_SIZE*2 ; i ++){
        printf("%d ",ordre_cmb[i]);
    }
    printf("\n");
    triParSelection(ordre_cmb,TEAM_SIZE*2);
    for(int i = 0 ; i < TEAM_SIZE*2 ; i ++){
        printf("%d ",ordre_cmb[i]);
    }
    printf("\n");
}



int main(){
    Combattant equipe1[TEAM_SIZE];
    Combattant equipe2[TEAM_SIZE];
    for(int i =0; i<TEAM_SIZE; i++){
        scan_int(&equipe1[i].deplacement);
    }
    for(int i =0; i<TEAM_SIZE; i++){
        scan_int(&equipe2[i].deplacement);
    }    
    tours(equipe1,equipe2);
}
//tour deplacement puis att puis prochain champion