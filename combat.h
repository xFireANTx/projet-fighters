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
        float pvCourant;
        float pvMax;
        float attaque;
        float defense;
        float agilite;
        float vitesse;
        Competence competences[5];
        int effetActif;
    } Combattant;

    Combattant creerCombattant(float pvCourant, float pvMax, float attaque, float defense, float agilite, float vitesse);
    void afficherStats(Combattant combattants[], int nbCombattants);
    int attaquer(Combattant agresseur, Combattant* victime);

#endif
