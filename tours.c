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
/*
int main(){  //a modifier
    char carte;
    generation_carte(20,carte);
    Combattant equipe1 [3];
    Combattant equipe2 [3];
    tours(equipe1, equipe2, carte);
}*/

void triABulles(Combattant tableau[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (tableau[j].vitesse > tableau[j + 1].vitesse) {
                // Échanger les éléments
                int temp = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = temp;
            }
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
// Affiche les stats d’un combattant
void afficherStats(Combattant combattants[], int nbCombattants){
    printf("combattant 1 : %f pv\n", combattants[0].pvCourant);
    printf("combattant 2 : %f pv\n", combattants[1].pvCourant);
    /*
    for (int i=1; i <= nbCombattants; i++) {
        printf("pvCourant du combattant %d : %f pv\n", i, combattants[i-1].pvCourant);
    }*/
}
                }
            }
        }
    }
}


void definirOrdreAttaque(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants) {
    tabComcattants[0]=equipe1.combattant1;
    tabComcattants[1]=equipe1.combattant2;
    tabComcattants[2]=equipe1.combattant3;
    tabComcattants[3]=equipe2.combattant1;
    tabComcattants[4]=equipe2.combattant2;
    tabComcattants[5]=equipe2.combattant3;
    triABulles(tabCombattants,6);
}

int verif_equipe_vivant(int tab[],Equipe equipe1, Equipe equipe2)
{
    if(!tab[0] && !tab[1] && !tab[2])
    {
        printf("L'Equipe 1 est morte, Vainqueur:\n);
        affiche_equipe(equipe1);
        return 1;
    }
    else if(!tab[3] && !tab[4] && !tab[5])
    {
        printf("L'Equipe 2 est morte, Vainqueur:\n);
        affiche_equipe(equipe2);
        return 1;
    }
    return 0;
}

int tours() {
    do{

    }while(!verif_equipe_vivant);
    return 1;
}



