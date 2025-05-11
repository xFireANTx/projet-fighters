// Ce fichiers headers contient toutes les fonctions relatives à la carte du jeu et au déplacement des personnages
#ifndef MAP_H
	#define MAP_H
    #define CARTE_TAILLE 20
	
    //Fonction qui créer et affiche le tableau
	void affiche_tableau(char** tab,int taille);
    void generation_carte(int num,char **carte);
    int choix_map();

    //Fonction qui s'occupent des déplacements
    void deplacement_bis(int *x,int *y,int portee,char **carte,char lettre);

#endif
