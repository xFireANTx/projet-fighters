#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "map.h"
#include "combat.h"
#include "utilitaire.h"
#include "tours.h"

int verif_obstacle(int x, int y, char **carte) {

    if(isalpha(carte[x][y])) { // Si la case est occupée par un personnage
        return 1;
    }
    return 0; // La case est libre
}


// x/y_MAX/MIN coordonnees du carree representant la portee de deplacement du joueur
int verif_coord(int* x, int* y,int xMax, int yMax, int xMin, int yMin,char **carte) {    
    affiche_tableau(carte,CARTE_TAILLE); 

    // On regarde si les coordonnees sont dans l'intervalle de deplacement
    printf("Vous etes sur la case : x = %d, y = %d\n", *x, *y);
    printf("Entrez x entre %d et %d : ", xMin, xMax);
    scan_int(x); // Regarder le fichier utilitaire pour voir comment fonctionne scan_int
    if (*x < xMin || *x > xMax) {                     
        printf("x=%d n'est pas accessible.\n", *x);
        return 0;
    }

    printf("Entrez y entre %d et %d : ", yMin, yMax);
    scan_int(y); // fichier utilitaire
    if (*y < yMin || *y > yMax) {
        printf("y=%d n'est pas accessible.\n", *y);
        return 0;
    }
    // On regarde si la case est libre
    int k = verif_obstacle(*x, *y, carte); 
    if (k == 1) { 
        printf("La case est occupee par un obstacle.\n");
        return 0;
    }
    else if (k == 2) {
        printf("La case est deja occupee par un personnage.\n");
        return 0;
    }
    else {
        printf("Voici la nouvelle position : x = %d, y = %d\n", *x, *y);
        return choix(); // On demande a l'utilisateur de confirmer son choix
    }
}

void deplacement(int *x,int *y,int portee,char **carte){   

    //cases disponible pour mouvement
    int xMin = *x-portee ,yMin = *y-portee ;        
    int xMax = *x+portee ,yMax = *y+portee;

   //on fait en sorte que les Min et Max ne sortent pas de la map
    if(*x-portee<0){                          
        xMin = 0;
    }
    if(*x+portee>CARTE_TAILLE-1){ 
        xMax = CARTE_TAILLE-1;
    }
    if(*y-portee<0){
        yMin=0;
    }
    if(*y+portee>CARTE_TAILLE-1){
        yMax=CARTE_TAILLE-1;
    }

    int t = 0;
    while(!t){
        t = verif_coord(x,y,xMax, yMax, xMin, yMin,carte);
    }
    return;
}

void deplacement_bis(int *x,int *y,int portee,char **carte){
    char input;
    affiche_tableau(carte, CARTE_TAILLE);
    scan_char(&input);
    if(input == '\n'|| portee == 0){
         return;
    }

    if(input == 'z'){
        if(carte[*x][*y-1] == '.'){
            y -= 1;
            deplacement(x, y, portee-1, carte);
        }
        else if(verif_obstacle(*x, *y-1, carte)){
            deplacement_bis(x, y, portee, carte);
        }
    }

    else if(input == 's'){
        if(carte[*x][*y+1] == '.'){
            y += 1;
            deplacement(x, y, portee-1, carte);
        }
        else if(verif_obstacle(*x, *y-1, carte)){
            deplacement_bis(x, y, portee, carte);
        }
    }

    else if(input == 'q'){
        if(carte[*x-1][*y] == '.'){
             x -= 1;
            deplacement(x, y, portee-1, carte);
        }
        else if(verif_obstacle(*x-1, *y, carte)){
            deplacement_bis(x, y, portee, carte);
        }
    }

    else if(input == 'd'){
        if(carte[*x+1][*y] == '.'){
            x += 1;
            deplacement(x, y, portee-1, carte);
        }
        else if(verif_obstacle(*x+1, *y, carte)){
            deplacement_bis(x, y, portee, carte);
        }
    }
    else {
        deplacement_bis(x, y, portee, carte);
    }
}

