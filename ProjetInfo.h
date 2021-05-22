//
// Created by wanto on 10/05/2021.
//

#ifndef PROJET_ALGO_PROJETINFO_H
#define PROJET_ALGO_PROJETINFO_H

#endif //PROJET_ALGO_PROJETINFO_H

/*Fichier contenant les structures */

typedef struct Boisson Boisson;
struct Boisson
{                           /*Notre boisson à ces caractéristiques et contient un pointeur associé*/
    char *nom;
    int alcool;
    int sucre;
    int prix;
    int nombreenstock;
    Boisson *suivant;
};

typedef struct ListeBoisson ListeBoisson;       /*On définit la liste avec son premier pointeur (liste chainée) */
struct ListeBoisson
{
    Boisson *premier;
};

typedef struct Cocktail Cocktail;
struct Cocktail
{
                            /*Notre cocktail à les caractéristiques des boissons et contient un pointeur associé*/
    ListeBoisson *listeBoisson;
    int alcool;
    int sucre;
    int prix;
    char *nom;
    Cocktail *suivant;

};

typedef struct ListeCocktail ListeCocktail;
struct ListeCocktail{

    struct Cocktail *premier;

};

Boisson *obtenirBoisson(ListeBoisson *liste, char *nom);

typedef struct Commande Commande;
struct Commande{

    char *nom;
    Commande *suivant;

};

typedef struct ListeCommande ListeCommande;
struct ListeCommande{

    struct Commande *premier;

};
