#ifndef TOURS_H
    #define TOURS_H
    #include "combat.h"
    
    // Fonctions qui trient le tableau de combattants par ordre de vitesse décroissante
    void definirOrdreAttaque(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants);
    void triABullesOptimise(Combattant tableau[], int taille);

    int est_vivant(Equipe equipe1, Equipe equipe2);
    int tours(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants, char **carte);

    void afficherCompetence(Combattant *perso);
    void afficherStats(Equipe equipe1, Equipe equipe2, Combattant *tabCombattants);
    
    int choix_attaque();
    void verifEffet(Combattant* perso);
    void cooldown(Combattant* perso);


#endif
