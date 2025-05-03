#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

/*
perso + rapide deplacement puis att
trier perso +rapide
*/

int main(){  //a modifier
    char carte;
    generation_carte(20,carte);
    Combattant equipe1 [3];
    Combattant equipe2 [3];
    tours(equipe1, equipe2, carte);
}

void triABulles(Combattant tableau[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tableau[j].vitesse > tableau[j + 1].vitesse) {
                // Échanger les éléments
                int temp = tableau[j].vitesse;
                tableau[j].vitesse = tableau[j + 1].vitesse;
                tableau[j + 1].vitesse = temp;
            }
        }
    }
}

void tours(Combattant *equipe1, Combattant *equipe2, char **carte){
    Combattant** perso;
    perso = malloc(sizeof(Combattant)*6);
    for(int t=0; t<3; t++){
        perso[t] = &equipe1[t];
    }
    for(int t=3; t<6; t++){
        perso[t] = &equipe2[t-3];
    }
    int victime;
    triABulles(perso, 6);       //tri perso par vitesse
    for(int i = 0; i<6; i++){
        deplacement(perso[i], carte);
        victime = verifATT(perso, i);
        combattre(*perso[i], perso[victime]);            //comprend pas
    }
}



int verifATT(Combattant* perso, int i){
    int x,y =0;
    int t=0;
    while(t==0){
        printf("entrez la coordonée x de l adversaire \n");
        scan_int(x);
        printf("entrez la coordonée y de l adversaire \n");
        scan_int(y);
        for(int j = 0; i<6; i++){
            if(x == perso[j].position_x && y == perso[j].position_y){
                if(perso[i].equipe != perso[j].equipe){
                    return j;
                }
            }
        }
    }
}


