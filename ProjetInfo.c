/*Projet d'info: Cocktail*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ProjetInfo.h"

int choice = 0;

int cocktailEnStock(Cocktail *pCocktail, ListeBoisson *pListe);

void initialiserTableauChar(char tableau[],int taille){

    while(taille != 0){

        tableau[taille] = "";
        taille--;

    }

}

int tailleEntier(int entier){

    int compteur = 1;

    while(entier > 9){

        entier /= 10;
        compteur++;

    }

    return compteur;

}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lireEntreeConsole(char *chaine, int longueur)
{
    //viderBuffer();
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

void afficherRetourLigne(int nombre){

    while(nombre != 0){

        printf("\n");
        nombre--;

    }

}

void afficherEspaces(int nombre){

    while(nombre != 0){

        printf(" ");
        nombre--;

    }

}

void afficherTexte(char *chaine,int nombreCaractereTotal){

    int tailleChaine = (int)strlen(chaine);
    int nombreEspaces = nombreCaractereTotal-tailleChaine-1;

    printf("*");
    afficherEspaces(nombreEspaces/2);
    printf("%s",chaine);
    afficherEspaces(nombreEspaces-(nombreEspaces/2));

}

void afficherEntier(int entier,int nombreCaractereTotal){

    int tailleChaine = tailleEntier(entier);
    int nombreEspaces = nombreCaractereTotal-tailleChaine-1;

    printf("*");
    afficherEspaces(nombreEspaces/2);
    printf("%i",entier);
    afficherEspaces(nombreEspaces-(nombreEspaces/2));

}

ListeCocktail *initialisationListeCocktail() {
    ListeCocktail *listeCocktail1 = malloc(sizeof(*listeCocktail1));
    listeCocktail1->premier = NULL;

    return listeCocktail1;
}


/*Comme on a deux listes les fonctions sont en double a chaque fois*/
ListeBoisson *initialisation() {
    ListeBoisson *liste = malloc(sizeof(*liste));
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


void insertion(ListeBoisson *liste, char *nvNom, int nvAlcool, int nvSucre, int nvPrix, int nvNombreenstock) {
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

void insertionCocktail(ListeCocktail *liste, ListeBoisson *listBoissons, char *nvNom, int nvAlcool, int nvSucre, int nvPrix) {
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

int cocktailEnStock(Cocktail *pCocktail, ListeBoisson *liste) {

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

void afficherInformationBoisson(ListeBoisson *listeBoisson) {

    if (listeBoisson != NULL) {

        printf("****************************************************************************************\n");
        printf("*                                   ListeBoisson Boissons                                     *\n");
        printf("****************************************************************************************\n");
        printf("*             Nom             *    Sucre    *    Alcool    *    Prix    *    Stocks    *\n");
        printf("*                             *             *              *            *              *\n");


        Boisson *boissonActuelle = listeBoisson->premier;
        while (boissonActuelle != NULL) {

            afficherTexte(boissonActuelle->nom, 30);
            afficherEntier(boissonActuelle->sucre, 14);
            afficherEntier(boissonActuelle->alcool, 15);
            afficherEntier(boissonActuelle->prix, 13);
            afficherEntier(boissonActuelle->nombreenstock,15);
            printf("*\n");
            boissonActuelle = boissonActuelle->suivant;

        }

        printf("****************************************************************************************\n");
    }else{

        exit(EXIT_FAILURE);

    }
}

void afficherListeBoisson(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail) {

    if(listeBoisson != NULL || listeCocktail != NULL){

        printf("*************************************************************************\n");
        printf("*                            ListeBoisson Boissons                             *\n");
        printf("*************************************************************************\n");
        printf("*             Nom             *    Sucre    *    Alcool    *    Prix    *\n");
        printf("*                             *             *              *            *\n");

    }

    if (listeBoisson != NULL) {

        Boisson *boissonActuelle = listeBoisson->premier;
        while (boissonActuelle != NULL) {

            afficherTexte(boissonActuelle->nom, 30);
            afficherEntier(boissonActuelle->sucre, 14);
            afficherEntier(boissonActuelle->alcool, 15);
            afficherEntier(boissonActuelle->prix, 13);
            printf("*");

            if (boissonActuelle->nombreenstock <= 0) {

                printf("*    RUPTURE DE STOCK\n");

            }
            printf("\n");
            boissonActuelle = boissonActuelle->suivant;

        }
    }

    if (listeCocktail != NULL) {

        Cocktail *cocktailactuel = listeCocktail->premier;
        while (cocktailactuel != NULL)
        {
            afficherTexte(cocktailactuel->nom,30);
            afficherEntier(cocktailactuel->sucre,14);
            afficherEntier(cocktailactuel->alcool,15);
            afficherEntier(cocktailactuel->prix,13);
            printf("*");

            if (cocktailEnStock(cocktailactuel, listeBoisson)) {

                printf("*    RUPTURE DE STOCK\n");

            }
            printf("\n");
            cocktailactuel = cocktailactuel->suivant;
        }
    }

    if(listeBoisson != NULL || listeCocktail != NULL){

        printf("*************************************************************************\n");
        afficherRetourLigne(3);

    }
}

void afficherListeCocktail(ListeBoisson *listeBoisson, ListeCocktail *liste) {
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

    printf("Les clients ont commande: \n");

    Commande *commande = listeCommande->premier;
    while (commande != NULL) {

        printf(" 1 %s\n", commande->nom);
        commande = commande->suivant;

    }
    afficherRetourLigne(3);

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

int listeBoissonContient(ListeBoisson *liste, char *nom) {

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

Boisson *obtenirBoisson(ListeBoisson *liste, char *nom) {

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

void gererStocks(ListeBoisson *listeBoisson){

    afficherInformationBoisson(listeBoisson);
    afficherRetourLigne(3);

    printf("Voulez vous commander une boisson?\n");

    char reponse[10] = {""};

    lireEntreeConsole(reponse,10);

    if(strcmp(reponse,"oui") == 0){


        printf("Quelle boisson voulez vous commander?\n");
        char nomBoisson[50] = {""};
        lireEntreeConsole(nomBoisson,50);

        if(listeBoissonContient(listeBoisson,nomBoisson) == 1){

            int condition = 0;
            char quantite[10];

            while(condition == 0){

            printf("Quelle quantite voulez vous commander?\n");

            lireEntreeConsole(quantite,10);

                if(strtol(quantite,NULL,10) == 0L) {

                    printf("Veuillez entrer un chiffre !\n");

                }else if(strtol(quantite,NULL,10) <= 0){

                    printf("Veuillez entrer un chiffre superieur a 0!\n");

                }else{

                    condition = 1;

                }
            }

                obtenirBoisson(listeBoisson, nomBoisson)->nombreenstock += strtol(quantite, NULL, 10);

        }

        gererStocks(listeBoisson);

    }

    afficherRetourLigne(3);
}

void creationCocktail(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, int client) {

    char nom[50] = {""};
    int condition = 1;

    while(condition == 1) {

        printf("Quel est le nom de votre Cocktail ?\n");
        lireEntreeConsole(nom, 50);
        if(strcmp(nom,"") != 0){

            condition = 0;

        }
    }
    char nomBoisson[100];

    Cocktail cocktail;
    cocktail.listeBoisson = initialisation();

    int alcool = 0;
    int sucre = 0;
    int prix = 0;
    int compteur = 0;

    while (condition == 0) {

        printf("Quelle boisson voulez vous utiliser?\n");

        lireEntreeConsole(nomBoisson, 100);

        if (listeBoissonContient(listeBoisson, nomBoisson) == 0) {
            printf("Nous ne proposons pas cette boisson\n");
        } else {
            Boisson *boisson = obtenirBoisson(listeBoisson, nomBoisson);

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
        char reponse[10];
        lireEntreeConsole(reponse,10);

        if (strcmp(reponse, "non") == 0) {

            condition = 1;

        }

    }

    afficherListeBoisson(cocktail.listeBoisson, NULL);
    insertionCocktail(listeCocktail, cocktail.listeBoisson, nom, alcool / compteur, sucre / compteur, (prix + (prix / 10)));
    afficherRetourLigne(3);
}

void ajouterBoisson(ListeBoisson *listeBoisson) {

    char nomBoisson[50];

    printf("Entrez le nom de votre boisson (30 caracteres max)\n");
    lireEntreeConsole(nomBoisson,50);

    if(strlen(nomBoisson) > 30){

        ajouterBoisson(listeBoisson);
        return;

    }

    char sucre[10] = {""};
    printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
    lireEntreeConsole(sucre,10);

    while(strtol(sucre,NULL,10) < 0 || strtol(sucre,NULL,10) > 100) {

        printf("Entrez le pourcentage de sucre de votre boisson [0-100]\n");
        lireEntreeConsole(sucre,10);

    }

    char alcool[10] = {""};
    printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
    lireEntreeConsole(alcool,10);

    while(strtol(alcool,NULL,10) < 0 || strtol(alcool,NULL,10) > 100) {

        printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
        lireEntreeConsole(alcool,10);

    }

    char prix[10] = {""};
    printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
    lireEntreeConsole(prix,10);

    while(strtol(prix,NULL,10) < 0) {

        printf("Entrez le prix de votre boisson (>0)\n");
        lireEntreeConsole(prix,10);

    }

    insertion(listeBoisson,nomBoisson, strtol(alcool,NULL,10), strtol(sucre,NULL,10),strtol(prix,NULL,10),0);

    printf("Votre boisson a ete ajoutee\n");

    afficherRetourLigne(3);

}

void afficherMenuBarman(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, ListeCommande *listeCommande, int *chiffreAffaire) {

    char choix[10];

    while (1 == 1) {


        printf("Vous êtes dans le menu Barman\n");
        printf("Vous pouvez :\n");
        printf("1. Gerer commandes\n");
        printf("2. Creer un Cocktail\n");
        printf("3. Gerer les stocks\n");
        printf("4. Voir le chiffre d'affaires\n");
        printf("5. Afficher liste boissons\n");
        printf("6. Ajout nouvelle Boisson\n");
        printf("7. Quitter");
        printf("Tapez 1, 2, 3, 4, 5, 6 ou 7\n");

        lireEntreeConsole(choix,10);
        choice = strtol(choix,NULL,10);

        afficherRetourLigne(3);

        switch (choice) {

            case 1:
                choice = 0;
                afficherListeCommandes(listeCommande);
                break;

            case 2:
                choice = 0;
                creationCocktail(listeBoisson, listeCocktail, 0);
                break;

            case 3:
                choice = 0;
                gererStocks(listeBoisson);
                break;

            case 4:

                choice = 0;
                printf("Le chiffre d'affaires du bar est de %i\n",*chiffreAffaire);
                afficherRetourLigne(3);
                break;

            case 5:

                choice = 0;
                afficherListeBoisson(listeBoisson, listeCocktail);
                break;

            case 6:

                choice = 0;
                ajouterBoisson(listeBoisson);
                break;

            case 7:

                choice = 0;
                return;
        }
    }
}

Commande *commanderBoisson(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, int *chiffreAffaire) {

    printf("Voici la listeBoisson des Boissons proposées: \n");
    afficherListeBoisson(listeBoisson, listeCocktail);

    printf("Entrez le nom de votre Boisson\n");
    char nomBoisson[100] = {0};
    lireEntreeConsole(nomBoisson,100);

    if (listeBoissonContient(listeBoisson, nomBoisson) == 1) {

        if (obtenirBoisson(listeBoisson, nomBoisson)->nombreenstock > 0) {

            Boisson *boisson = obtenirBoisson(listeBoisson, nomBoisson);
            boisson->nombreenstock -= 1;

            Commande *commande = malloc(sizeof(*commande));
            commande->nom = boisson->nom;
            commande->suivant = NULL;
            *chiffreAffaire += boisson->prix;
            printf("Vous avez commander %s, vous serez servi rapidement\n",boisson->nom);
            return commande;

        } else {

            printf("Nous n'avons plus de %s en stock\n", nomBoisson);
        }

    } else if (listeCocktailContient(listeCocktail, nomBoisson)) {

        if (cocktailEnStock(obtenirCocktail(listeCocktail, nomBoisson), listeBoisson) == 0) {

            Cocktail *cocktail = obtenirCocktail(listeCocktail, nomBoisson);

            Boisson *actuel = cocktail->listeBoisson->premier;

            while (actuel != NULL) {

                obtenirBoisson(listeBoisson, actuel->nom)->nombreenstock -= 1;
                actuel = actuel->suivant;

            }

            Commande *commande = malloc(sizeof(*commande));
            commande->nom = cocktail->nom;
            commande->suivant = NULL;

            *chiffreAffaire += cocktail->prix;
            printf("Vous avez commander %s, vous serez servi rapidement\n",cocktail->nom);
            return commande;
        }


    } else {

        printf("Nous ne proposons pas cette boisson\n");
        return NULL;

    }

    return NULL;

}

void afficherMenuClient(ListeBoisson *listeBoisson, ListeCocktail *pCocktail, ListeCommande *listeCommandes,int *chiffreAffaire) {

    int condition = 1;
    char choix[10];

    while (condition == 1) {

        printf("Vous êtes dans le menu client\n");
        printf("Vous pouvez :\n");
        printf("1. Commander une boisson\n");
        printf("2. Voir la cartes des boissons\n");
        printf("3.Créer un Cocktail\n");
        printf("4. Quitter\n");
        printf("Tapez 1, 2, 3 ou 4\n");

        lireEntreeConsole(choix,10);
        choice = strtol(choix,NULL,10);

        switch (choice) {

            case 1:

                choice = 0;
                insertionCommande(listeCommandes, commanderBoisson(listeBoisson, pCocktail, chiffreAffaire));
                break;

            case 2:
                choice = 0;
                afficherListeBoisson(listeBoisson, pCocktail);
                afficherListeCocktail(listeBoisson,pCocktail);
                break;

            case 3:
                choice = 0;
                creationCocktail(listeBoisson, pCocktail, 1);
                break;

            case 4:
                choice = 0;
                condition = 0;
                break;

        }

    }

}

void afficherMenu(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, ListeCommande *listeCommandes, int *chiffreAffaire) {

    int condition = 1;

    while (condition == 1) {

        printf("Vous êtes :\n");
        printf("1. Barman\n");
        printf("2. Client\n");
        printf("3. Quitter\n");
        printf("Tapez 1,2 ou 3\n");

        char choix[10];

        lireEntreeConsole(choix,10);
        choice = strtol(choix,NULL,10);

        if (choice == 1) {
            choice = 0;
            afficherMenuBarman(listeBoisson, listeCocktail, listeCommandes, chiffreAffaire);

        } else if (choice == 2) {
            choice = 0;
            afficherMenuClient(listeBoisson, listeCocktail, listeCommandes,chiffreAffaire);

        } else if (choice == 3) {
            choice = 0;
            condition = 0;

        }else{

            choice = 0;

        }

    }
}

int main() {

    printf("Bienvenue dans le Bar !\n");

    ListeBoisson *listeBoisson = initialisation();

    insertion(listeBoisson, "tequila", 40, 0, 8, 20);
    insertion(listeBoisson, "vin", 12, 0, 6,5);
    insertion(listeBoisson, "rhum", 40, 0, 4, 53);
    insertion(listeBoisson, "jus d'orange", 0, 10, 4, 60);
    insertion(listeBoisson, "noix de Coco", 0, 4, 8, 1);
    insertion(listeBoisson, "coca", 0, 30, 2, 247);

    ListeCocktail *listeCocktail = initialisationListeCocktail();
    ListeCommande *listeCommandes = initialisationCommande();

    int chiffreAffaire = 0;

    afficherMenu(listeBoisson, listeCocktail, listeCommandes, &chiffreAffaire);

    return 0;
}
