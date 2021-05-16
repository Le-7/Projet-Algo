/*Projet d'info: Cocktail*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ProjetInfo.h"

int choice = 0;

int cocktailEnStock(Cocktail *pCocktail, Liste *pListe);

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    viderBuffer();
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

ListeCocktail *initialisationListeCocktail() {
    ListeCocktail *listeCocktail1 = malloc(sizeof(*listeCocktail1));
    listeCocktail1->premier = NULL;

    return listeCocktail1;
}


/*Comme on a deux listes les fonctions sont en double a chaque fois*/
Liste *initialisation() {
    Liste *liste = malloc(sizeof(*liste));
    Boisson *element = malloc(sizeof(*element));  /* on allocalise la memoire nécessaire*/

    if (liste == NULL || element == NULL)     /*si il y a rien bah on quitte, t as cru on allait rester planté la 4h */
    {
        exit(EXIT_FAILURE);
    }

    element->nom = NULL;
    element->alcool = 0;
    element->sucre = 0;
    element->prix = 0;
    element->nombreenstock = 0;         /*valeurs de base des éléments */
    element->suivant = NULL;
    liste->premier = NULL;

    return liste;
}

ListeCommande *initialisationCommande() {
    ListeCommande *liste = malloc(sizeof(*liste));
    Commande *element = malloc(sizeof(*element));  /* on allocalise la memoire nécessaire*/

    if (liste == NULL || element == NULL)     /*si il y a rien bah on quitte, t as cru on allait rester planté la 4h */
    {
        exit(EXIT_FAILURE);
    }

    element->nom = NULL;
    element->suivant = NULL;
    liste->premier = NULL;

    return liste;
}


void insertion(Liste *liste, char *nvNom, int nvAlcool, int nvSucre, int nvPrix, int nvNombreenstock) {
    /* Création du nouvel élément */

    Boisson *nouveau = malloc(sizeof(Boisson));

    if (liste == NULL || nouveau == NULL) {
        exit(EXIT_FAILURE);
    }

    nouveau->nom = nvNom;
    nouveau->alcool = nvAlcool;
    nouveau->sucre = nvSucre;
    nouveau->prix = nvPrix;
    nouveau->nombreenstock = nvNombreenstock;

    /* Insertion de l'élément au début de la liste */

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

}

void insertionCommande(ListeCommande *listeCommande, Commande *commande) {

    if (commande != NULL) {

        commande->suivant = listeCommande->premier;
        listeCommande->premier = commande;
    }
}

void insertionCocktail(ListeCocktail *liste, Liste *listBoissons, char *nvNom, int nvAlcool, int nvSucre, int nvPrix) {
    /* Création du nouvel élément */

    Cocktail *nouveau = malloc(sizeof(Cocktail));

    if (liste == NULL || nouveau == NULL) {
        exit(EXIT_FAILURE);
    }

    nouveau->nom = nvNom;
    nouveau->alcool = nvAlcool;
    nouveau->sucre = nvSucre;
    nouveau->prix = nvPrix;
    nouveau->listeBoisson = listBoissons;

    /* Insertion de l'élément au début de la liste */

    nouveau->suivant = liste->premier;

    liste->premier = nouveau;

}

int cocktailEnStock(Cocktail *pCocktail, Liste *liste) {

    if (pCocktail->listeBoisson == NULL) {
        exit(EXIT_FAILURE);
    }

    Boisson *actuel = pCocktail->listeBoisson->premier;
    while (actuel != NULL) {

        if (obtenirBoisson(liste, actuel->nom)->nombreenstock <= 0) {

            return 1;

        }

        actuel = actuel->suivant;
    }

    return 0;
}

void afficherInformationBoisson(Liste *liste) {
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    Boisson *actuel = liste->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/
    while (actuel != NULL)          /*si il y a plus d élément on quitte*/
    {
        /*on affiche l élément et apres on passe au suivant*/
        printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros, %i en stock \n ", actuel->nom,
               actuel->alcool, actuel->sucre, actuel->prix, actuel->nombreenstock);
        actuel = actuel->suivant;
    }
}

void afficherListeBoisson(Liste *liste, ListeCocktail *pCocktail) {

    if (liste == NULL) {
        return;
    }

    Boisson *actuel = liste->premier;
    while (actuel != NULL) {

        if (actuel->nombreenstock > 0) {
            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros\n ", actuel->nom, actuel->alcool,
                   actuel->sucre, actuel->prix);
        } else {

            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros RUPTURE DE STOCK\n ", actuel->nom,
                   actuel->alcool,
                   actuel->sucre, actuel->prix);

        }
        fflush(stdout);
        actuel = actuel->suivant;

    }

    if (pCocktail == NULL) {
        return;
    }

    Cocktail *cocktailactuel = pCocktail->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/
    while (cocktailactuel != NULL)          /*si il y a plus d élément on quitte*/
    {
        /*on affiche l élément et apres on passe au suivant*/

        if (cocktailEnStock(cocktailactuel, liste) == 1) {
            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros\n ", cocktailactuel->nom,
                   cocktailactuel->alcool,
                   cocktailactuel->sucre, cocktailactuel->prix);
        } else {

            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros RUPTURE DE STOCK\n ",
                   cocktailactuel->nom, cocktailactuel->alcool,
                   cocktailactuel->sucre, cocktailactuel->prix);

        }
        cocktailactuel = cocktailactuel->suivant;
    }
}

