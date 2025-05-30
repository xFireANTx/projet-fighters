//Ce fichiers headers contient toutes les fonctions relatives au combat du jeu

#ifndef COMBAT_H
    #define COMBAT_H
    typedef struct {
        char nom[10];
        int valeur;
        char description[80];
        int nbTourActifs;
        int nbTourRechargement;
        int portee;
    } Competence;
    
    typedef struct {

        char nom[9];
        char premierelettre;
        int equipe;
        float pvCourant;
        float pvMax;
        float attaque;
        float defense;
        float agilite;
        float vitesse;
        Competence competences[3];
        int effetActif;
        int dureeEffet;
        int position_x;
        int position_y;
        int deplacement;
        int portee;
        int vivant;
    } Combattant;

    typedef struct {
        int equipe;
        char nom[51];
        Combattant combattant1;
        Combattant combattant2;
        Combattant combattant3;
    } Equipe;

    Combattant creerCombattant(int perso,int num_equipe);
    void assignation_competence(Combattant *perso,int num);
    Combattant choix_perso(int num_equipe,int deja_pris[]);
    Equipe creerEquipe(int num_equipe,char **carte);

    
    void affiche_equipe(Equipe equipe);
    
    void verif_combattant_portee(char **carte,int x, int y, int portee, int num_equipe, Combattant* cible, int* cible_atteignable,Combattant *allie, int *allie_atteignable);
    void attaque_base(Combattant agresseur, Combattant* ennemi, Combattant* allie,char **carte);
    int attaque_base_degat(Combattant agresseur, Combattant* victime);


    void afficherStats(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants);

    int choix_competence(Combattant agresseur,Combattant *allie, Combattant *allie_copie , Combattant *ennemi, char **carte);
    void afficherCompetence(Combattant *perso);

    void application_effet(Combattant *victime, Combattant *agresseur,int effet,int num_competence);
    int Mage(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);
    int Soigneur(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);
    int Ninja(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);
    int Tank(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);
    int Guerrier(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);
    int Archer(Combattant *joueur, Combattant joueur_copie, char **carte, Combattant* ennemi, Combattant *allie, int choix);

#endif
