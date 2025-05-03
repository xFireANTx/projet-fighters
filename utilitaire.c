#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "interface.h"
#include "combat.h"
#include "utilitaire.h"


void vider_tampon()
{
    char c;
    while (c = getchar() != '\n' && c!=EOF); // Vide le tampon d'entrée
  // on vérifie EOF car dans certain cas particulier getchar() renvoie EOF ce qui peut créer une boucle infinie car EOF marque la fin du flux entrant
}

/*La fonction scan_TYPE(TYPE* valeur)  vérifie si l'utilisateur a bien entré un nombre du type VALEUR
Si l'utilisateur entre autre chose qu'un nombre du type VALEUR, la fonction lui demande de recommencer
Si l'utilisateur entre plusieurs valeurs, la fonction lui demande de recommencer
*/

void scan_int(int *valeur)
{
    int resultat = 0;
    do{
        resultat = scanf("%d", valeur);
        if (resultat != 1) 
        {
            printf("Valeur entree incorrect, reessayez:\n");
            vider_tampon();
        
        }
        else
        {
            char c = getchar();
            if (c != '\n') 
            {
                printf("Trop de valeur entree, reessayez.\n");
                vider_tampon();
                resultat = 0; // Réinitialiser resultat pour continuer la boucle
            }
        }
    }while(resultat != 1);
}

void scan_float(float *valeur)
{
    int resultat = 0;
    do{
        resultat = scanf("%f", valeur);
        if (resultat != 1) 
        {
            printf("Valeur entree incorrect, reessayez:\n");
            vider_tampon();
        
        }
        else
        {
            char c = getchar();
            if (c != '\n') 
            {
                printf("Trop de valeur entree, reessayez.\n");
                vider_tampon();
                resultat = 0; // Réinitialiser resultat pour continuer la boucle
            }
        }
    }while(resultat != 1);
}

void scan_char(char *valeur)
{
    int resultat = 0;
    do{
        resultat = scanf(" %c", valeur); // Notez l'espace avant %c pour ignorer les espaces
        if (resultat != 1) 
        {
            printf("Vous devez rentrez un caractere,reessayer:\n"); //Cas extrêmement rare comme ctrl + D ou ctrl + Z
            vider_tampon();
        
        }
        else
        {
            char c = getchar();
            if (c != '\n') 
            {
                printf("Trop de caractere entree, reessayez:\n");
                vider_tampon();
                resultat = 0; // Réinitialiser resultat pour continuer la boucle
            }
        }
    }while(resultat != 1);
}

int choix()
{
    printf("Confirmez vous votre choix (o/n): ");
    char c;
    scan_char(&c); // On utilise une fonction de scan_char pour lire un seul caractère
    if(c =='O' || c =='o')
    {
        printf("Choix confirme\n");
        return 1;
    }
    else if(c == 'N' || c == 'n')
    {
        printf("Choix non confirme\n");
        return 0;
    }
    else
    {
        printf("Erreur de saisie,vous devez choisir entre Oui ou Non (o/n), recommencez.\n");
        return choix(); // Appel récursif pour redemander le choix
    }  
}

int nbAleatoire(int max) {
    srand(time(NULL)); // Initialisation de la graine de génération aléatoire
    if (max <= 0) return 0;
    return rand() % max;
}
