#include <stdio.h>
#include <stdlib.h>
#include "interface.h"


#define CARTE_TAILLE 20

int main()
{
	//Création des tableaux de 20*20 pour les maps à partir des fichiers texte map.txt
	char *ligne = NULL;
	char **carte = NULL;
	FILE* fichier = NULL;
	
	carte = malloc(CARTE_TAILLE*sizeof(char*));
	if(carte == NULL)
	{
		printf("Erreur d'allocation memoire\n");
		exit(1);
	}
	
	
	fichier = fopen("map1.txt","r");
	if(fichier == NULL)
	{
		printf("Ouverture du fichier impossible\n");
		exit(1);
	}
	
	for(int a=0;a<CARTE_TAILLE;a++)
	{
		ligne = malloc(CARTE_TAILLE*sizeof(char));
		if(ligne == NULL)
		{
			printf("Erreur d'allocation memoire\n");
			exit(1);
		}
		for(int b=0;b<CARTE_TAILLE;b++)
		{
			 ligne[b]=fgetc(fichier);
			 
			 
		}
		//Récupération du saut de ligne
		char poubelle = fgetc(fichier);
		carte[a]=ligne;
	}
	
	affiche_tableau(carte,CARTE_TAILLE);
	fclose(fichier);
	for(int a=0;a<CARTE_TAILLE;a++)
	{
		free(carte[a]);
	}
	free(carte);
}
