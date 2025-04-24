// Ce fichiers headers contient toutes les fonctions relatives à l’interface graphique du jeu et à la carte
#ifndef INTERFACE_H
	#define INTERFACE_H
    #define CARTE_TAILLE 20
	
	void affiche_tableau(char** tab,int taille);
    void generation_carte(int num,char **carte);
    int choix_map();
    int verif_coord(int* x, int* y,int xMax, int yMax, int xMin, int yMin,char **carte);
    int verif_obstacle(int x, int y, char **carte);
    void deplacement(int *x,int*y ,int portee,char **map);

#endif
