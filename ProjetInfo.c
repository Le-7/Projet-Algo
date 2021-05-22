/*Projet d'info: Cocktail*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "ProjetInfo.h"

int choice = 0;

int cocktailEnStock(Cocktail *pCocktail, ListeBoisson *pListe);

int tailleEntier(int entier) {

    int compteur = 1;

    while (entier > 9) {

        entier /= 10;
        compteur++;

    }

    return compteur;

}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int lireEntreeConsole(char *chaine, int longueur) {
    //viderBuffer();
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL) {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL) {
            *positionEntree = '\0';
        } else {
            viderBuffer();
        }
        return 1;
    } else {
        viderBuffer();
        return 0;
    }
}

void afficherRetourLigne(int nombre) { /*Création fonction retour ligne pour */

    while (nombre != 0) {

        printf("\n");
                nombre--;

    }

}

void afficherEspaces(int nombre) { /*Création fonction afficher espace*/

    while (nombre != 0) { /*Boucle*/

        printf(" "); /*Affiche espace*/
                nombre--; /*Décrémentation*/

    }

}

void afficherTexte(char *chaine, int nombreCaractereTotal) {

    int tailleChaine = (int) strlen(chaine);
    int nombreEspaces = nombreCaractereTotal - tailleChaine - 1;

    printf("*");

    afficherEspaces(nombreEspaces / 2);
    printf("%s", chaine);
        afficherEspaces(nombreEspaces - (nombreEspaces / 2));

}

void afficherEntier(int entier, int nombreCaractereTotal) {

    int tailleChaine = tailleEntier(entier);
    int nombreEspaces = nombreCaractereTotal - tailleChaine - 1;

    printf("*");
        afficherEspaces(nombreEspaces / 2);
    printf("%i", entier);
        afficherEspaces(nombreEspaces - (nombreEspaces / 2));

}

ListeCocktail *initialisationListeCocktail() { /*Création de la liste des cocktails*/
    ListeCocktail *listeCocktail1 = malloc(sizeof(*listeCocktail1)); /*Allocation de la mémoire nécessaire*/
    listeCocktail1->premier = NULL;

    return listeCocktail1;
}


/*Comme on a deux listes les fonctions sont en double a chaque fois*/
ListeBoisson *initialisation() {
    ListeBoisson *liste = malloc(sizeof(*liste));
    Boisson *element = malloc(sizeof(*element));  /*on allocalise la memoire nécessaire*/

    if (liste == NULL || element == NULL)     /*s'il n'y a rien, on quitte*/
    {
        exit(EXIT_FAILURE);
    }
    /*valeurs de base des éléments des boissons*/
    element->nom = NULL;
    element->alcool = 0;
    element->sucre = 0;
    element->prix = 0;
    element->nombreenstock = 0;         
    element->suivant = NULL;
    liste->premier = NULL;

    return liste;
}

