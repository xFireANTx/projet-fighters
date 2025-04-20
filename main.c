#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int main()
{
    char **carte = malloc(CARTE_TAILLE*sizeof(char*));
    int n_map=choix_map();
    generation_carte(n_map,carte);
    affiche_tableau(carte,CARTE_TAILLE);
    for(int a=0;a<CARTE_TAILLE;a++)
	{
		free(carte[a]);
	}
	free(carte);
}
