#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int choix_map()
{
    int num_map=0;
    char c;
    do{
        printf("Choisissez le numero de la carte (1-3): ");
        if (scanf("%d", &num_map)!=1) 
        {
            printf("Valeur entree incorrect.\n");
            vider_tampon();
            num_map=0;
        }
        else {
            if ((c = getchar()) != '\n') 
            {
                printf("Trop de valeur entree, reessayez.\n");
                vider_tampon();
                num_map = 0;
            }
            else if(num_map < 1 || num_map > 3) 
            {
                printf("Numsro de carte invalide. Veuillez choisir entre 1, 2 et 3.\n");
                num_map=0;
            }
        }

    } while (num_map < 1 || num_map > 3);
    return num_map;   
}


void generation_carte(int num,char **carte )
{
	//Création des tableaux de 20*20 pour les maps à partir des fichiers texte map.txt
	char *ligne = NULL;
	FILE* fichier = NULL;
	if(carte == NULL)
	{
		printf("Erreur d'allocation memoire\n");
		exit(1);
	}
	
	//On ouvre la map que l'on va utiliser
    switch (num)
    {
        case 1:
            fichier = fopen("map1.txt","r");
        break;
        case 2:
            fichier = fopen("map2.txt","r");
        break;
        case 3:
            fichier = fopen("map3.txt","r");
        break;
        default:
            printf("Erreur de choix de carte\n");
            exit(1);
            break;
    } 
	
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
		fgetc(fichier);
		carte[a]=ligne;

	}
	
	affiche_tableau(carte,CARTE_TAILLE);
	fclose(fichier);
}
