#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"

int verif_obstacle(int x, int y, char **carte) {
    if (carte[x][y] == 'X') {
        return 1; // La case est occupée par un mur
    }
    else if(carte[x][y] == '1' || carte[x][y] == '2'){
        return 2;// La case est occupée par un personnage
    }
    return 0; // La case est libre
}


// x/y_MAX/MIN coordonnees du carree representant la portee de deplacement du joueur


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
