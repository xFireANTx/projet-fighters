#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"


int verif_coord(int* x, int* y,int xMax, int yMax, int xMin, int yMin) { // x/y_MAX/MIN coordonnees du carree representant la portee du joueur
    // x et y sont les coordonnees du joueur    
    printf("Entrez x entre %d et %d : ", xMin, xMax);
    scan_int(x);//fichier utilitaire

    printf("Entrez y entre %d et %d : ", yMin, yMax);
    scan_int(y);//fichier utilitaire

    if (*x < xMin || *x> xMax) {                     //On regarde si les coordonees sont dans l intervalle de deplacement
        printf("x n est pas une coordonnee valable.\n");
        return 0;
    }
    if (*y < yMin || *y > yMax) {
        printf("y n est pas une coordonnee valable.\n");
        return 0;
    }

    printf("Pas de probleme.\n");
    printf("Nouvelle position : x = %d, y = %d\n", *x, *y);
    return 1;
}



int deplacement(int portee,char map[CARTE_TAILLE][CARTE_TAILLE],int  position[2]){   //r = nombre de deplacement //il manque le changement de la map et la mise a jour de la position
    int x = position[0],y = position[1];  //position depart
    int xMin = x-portee ,yMin = y-portee ;        //cases disponible pour mouvement
    int xMax = x+portee ,yMax = y+portee;
    int mouvement_x,mouvement_y;        //position arrivée          
    if(x-portee<0){                          //on fait en sorte que les Min et Max ne sortent pas de la map
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
        t = verif_coord(position,position+1,xMax, yMax, xMin, yMin);
    }
}