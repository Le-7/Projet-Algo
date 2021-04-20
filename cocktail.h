/*Fichier contenant les structures */

typedef struct BoissonAlcoolisee BoissonAlcoolisee;
struct BoissonAlcoolisee
{
    char *nom;
    int alcool;
    int prix;
    int nombreenstock;
    BoissonAlcoolisee *suivant;
};

typedef struct BoissonnonAlcoolisee BoissonnonAlcoolisee;
struct BoissonnonAlcoolisee
{
    char *nom2;
    int sucre;
    int prix2;
    int nombreenstock2;
    BoissonnonAlcoolisee *suivant2;
};

/*Cette structure etait un essai jla laisse si vous voulez la reprendre*/
typedef struct Cocktail Cocktail;
struct Cocktail
{
    int* n1;
    int* n2;
    BoissonAlcoolisee *lalcool;
    BoissonnonAlcoolisee *lsucre;
    int nombredalcool;
    int nombredesucre;
    char *nomCocktail;

};

typedef struct Liste Liste;
struct Liste
{
    BoissonAlcoolisee *premier;
};

typedef struct Liste2 Liste2;
struct Liste2
{
    BoissonnonAlcoolisee *premier2;
};
