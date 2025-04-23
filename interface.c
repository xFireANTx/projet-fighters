#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "combat.h"
#include "utilitaire.h"



void affiche_tableau(char** tab,int taille)
{
	if(tab==NULL)
	{
		printf("Erreur \n");
		exit(1);
	}
	for(int a=0;a<taille;a++)
	{
		for(int b=0;b<taille;b++)
		{
			printf("%c",tab[a][b]);
		}
		printf("\n");
	}
}
