/*Projet d'info: Cocktail*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cocktail.h"  /* on integre les librairies de base et notre fichier de structure*/

/*ca c est le bail que j essayais de faire marcher pour les cocktails mais vous pouvez reprendre de 0*/
void initialisationcock(Liste *liste,Liste2 *liste2)
{ 
    int i; 
    Cocktail C;
    BoissonAlcoolisee *actuel = liste->premier;
    printf("Nom du Cocktail  ? ");
    C.nomCocktail = scanf("%s", C.nomCocktail); ;
    printf("Combien de boissons alcoolisées ? ");
    int n1 = scanf("%i", &n1);
    printf("Combien de boissons non alcoolisées ? ");
    int n2 = scanf("%i", &n2);
    C.lalcool = malloc(n1 * sizeof(BoissonAlcoolisee));
    C.lsucre = malloc(n2 * sizeof(BoissonnonAlcoolisee));
    for (i = 1 ;i<n1+1 ;i + 1)
        {
            char *x;
            printf(" Nom de la %i boisson alcoolisée ? ", i);
            x = scanf("%s", x);
            int comparaison;
            comparaison = strcmp(x, actuel->nom);
            if (comparaison == 1)
            {
                puts ("y");
            }
            actuel = actuel->suivant;
        }

}
/*Comme on a deux listes les fonctions sont en double a chaque fois*/
Liste *initialisation()             
{
    Liste *liste = malloc(sizeof(*liste));   
    BoissonAlcoolisee *element = malloc(sizeof(*element));  /* on allocalise la memoire nécessaire*/

    if (liste == NULL || element == NULL)     /*si il y a rien bah on quitte, t as cru on allait rester planté la 4h */
    {
        exit(EXIT_FAILURE);
    }

    element->nom = NULL;    
    element->alcool = 0;
    element->prix = 0;
    element->nombreenstock = 0;         /*valeurs de bases des éléments */
    element->suivant = NULL;
    liste->premier = NULL;

    return liste;
}
Liste2 *initialisation2()
{
    Liste2 *liste2 = malloc(sizeof(*liste2));
    BoissonnonAlcoolisee *element = malloc(sizeof(*element));

    if (liste2 == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    element->nom2 = "0";
    element->sucre = 0;
    element->prix2 = 0;
    element->nombreenstock2 = 0;
    element->suivant2 = NULL;
    liste2->premier2 = NULL;

    return liste2;
}
void insertion2(Liste2 *liste2, char *nvNom2,int nvSucre, int nvPrix2, int nvNombreenstock2)
{
    /* Création du nouvel élément */
    BoissonnonAlcoolisee *nouveau = malloc(sizeof(*nouveau));
    if (liste2 == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nom2 = nvNom2;
    nouveau->sucre = nvSucre;
    nouveau->prix2 = nvPrix2;
    nouveau->nombreenstock2 = nvNombreenstock2;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant2 = liste2->premier2;
    liste2->premier2 = nouveau;
}
void insertion(Liste *liste, char *nvNom,int nvAlcool, int nvPrix, int nvNombreenstock)
{
    /* Création du nouvel élément */
    BoissonAlcoolisee *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nom = nvNom;
    nouveau->alcool = nvAlcool;
    nouveau->prix = nvPrix;
    nouveau->nombreenstock = nvNombreenstock;

    /* Insertion de l'élément au début de la liste */
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }

    BoissonAlcoolisee *actuel = liste->premier; /*on affiche l élément actuel qu on assigne au debut au premier élément de la liste*/

    while (actuel != NULL)          /*si il y a plus d élément on quitte*/
    {
        printf(" ||%s|| , %i pourcents d'alcool, %i euros, %i en stock \n ", actuel->nom, actuel->alcool,actuel->prix,actuel->nombreenstock );
        actuel = actuel->suivant;  /*on affiche l élément et apres on passe au suivant*/
    }
}
void afficherListe2(Liste2 *liste2)
{
    if (liste2 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    BoissonnonAlcoolisee *actuel = liste2->premier2;

    while (actuel != NULL)
    {
        printf(" ||%s|| , %i pourcents de sucre, %i euros, %i en stock \n ", actuel->nom2, actuel->sucre,actuel->prix2,actuel->nombreenstock2 );
        actuel = actuel->suivant2;
    }
}

int main()
{
    Liste *maListe = initialisation();
    Liste2 *maListe2 = initialisation2();

    insertion(maListe, "Tequila", 40, 8, 20);
    insertion(maListe, "Vin", 12, 6, 5);    /*Ca sert d exemple mais apres c est facile de demander a l utilisateur de rentrée ses propes bails avec un menu, jvoulais faire ca vers la fin*/
    insertion(maListe, "Rome", 40, 4, 53 );
    
    insertion2(maListe2, "Jus d'orange", 10, 4, 60);
    insertion2(maListe2, "Noix de Coco", 4, 8, 2);
    insertion2(maListe2, "Coca", 30, 2, 247 );

    afficherListe(maListe);
    afficherListe2(maListe2);
    initialisationcock(maListe, maListe2);
    return 0;
}
