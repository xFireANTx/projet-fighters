#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "map.h"
#include "combat.h"
#include "utilitaire.h"
#include "tours.h"



void deplacement_bis(int *x, int *y, int portee, char **carte,char lettre) {
    if (portee == 0) {
        printf("Portee maximale atteinte.\n");
        return;
    }

    char input;
    scan_char(&input);

    int n_x = *x;
    int n_y = *y;
    if(input == 'a') {
        return; // Fin du déplacement
    }
    else if (input == 'z' && *x > 0 && carte[*x-1][*y] == '.') {
        n_x = *x - 1;
    } else if (input == 's' && *x < CARTE_TAILLE-1 && carte[*x+1][*y] == '.') {
        n_x = *x + 1;
    } else if (input == 'q' && *y > 0 && carte[*x][*y-1] == '.') {
        n_y = *y - 1;
    } else if (input == 'd' && *y < CARTE_TAILLE-1 && carte[*x][*y+1] == '.') {
        n_y = *y + 1;
    } else {
        deplacement_bis(x, y, portee, carte, lettre);
        return; // Si le mouvement n'est pas valide, on redemande
    }

    // Mettre à jour la carte et les coordonnées
    carte[*x][*y] = '.'; // Ancienne position
    carte[n_x][n_y] = lettre; // Nouvelle position 
    *x = n_x;
    *y = n_y;

    affiche_tableau(carte, CARTE_TAILLE);
    deplacement_bis(x, y, portee - 1, carte,lettre);