void afficherListeCocktail(ListeCocktail *liste, Liste *listeBoisson) {
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    Cocktail *actuel = liste->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/
    while (actuel != NULL)          /*si il y a plus d élément on quitte*/
    {
        /*on affiche l élément et apres on passe au suivant*/

        if (cocktailEnStock(actuel, listeBoisson) == 0) {
            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros\n ", actuel->nom, actuel->alcool,
                   actuel->sucre, actuel->prix);
        } else {

            printf(" ||%s|| , %i pourcents d'alcool, %i pourcents de sucre, %i euros RUPTURE DE STOCK\n ", actuel->nom,
                   actuel->alcool,
                   actuel->sucre, actuel->prix);

        }
        actuel = actuel->suivant;
    }
}

void afficherListeCommandes(ListeCommande *listeCommande) {

    if (listeCommande == NULL) {

        exit(EXIT_FAILURE);

    }

    Commande *commande = listeCommande->premier;
    while (commande != NULL) {

        printf("%s\n", commande->nom);
        commande = commande->suivant;

    }

}

int listeCocktailContient(ListeCocktail *liste, char *nom) {

    Cocktail *actuel = liste->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/

    while (actuel != NULL)          /*si il y a plus d élément on quitte*/
    {

        if (strcmp(actuel->nom, nom) == 0) {

            return 1;

        }
        actuel = actuel->suivant;  /*on affiche l élément et apres on passe au suivant*/
    }

    return 0;
}

int listeBoissonContient(Liste *liste, char *nom) {

    Boisson *actuel = liste->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/

    while (actuel != NULL)          /*si il y a plus d élément on quitte*/
    {

        if (strcmp(actuel->nom, nom) == 0) {

            return 1;

        }
        actuel = actuel->suivant;  /*on affiche l élément et apres on passe au suivant*/
    }

    return 0;
}

Boisson *obtenirBoisson(Liste *liste, char *nom) {

    Boisson *actuel = liste->premier;

    while (actuel != NULL) {

        if (strcmp(actuel->nom, nom) == 0) {


            return actuel;

        }
        actuel = actuel->suivant;
    }

    return NULL;

}

Cocktail *obtenirCocktail(ListeCocktail *listeCocktail, char *nom) {

    Cocktail *actuel = listeCocktail->premier;

    while (actuel != NULL) {

        if (strcmp(actuel->nom, nom) == 0) {

            return actuel;

        }
        actuel = actuel->suivant;
    }

    return NULL;
}

void creationCocktail(Liste *liste, ListeCocktail *pCocktail, int client) {

    printf("Quel est le nom de votre Cocktail ?\n");
    char nom[50];
    lire(nom,50);

    int condition = 1;
    char nomBoisson[100];

    Cocktail cocktail;
    cocktail.listeBoisson = initialisation();

    int alcool = 0;
    int sucre = 0;
    int prix = 0;
    int compteur = 0;

    while (condition == 1) {

        printf("Quelle boisson voulez vous utiliser?\n");

        lire(nomBoisson,50);

        if (listeBoissonContient(liste, nomBoisson) == 0) {
            printf("Nous ne proposons pas cette boisson\n");
        } else {
            Boisson *boisson = obtenirBoisson(liste, nomBoisson);

            if (boisson->nombreenstock == 0) {

                printf("Cette boisson est en rupture de stock\n");
            } else {

                alcool += boisson->alcool;
                sucre += boisson->sucre;
                prix += boisson->prix;
                compteur++;
                insertion(cocktail.listeBoisson, boisson->nom, boisson->alcool, boisson->sucre, boisson->prix,
                          boisson->nombreenstock);

            }
        }


        printf("Voulez vous utiliser une autre boisson?\n");
        char *reponse = "";
        scanf("%s", reponse);

        if (strcmp(reponse, "non") == 0) {

            condition = 0;

        }

    }

    afficherListeBoisson(cocktail.listeBoisson, NULL);
    insertionCocktail(pCocktail, cocktail.listeBoisson, nom, alcool / compteur, sucre / compteur, (prix+(prix/10)));
    afficherListeCocktail(pCocktail, liste);

}

