#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NB_PHRASES 50
#define NB_LETTRES_MOT 30
#define NB_LETTRES_PHRASE 300


//Déclaration des structures:
typedef struct t_position{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct t_position* suivant;
}t_Position;


typedef struct t_listePositions{
    struct t_position* debut;
    int nb_elements;
}t_ListePositions;


typedef struct t_noeud{
    char* mot;
    int nb_occurences;
    struct t_listePositions positions;
    struct t_noeud* filsGauche;
    struct t_noeud* filsDroit;
}t_Noeud;


typedef struct t_index{
    struct t_noeud* racine;
    char* tab_phrases[NB_PHRASES];
    int nb_mots_differents;
    int nb_mots_total;
    int nb_phrase;
}t_Index;

typedef struct t_pile{
    struct t_noeud** tab;
    int sommet;
    int max;
}t_Pile;



//Prototypes des fonctions

    //Fonctions princiaples

    void menu_principal(void);

    t_Noeud*rechercher_mot(t_Index*index, char *mot);
    
    int indexer_fichier(t_Index *index, char *filename);

    void afficher_index(t_Index* index);

    void liberer_index(t_Index* index);

    t_Index* equilibrer_index(t_Index *index);

    void afficher_occurences_mot(t_Index* index, char* mot);



    //Fonctions secondaires

    t_ListePositions* creer_liste_positions();

    int ajouter_position(t_ListePositions* listeP, int ligne, int ordre, int num_phrase);

    t_Index* creer_index();

    int ajouter_noeud(t_Index *index, t_Noeud *noeud); 
    
    void majuscule(char* s);

    void minuscule(char* s);

    void addLetter(char* mot, char c);

    t_Noeud* creer_noeud(char* word, int order, int phrase, int line);

    void traiter_noeud(t_Index* index, char* mot, int order, int phrase, int line);

    void suppression_postfix(t_Noeud* racine);

    t_Pile* creer_pile(int max);

    int pile_vide (t_Pile *P);

    int pile_pleine(t_Pile *P);

    int empiler(t_Pile* P, t_Noeud* elmt);

    int depiler(t_Pile* P, t_Noeud** dest);

    void libere(t_Pile* P);

    char afficher_lettre(t_Noeud* courant, char first_letter); 

    int arbre_equilibre(t_Index* index);

    int hauteur_arbre(t_Noeud* racine);

    int max(int a,int b);

    t_Noeud* placer_noeud(t_Index* index, t_Noeud** tab, int sup);

    void indexer_phrase(t_Index* index, char* filename, char** tab);

