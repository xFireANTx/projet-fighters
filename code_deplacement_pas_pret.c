#define MAP_SIZE 20
#include <stdio.h>
#include <stdlib.h>


int verif_coord(int xMax, int yMax, int xMin, int yMin) {
    int mouvement_x, mouvement_y;
    int lecture1, lecture2;

    printf("Entrez x entre %d et %d : ", xMin, xMax);
    while ((lecture1 = scanf("%d", &mouvement_x)) != 1) {               //lecture regarde si un bon nombre a été entré 1=oui  0=non
        printf("Entree invalide ! Veuillez entrer un nombre : ");
        while (getchar() != '\n');                                      // Nettoie le buffer
    }

    printf("Entrez y entre %d et %d : ", yMin, yMax);
    while ((lecture2 = scanf("%d", &mouvement_y)) != 1) {               //lecture regarde si un bon nombre a été entré 1=oui  0=non
        printf("Entree invalide ! Veuillez entrer un nombre : ");
        while (getchar() != '\n');                                      // Nettoie le buffer
    }

    if (mouvement_x < xMin || mouvement_x > xMax) {                     //On regarde si les coordonees sont dans l intervalle de deplacement
        printf("x n est pas une coordonnee valable.\n");
        return 0;
    }
    if (mouvement_y < yMin || mouvement_y > yMax) {
        printf("y n est pas une coordonnee valable.\n");
        return 0;
    }

    printf("Pas de probleme.\n");
    return 1;
}

int deplacement(int r,char map[MAP_SIZE][MAP_SIZE],int  position[2]){   //r = nombre de deplacement //il manque le changement de la map et la mise a jour de la position
    int x = position[0],y = position[1];  //position depart
    int xMin = x-r ,yMin = y-r ;        //cases disponible pour mouvement
    int xMax = x+r ,yMax = y+r;
    int mouvement_x,mouvement_y;        //position arrivée          
    if(x-r<0){                          //on fait en sorte que les Min et Max ne sortent pas de la map
        xMin = 0;
    }
    if(x+r<MAP_SIZE){
        xMax = MAP_SIZE;
    }
    if(y-r<0){
        yMin=0;
    }
    if(y+r>MAP_SIZE){
        yMax=MAP_SIZE;
    }
    int t = 0;
    while(t == 0){
    t = verif_coord(xMax, yMax, xMin, yMin);
    }
}


void afficherTableau(char tableau[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
}


int main(){
    char carte[MAP_SIZE][MAP_SIZE] = {0};
    afficherTableau(carte);
    
}

