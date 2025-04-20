/*Bien que le fichier s'appelle interface.h, il sert surtout à stocker tout les prototypes de focntions.*/ 

#ifndef INTERFACE_H
	#define INTERFACE_H
    #define CARTE_TAILLE 20
	
	void affiche_tableau(char** tab,int taille);
    void generation_carte(int num,char **carte);
    void vider_tampon();
    int choix_map();
    void scan_int(int *valeur);
    void scan_float(float *valeur);
	
#endif
