#define MAP_SIZE 20
#include <stdio.h>
#include <stdlib.h>

int deplacement(int r,int map[MAP_SIZE][MAP_SIZE],int  position[2]){   //r = nombre de deplacement
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
    int lecture1,lecture2;
    int t;
    lecture1 = scanf("%ld", &mouvement_x);      //on verifie si de nobres sont rentrée/ si c est un      nombre entier, lecture = 1    sinon, lecture = 0
                                        printf("%d %d\n",lecture1, mouvement_x);    //je cherchais la ou ca plantais
    lecture2 = scanf("%ld", &mouvement_y);
                                        printf("%d %d\n",lecture2, mouvement_y);    //je cherchais la ou ca plantais
    if(lecture1 == 0 ||lecture2 == 0){
        printf("mauvaise coordonnees\n");
                                        printf("%d %d\n",lecture1, lecture2);       //idem
        exit(3);
    }
                                        printf("%d %d \n",lecture1, lecture2);      //idem
    if(mouvement_x<xMin || mouvement_x>xMax){  //on regarde si les coordonées sont compris dans les cases authorisées
        exit(2);
    }
    if(mouvement_y<yMin || mouvement_y>yMax){
        exit(3);
    }
    if(t == 0){
        exit(4);
    }
    else{
        printf("pas de probleme");
    }
}



void afficherTableau(int tableau[MAP_SIZE][MAP_SIZE]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            printf("%d ", tableau[i][j]);
        }
        printf("\n");
    }
}


int main(){
    int carte[MAP_SIZE][MAP_SIZE] = {0};
    afficherTableau(carte);
}

