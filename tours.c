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

int verif_coord(int* x, int* y,int xMax, int yMax, int xMin, int yMin) { 
    // x et y sont les coordonnees du joueur    
    printf("Entrez x entre %d et %d : ", xMin, xMax);
    scan_int(x);//Regarder le fichier utilitaire pour voir comment fonctionne scan_int
    if (*x < xMin || *x> xMax) {                     //On regarde si les coordonees sont dans l intervalle de deplacement
        printf("x=%d n'est pas accessible.\n",*x);
        return 0;
    }

    printf("Entrez y entre %d et %d : ", yMin, yMax);
    scan_int(y);//fichier utilitaire
    if (*y < yMin || *y > yMax) {
        printf("y=%d n'est pas accessible.\n",*y);
        return 0;
    }

    printf("Pas de probleme.\n");
    printf("Nouvelle position : x = %d, y = %d\n", *x, *y);
    return 1;
}
void deplacement(Combattant *perso,char **map){   
    int x,y,portee;
    x = perso->position_x;
    y = perso->position_y;
    portee = perso->deplacement;

    //cases disponible pour mouvement
    int xMin = x-portee ,yMin = y-portee ;        
    int xMax = x+portee ,yMax = y+portee;
   //on fait en sorte que les Min et Max ne sortent pas de la map
    if(x-portee<0){                          
        xMin = 0;
    }
    if(x+portee>CARTE_TAILLE-1){ 
        xMax = CARTE_TAILLE-1;
    }
    if(y-portee<0){
        yMin=0;
    }
    if(y+portee>CARTE_TAILLE-1){
        yMax=CARTE_TAILLE-1;
    }

    int t = 0;
    while(!t){
        t = verif_coord(perso->position_x,perso->position_y,xMax, yMax, xMin, yMin);
    }
    return;
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