ListeCommande *initialisationCommande() {
    ListeCommande *liste = malloc(sizeof(*liste));
    Commande *element = malloc(sizeof(*element));  /*on allocalise la memoire nécessaire*/

    if (liste == NULL || element == NULL)     /*s'il n'y a rien, on quitte*/
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

    Boisson *nouveau = malloc(sizeof(Boisson)); /*Allocation de la mémoire nécessaitr*/

    if (liste == NULL || nouveau == NULL) { /*S'il n'y a rien, on quitte*/
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

void insertionCocktail(ListeCocktail *liste, ListeBoisson *listBoissons, char *nvNom, int nvAlcool, int nvSucre,
                       int nvPrix) {
    /* Création du nouvel élément */

    Cocktail *nouveau = malloc(sizeof(Cocktail)); /*Allocation de la mémoire nécessaire*/

    if (liste == NULL || nouveau == NULL) { /*S'il n'y a rien, on quitte*/
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

int cocktailEnStock(Cocktail *pCocktail, ListeBoisson *liste) { /*Vérifier les stocks d'un cocktail*/

    if (pCocktail->listeBoisson == NULL) { /*S'il n'y a rien, on quitte*/
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

void afficherinformationCocktail(Cocktail *cocktail, char *texte) {

    if (cocktail != NULL) {

        printf("*************************************************************************\n");
                afficherTexte(texte, 72);
        printf("*\n");
                printf("*************************************************************************\n");
                printf("*             Nom             *    Sucre    *    Alcool    *    Prix    *\n");
                printf("*                             *             *              *            *\n");
        
        Boisson *boissonActuelle = cocktail->listeBoisson->premier;
        while (boissonActuelle != NULL) {

            afficherTexte(boissonActuelle->nom, 30);
            afficherEntier(boissonActuelle->sucre, 14);
            afficherEntier(boissonActuelle->alcool, 15);
            afficherEntier(boissonActuelle->prix, 13);
            boissonActuelle = boissonActuelle->suivant;
            printf("*\n");
                    }


        afficherTexte(cocktail->nom, 30);
        afficherEntier(cocktail->sucre, 14);
        afficherEntier(cocktail->alcool, 15);
        afficherEntier(cocktail->prix, 13);

    } else {

        exit(EXIT_FAILURE);

    }


}

void afficherInformationBoisson(ListeBoisson *listeBoisson, char *texte) {

    if (listeBoisson != NULL) {

        printf("****************************************************************************************\n");
                afficherTexte(texte, 87);
        printf("*\n");
                printf("****************************************************************************************\n");
                printf("*             Nom             *    Sucre    *    Alcool    *    Prix    *    Stocks    *\n");
                printf("*                             *             *              *            *              *\n");
        

        Boisson *boissonActuelle = listeBoisson->premier;
        while (boissonActuelle != NULL) {

            afficherTexte(boissonActuelle->nom, 30);
            afficherEntier(boissonActuelle->sucre, 14);
            afficherEntier(boissonActuelle->alcool, 15);
            afficherEntier(boissonActuelle->prix, 13);
            afficherEntier(boissonActuelle->nombreenstock, 15);
            printf("*\n");
                        boissonActuelle = boissonActuelle->suivant;

        }

        printf("****************************************************************************************\n");
            } else {

        exit(EXIT_FAILURE);

    }
}

void afficherListeBoisson(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail) {

    if (listeBoisson != NULL || listeCocktail != NULL) {

        printf("*************************************************************************\n");
                printf("*                            Liste Boissons                             *\n");
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
            
            if (boissonActuelle->nombreenstock <= 0) { /*Si le stock de boisson est nul*/

                printf("*    RUPTURE DE STOCK\n"); /*On affiche "rupture de stock"*/
                
            }
            printf("\n");
                        boissonActuelle = boissonActuelle->suivant;

        }
    }

    if (listeCocktail != NULL) {

        Cocktail *cocktailactuel = listeCocktail->premier;
        while (cocktailactuel != NULL) {
            afficherTexte(cocktailactuel->nom, 30);
            afficherEntier(cocktailactuel->sucre, 14);
            afficherEntier(cocktailactuel->alcool, 15);
            afficherEntier(cocktailactuel->prix, 13);
            printf("*");
            
            if (cocktailEnStock(cocktailactuel, listeBoisson)) { /*Si le stock de boisson est nul*/
/*Alors un cocktail qui contient cette boisson n'est plus disponible non plus*/
                printf("*    RUPTURE DE STOCK\n"); /*On affiche "rupture de stock"*/
                
            }
            printf("\n");
                        cocktailactuel = cocktailactuel->suivant;
        }
    }

    if (listeBoisson != NULL || listeCocktail != NULL) {

        printf("*************************************************************************\n");
                afficherRetourLigne(3);

    }
}

void afficherListeCommandes(ListeCommande *listeCommande) { /*Afficher l'historique des commandes*/

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

    Cocktail *actuel = liste->premier; /*on affiche l'élément actuel qu'on assigne au début au premier élément de la liste*/

    while (actuel != NULL)          /*s'il n'y a plus d élément on quitte*/
    {

        if (strcmp(actuel->nom, nom) == 0) {

            return 1;

        }
        actuel = actuel->suivant;  /*on affiche l'élément et apres on passe au suivant*/
    }

    return 0;
}

int listeBoissonContient(ListeBoisson *liste, char *nom) {

    Boisson *actuel = liste->premier; /*on affiche l'élément actuel qu'on assigne au début au premier élément de la liste*/

    while (actuel != NULL)          /*s'il n'y a plus d élément on quitte*/
    {

        if (strcmp(actuel->nom, nom) == 0) {

            return 1;

        }
        actuel = actuel->suivant;  /*on affiche l'élément et après on passe au suivant*/
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

void gererStocks(ListeBoisson *listeBoisson) {

    afficherInformationBoisson(listeBoisson, "Liste Boisson"); /*On affiche la liste des boissons*/
    afficherRetourLigne(3);

    printf("Voulez vous commander une boisson?\n");
    
    char reponse[10] = {""};

    lireEntreeConsole(reponse, 10);

    if (strcmp(reponse, "oui") == 0) { /*Si la réponse est "oui" */


        printf("Quelle boisson voulez vous commander?\n"); /*On affiche */
                char nomBoisson[50] = {""};
        lireEntreeConsole(nomBoisson, 50);

        if (listeBoissonContient(listeBoisson, nomBoisson) == 1) {

            int condition = 0;
            char quantite[10];

            while (condition == 0) {

                printf("Quelle quantite voulez vous commander?\n");
                
                lireEntreeConsole(quantite, 10);

                if (strtol(quantite, NULL, 10) == 0L) {

                    printf("Veuillez entrer un chiffre !\n");
                    
                } else if (strtol(quantite, NULL, 10) <= 0) {

                    printf("Veuillez entrer un chiffre superieur a 0!\n");
                    
                } else {

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

    char *nom = malloc(50 * sizeof(char));
    int condition = 1;

    while (condition == 1) {

        printf("Quel est le nom de votre Cocktail ?\n");
                lireEntreeConsole(nom, 50);
        if (strcmp(nom, "") != 0) {

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

        if (listeBoissonContient(listeBoisson, nomBoisson) == 0 ||
            (client == 0 && obtenirBoisson(listeBoisson, nomBoisson)->nombreenstock <= 0)) {
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
        lireEntreeConsole(reponse, 10);

        if (strcmp(reponse, "non") == 0) {

            condition = 1;

        }

    }

    cocktail.nom = nom;
    cocktail.sucre = sucre;
    cocktail.prix = prix;
    cocktail.alcool = alcool;

    afficherinformationCocktail(&cocktail, "Voici les details de votre cocktail");
    insertionCocktail(listeCocktail, cocktail.listeBoisson, nom, alcool / compteur, sucre / compteur,
                      (prix + (prix / 10)));
    afficherRetourLigne(3);
}

void ajouterBoisson(ListeBoisson *listeBoisson) {

    char *nomBoisson = malloc(50 * sizeof(char));

    printf("Entrez le nom de votre boisson (30 caracteres max)\n");
        lireEntreeConsole(nomBoisson, 50);

    if (strlen(nomBoisson) > 30) {

        ajouterBoisson(listeBoisson);
        return;

    }

    char sucre[10] = {""};
    printf("Entrez le pourcentage de sucre de votre boisson [0-100]\n");
        lireEntreeConsole(sucre, 10);

    while (strtol(sucre, NULL, 10) < 0 || strtol(sucre, NULL, 10) > 100) {

        printf("Entrez le pourcentage de sucre de votre boisson [0-100]\n");
                lireEntreeConsole(sucre, 10);

    }

    char alcool[10] = {""};
    printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
        lireEntreeConsole(alcool, 10);

    while (strtol(alcool, NULL, 10) < 0 || strtol(alcool, NULL, 10) > 100) {

        printf("Entrez le pourcentage d'alcool de votre boisson [0-100]\n");
                lireEntreeConsole(alcool, 10);

    }

    char prix[10] = {""};
    printf("Entrez le prix de votre boisson [0-100]\n");
        lireEntreeConsole(prix, 10);

    while (strtol(prix, NULL, 10) < 0) {

        printf("Entrez le prix de votre boisson (>0)\n");
                lireEntreeConsole(prix, 10);

    }

    insertion(listeBoisson, nomBoisson, strtol(alcool, NULL, 10), strtol(sucre, NULL, 10), strtol(prix, NULL, 10), 0);

    printf("Votre boisson a ete ajoutee\n");
    
    afficherRetourLigne(3);

}

void afficherMenuBarman(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, ListeCommande *listeCommande,
                        int *chiffreAffaire) { /*Affichage du menu BARMAN*/

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
                printf("7. Quitter\n");
                printf("Tapez 1, 2, 3, 4, 5, 6 ou 7\n");
        
        lireEntreeConsole(choix, 10);
        choice = strtol(choix, NULL, 10);

        afficherRetourLigne(3);

        switch (choice) {

            case 1: /*Si choix 1*/
                choice = 0;
                afficherListeCommandes(listeCommande); /*Appel de la fonction pour afficher la liste de commandes*/
                break;

            case 2: /*Si choix 2*/
                choice = 0;
                creationCocktail(listeBoisson, listeCocktail, 0); /*Appel de la fonction qui créé les cocktails*/
                break;

            case 3: /*Si choix 3*/
                choice = 0;
                gererStocks(listeBoisson); /*Appel de la fonction gérer les stocks*/
                break;

            case 4: /*Si choix 4*/

                choice = 0;
                printf("Le chiffre d'affaires du bar est de %i\n", *chiffreAffaire); /*Affichage du chiffre d'affaires*/
                                afficherRetourLigne(3);
                break;

            case 5: /*Si choix 5*/

                choice = 0;
                afficherListeBoisson(listeBoisson, listeCocktail); /*Afficher la liste des boissons et cocktails*/
                break;

            case 6: /*Si choix 6*/

                choice = 0;
                ajouterBoisson(listeBoisson); /*Appel de la fonction qui ajoute une nouvelle boisson*/
                break;

            case 7: /*Si choix 7*/

                choice = 0; /*Retour au menu principal*/
                return;
        }
    }
}

Commande *commanderBoisson(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, int *chiffreAffaire) {

    printf("Voici la listeBoisson des Boissons proposées: \n");
        afficherListeBoisson(listeBoisson, listeCocktail);

    printf("Entrez le nom de votre Boisson\n");
        char nomBoisson[100] = {0};
    lireEntreeConsole(nomBoisson, 100);

    if (listeBoissonContient(listeBoisson, nomBoisson) == 1) {

        if (obtenirBoisson(listeBoisson, nomBoisson)->nombreenstock > 0) {

            Boisson *boisson = obtenirBoisson(listeBoisson, nomBoisson);
            boisson->nombreenstock -= 1;

            Commande *commande = malloc(sizeof(*commande));
            commande->nom = boisson->nom;
            commande->suivant = NULL;
            *chiffreAffaire += boisson->prix;
            printf("Vous avez commander %s, vous serez servi rapidement\n", boisson->nom);
                        printf("Le prix de votre commande est de %i euros\n", boisson->prix);
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
            printf("Vous avez commande %s, vous serez servi rapidement\n", cocktail->nom);
                        printf("Le prix de votre commande est de %i euros\n", cocktail->prix);
                        return commande;
        }


    } else {

        printf("Nous ne proposons pas cette boisson\n");
                return NULL;

    }

    return NULL;

}
/*Affichage du menu CLIENT*/
void afficherMenuClient(ListeBoisson *listeBoisson, ListeCocktail *pCocktail, ListeCommande *listeCommandes,
                        int *chiffreAffaire) {

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
        
        lireEntreeConsole(choix, 10); /*Utilisation de la base 10*/
        choice = strtol(choix, NULL, 10); /*Utilisation de strol pour convertir le chaine en long*/

        switch (choice) {

            case 1: /*Si le choix est commander une boisson, on appelle la fonction commanderBoisson*/

                choice = 0;
                insertionCommande(listeCommandes, commanderBoisson(listeBoisson, pCocktail, chiffreAffaire));
                break;

            case 2: /*Si le choix est voir les boissons, on appelle la fonction afficher ListeBoisson*/
                choice = 0;
                afficherListeBoisson(listeBoisson, pCocktail);
                break;

            case 3: /*Si le choix est créer un cockatil, on appelle la fonction créationCocktail*/
                choice = 0;
                creationCocktail(listeBoisson, pCocktail, 1);
                break;

            case 4: /*Si le choix est de quitter, on quitte et on revient au menu principal */
                choice = 0;
                condition = 0;
                break;

        }

    }

}
/*Affichage du menu PRINCIPAL*/
void afficherMenu(ListeBoisson *listeBoisson, ListeCocktail *listeCocktail, ListeCommande *listeCommandes,
                  int *chiffreAffaire) {

    int condition = 1;

    while (condition == 1) {

        printf("Vous êtes :\n");
                printf("1. Barman\n");
                printf("2. Client\n");
                printf("3. Quitter\n");
                printf("Tapez 1,2 ou 3\n");
        
        char choix[10];

        lireEntreeConsole(choix, 10); /*Utilisation de la base 10*/
        choice = strtol(choix, NULL, 10); /*Utilisation de strol pour convertir le chaine en long*/

        if (choice == 1) { /*Si l'utilisateur entre 1, le menu BARMAN s'affiche*/
            choice = 0;
            afficherMenuBarman(listeBoisson, listeCocktail, listeCommandes, chiffreAffaire);

        } else if (choice == 2) { /*Si l'utilisateur entre 2, le menu CLIENT s'affiche*/
            choice = 0;
            afficherMenuClient(listeBoisson, listeCocktail, listeCommandes, chiffreAffaire);

        } else if (choice == 3) { /*Si l'utilisateur entre 3 il quitte le programme*/
            choice = 0;
            condition = 0;

        } else { /*Si l'utilisateur entre autre chose, le menu se réaffiche*/

            choice = 0;

        }

    }
}

int main() {   /*Fonction principale*/

    printf("Bienvenue dans le Bar !\n"); /*Affichage d'un message*/
    
    ListeBoisson *listeBoisson = initialisation();  /*Initialisation de la liste des boissons*/

    insertion(listeBoisson, "tequila", 40, 0, 8, 20); /*Insertion des boissons pré-créées*/
    insertion(listeBoisson, "vin", 12, 0, 6, 5); /*Nom, degré d'alcool, degré de sucre, prix, stock*/
    insertion(listeBoisson, "rhum", 40, 0, 4, 53);
    insertion(listeBoisson, "jus d'orange", 0, 10, 4, 60);
    insertion(listeBoisson, "noix de Coco", 0, 4, 8, 1);
    insertion(listeBoisson, "coca", 0, 30, 2, 247);

    ListeCocktail *listeCocktail = initialisationListeCocktail(); /*Initialisation des cocktails*/
    ListeCommande *listeCommandes = initialisationCommande(); /*Initialisation des commandes*/

    int chiffreAffaire = 0; /*Chiffre d'affaire initialisé à 0*/

    afficherMenu(listeBoisson, listeCocktail, listeCommandes, &chiffreAffaire); /*Affichage menu*/

    return 0;
}