void afficherMenuBarman(Liste *liste, ListeCocktail *pCocktail, ListeCommande *listeCommande) {

    int condition = 0;

    while (condition == 0) {

        printf("Vous êtes dans le menu Barman\n");
        printf("Vous pouvez :\n");
        printf("1. Gérer les stocks\n");
        printf("2. Voir la cartes des boissons\n");
        printf("3. Créer un Cocktail\n");
        printf("4. Gérer commandes\n");
        printf("5. Quitter\n");
        printf("Tapez 1, 2, 3, 4 ou 5\n");
        fflush(stdout);
        scanf("%i", &choice);

        switch (choice) {

            case 1:
                choice = 0;
                afficherInformationBoisson(liste);
                break;

            case 2:
                choice = 0;
                afficherListeBoisson(liste, pCocktail);
                break;

            case 3:
                choice = 0;
                creationCocktail(liste, pCocktail, 0);
                break;

            case 4:

                choice = 0;
                afficherListeCommandes(listeCommande);
                break;

            default:

                choice = 0;
                condition = 1;
                return;
        }
    }
}

Commande *commanderBoisson(Liste *liste, ListeCocktail *listeCocktail) {

    printf("Entrez le nom de votre Boisson\n");
    fflush(stdout);
    char nomBoisson[100] = {0};
    scanf("%s", nomBoisson);

    if (listeBoissonContient(liste, nomBoisson) == 1) {

        if (obtenirBoisson(liste, nomBoisson)->nombreenstock > 0) {

            Boisson *boisson = obtenirBoisson(liste, nomBoisson);
            boisson->nombreenstock -= 1;

            Commande *commande = malloc(sizeof(*commande));
            commande->nom = boisson->nom;
            commande->suivant = NULL;

            return commande;

        } else {

            printf("Nous n'avons plus de %s en stock\n", nomBoisson);
            fflush(stdout);
        }

    } else if (listeCocktailContient(listeCocktail, nomBoisson)) {

        if (cocktailEnStock(obtenirCocktail(listeCocktail, nomBoisson), liste) == 0) {

            Cocktail *cocktail = obtenirCocktail(listeCocktail, nomBoisson);

            Boisson *actuel = cocktail->listeBoisson->premier;

            while (actuel != NULL) {

                obtenirBoisson(liste, actuel->nom)->nombreenstock -= 1;
                actuel = actuel->suivant;

            }

            Commande *commande = malloc(sizeof(*commande));
            commande->nom = cocktail->nom;
            commande->suivant = NULL;

            return commande;
        }


    } else {

        printf("Nous ne proposons pas cette boisson\n");
        fflush(stdout);
        return NULL;

    }

    return NULL;

}

void afficherMenuClient(Liste *liste, ListeCocktail *pCocktail, ListeCommande *listeCommandes) {

    int condition = 1;

    while (condition == 1) {

        printf("Vous êtes dans le menu client\n");
        printf("Vous pouvez :\n");
        printf("1. Commander une boisson\n");
        printf("2. Voir la cartes des boissons\n");
        printf("3.Créer un Cocktail\n");
        printf("4. Quitter\n");
        printf("Tapez 1, 2, 3 ou 4\n");

        fflush(stdout);

        scanf("%i", &choice);

        switch (choice) {

            case 1:

                choice = 0;
                insertionCommande(listeCommandes, commanderBoisson(liste, pCocktail));
                break;

            case 2:
                choice = 0;
                afficherListeBoisson(liste, pCocktail);
                break;

            case 3:
                choice = 0;
                creationCocktail(liste, pCocktail, 1);
                break;

            case 4:
                choice = 0;
                condition = 0;
                break;

        }

    }

}

void afficherMenu(Liste *liste, ListeCocktail *listeCocktail, ListeCommande *listeCommandes) {

    int condition = 1;

    while (condition == 1) {

        printf("Vous êtes :\n");
        printf("1. Barman\n");
        printf("2. Client\n");
        printf("3. Quitter\n");
        printf("Tapez 1,2 ou 3\n");
        fflush(stdout);


        scanf("%i", &choice);

        if (choice == 1) {
            choice = 0;
            afficherMenuBarman(liste, listeCocktail, listeCommandes);

        } else if (choice == 2) {
            choice = 0;
            afficherMenuClient(liste, listeCocktail, listeCommandes);

        } else if (choice == 3) {
            choice = 0;
            condition = 0;

        }

    }
}

int main() {

    printf("Bienvenue dans le Bar !\n");
    fflush(stdout);

    Liste *listeBoisson = initialisation();

    insertion(listeBoisson, "Tequila", 40, 0, 8, 20);
    insertion(listeBoisson, "Vin", 12, 0, 6,
              5);    //Ca sert d exemple mais apres c est facile de demander a l utilisateur de rentrée ses propes bails avec un menu, jvoulais faire ca vers la fin
    insertion(listeBoisson, "Rhum", 40, 0, 4, 53);

    insertion(listeBoisson, "Jus d'orange", 0, 10, 4, 60);
    insertion(listeBoisson, "Noix de Coco", 0, 4, 8, 1);
    insertion(listeBoisson, "Coca", 0, 30, 2, 247);

    afficherListeBoisson(listeBoisson, NULL);

    ListeCocktail *listeCocktail = initialisationListeCocktail();

    ListeCommande *listeCommandes = initialisationCommande();

    afficherMenu(listeBoisson, listeCocktail, listeCommandes);

    return 0;
}
