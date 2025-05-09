//Ce fichiers headers contient toutes les fonctions relatives au combat du jeu

#ifndef COMBAT_H
    #define COMBAT_H
    typedef struct {
        char nom[10];
        int valeur;
        char description[10];
        int nbTourActifs;
        int nbTourRechargement;
    } Competence;
    
    typedef struct {

        char nom[11];
        int equipe;
        float pvCourant;
        float pvMax;
        float attaque;
        float defense;
        float agilite;
        float vitesse;
        Competence competences[5];
        int effetActif;
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
    } EQUIPE;

    Combattant creerCombattant(int perso);
    EQUIPE creerEquipe(int num_equipe);
    void affiche_equipe(EQUIPE equipe);
    int verif_portee(Combattant agresseur, Combattant victime);
    void combattre(Combattant combattant1, Combattant* combattant2);
    void afficherStats(Combattant combattants[], int nbCombattants);
    int attaquer(Combattant agresseur, Combattant* victime);
#endif
