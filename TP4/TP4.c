#include "TP4.h"

t_ListePositions *creer_liste_positions()
{
    //On alloue de la mémoire pour créer une liste de positions
    t_ListePositions* newL = (t_ListePositions*)malloc(sizeof(t_ListePositions));

    //On test si l'allocation a bien été réalisée et si oui, on initialise les champs:
    if (newL == NULL)
        return NULL;
    else
    {
        
        newL->debut = NULL;
        newL->nb_elements = 0;
        return newL;
    }
}



int ajouter_position(t_ListePositions *listeP, int ligne, int ordre, int num_phrase)
{
    //On alloue de la mémoire pour créer une position:
    t_Position *newP = (t_Position*)malloc(sizeof(t_Position));

    //On test si l'allocation a bien été faite:
    if (!newP)
        return 0;
    else
    {
        //On initialise la nouvelle position:
        newP->numero_ligne = ligne;
        newP->ordre = ordre;
        newP->numero_phrase = num_phrase;
        newP->suivant = NULL;

        if (!listeP->debut)//si la liste ne contient encore aucune position
        {
            listeP->debut = newP;
            listeP->nb_elements = 1;
            return 1;
        }
        else // Si la liste en contient deja
        {
            t_Position *search = listeP->debut;
            while(search->suivant)
            {
                search = search->suivant;
            }
            search->suivant = newP;
            listeP->nb_elements++;
        }
    }
}

t_Index *creer_index()
{
    t_Index* new_index = malloc(sizeof(t_Index));
    if (new_index)
    {
        new_index->racine = NULL;
        new_index->nb_mots_differents = 0;
        new_index->nb_mots_total = 0;
        new_index->nb_phrase = 0;
    }
    return new_index;
}

t_Noeud *rechercher_mot(t_Index *index, char *mot)
{
    t_Noeud *recherche = index->racine;
    while (recherche)
    {
        if(strcmp(recherche->mot, mot) == 0) return recherche;
        if (strcmp(recherche->mot, mot) > 0)
        {
            recherche = recherche->filsGauche;
        }
        else if (strcmp(recherche->mot, mot) < 0)
        {
            recherche = recherche->filsDroit;
        }
    }
    return NULL;
}

int ajouter_noeud(t_Index *index, t_Noeud *noeud)
{

    if (index->racine == NULL) //si la racine est vide on place le nouveau noeud à la racine
    {
        index->racine = noeud;
        index->nb_mots_differents = 1;
        index->nb_mots_total = 1;
        return 1;
    }
    else
    {
        t_Noeud *tmpTree = index->racine; //on crée 1 indexe pour parcourir la liste

        while (tmpTree != NULL) //sinon on pacourt l'abre pour placer le noeud au bon endroit
        {
            //tmpNode = tmpTree;
            if (strcmp(noeud->mot, tmpTree->mot) == 0)
                return 0; //si le mot est déja dans la liste on retourne 0

            else if (strcmp(noeud->mot, tmpTree->mot) < 0)
            {
                if(tmpTree->filsGauche != NULL)
                {
                    tmpTree = tmpTree->filsGauche;
                }
                else
                {
                    tmpTree->filsGauche = noeud;
                    index->nb_mots_differents++;
                    index->nb_mots_total++;
                    return 1;
                }
            }

            else if (strcmp(noeud->mot, tmpTree->mot) > 0)
            {
                if(tmpTree->filsDroit != NULL)
                {
                    tmpTree = tmpTree->filsDroit;
                }
                else
                {
                    tmpTree->filsDroit = noeud;
                    index->nb_mots_differents++;
                    index->nb_mots_total++;
                    return 1;
                }
                
            }
        }
    }
}

int indexer_fichier(t_Index *index, char *filename)
{
    FILE* file = NULL;
    int line = 1, order = 1, phrase = 1;
    char mot[NB_LETTRES_MOT];
    mot[0] = '\0';
    int caractereActuel = 0;
    int nb_mot_indexe = 0;

    file = fopen(filename, "r+");
    if (!file)
    {
        printf("Echec de l'importation.\n");
        return 0;
    }

    do
    {
        caractereActuel = fgetc(file); // On lit le caractère

        if (isalnum(caractereActuel))
        {
            addLetter(mot, caractereActuel);
        }

        else if (caractereActuel == ' ' || caractereActuel == '\'')
        {
            if(mot[0] != '\0')
            {
                minuscule(mot);
                traiter_noeud(index, mot, order, phrase, line);
                mot[0] = '\0';
                order++;
                nb_mot_indexe++;

            }
        }

        else if (caractereActuel == '.' || caractereActuel == '?' || caractereActuel == '!')
        {
            minuscule(mot);
            traiter_noeud(index, mot, order, phrase, line);
            mot[0] = '\0';
            phrase++;
            order++;
            nb_mot_indexe++;
            index->nb_phrase++;
            fgetc(file);
        }

        else if (caractereActuel == '\n')
        {
            order = 1;
            line++;
        }

    } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    fclose(file);
    return nb_mot_indexe;
}

void addLetter(char *mot, char c)
{
    strcat(mot, (char[2]){(char)c, '\0'});
}

void minuscule(char *s)
{
    for (int i = 0; i <= strlen(s); i++)
    {
        s[i] = tolower(s[i]);
    }
}

t_Noeud *creer_noeud(char *word, int order, int phrase, int line)
{
    t_Noeud *elmt = malloc(sizeof(t_Noeud));
    if(!elmt) return NULL;
    char* new_word = malloc(30*sizeof(char));
    if(!new_word) return NULL;
    strcpy(new_word, word);
    elmt->mot = new_word;
    elmt->nb_occurences = 1;
    elmt->filsDroit = NULL;
    elmt->filsGauche = NULL;

    t_ListePositions elmt_liste_position = *creer_liste_positions();
    ajouter_position(&elmt_liste_position, line, order, phrase);
    elmt->positions = elmt_liste_position;

    return elmt;
}

void majuscule(char *s)
{
    s[0] = toupper(s[0]);
}

void traiter_noeud(t_Index *index, char *mot, int order, int phrase, int line)
{
    t_Noeud* recherche = rechercher_mot(index, mot);

    if(!recherche)
    {
        t_Noeud *new_noeud = creer_noeud(mot, order, phrase, line);
        if(!new_noeud)
        {
            printf("Probleme de creation de noeud\n");
            return;
        }
        int noeud_ajoute = ajouter_noeud(index, new_noeud);
    }

    else
    {   
        recherche->nb_occurences++;
        recherche->positions.nb_elements++;
        index->nb_mots_total++;

        ajouter_position(&recherche->positions, line, order, phrase);
    }
}

t_Pile* creer_pile(int max)
{

    t_Pile* P= (t_Pile*)malloc(sizeof(t_Pile));
    
    if(!P)
        return NULL;
     
    P->tab=(t_Noeud**)malloc(max*sizeof(t_Noeud*));
    
    if(!P->tab)
    {
        free(P);
        return NULL;
    }
    P->sommet = -1;
    P->max = max;
    return P;
}

int pile_vide(t_Pile* P)
{
    if(!P)
        return -1;
    return (P->sommet == -1);
}

int pile_pleine(t_Pile* P)
{
   if(!P)
        return -1;

    return (P->sommet == P->max-1);
}

int empiler(t_Pile* P ,t_Noeud* elmt)
{
    int a;
    a = pile_pleine(P);// 3 valeurs possible pour la variable a(voir la fonction Non_Pleine)
    if(!a)// L'ajout ne peut se faire que si a=0 (sinon la t_Pile est non initialisée ou pleine)
    {   // Si a==0
        // Mettre à jour sommet et insérer l'élément dans le tableau
        P->sommet++;
        P->tab[P->sommet] = elmt;
    }
    return a;
}

int depiler(t_Pile* P, t_Noeud** dest)
{
    int a;
    a = pile_vide(P);
    if(!a)
    {
        *dest = P->tab[P->sommet];
        P->sommet--;
    }
    return a;
}

void libere(t_Pile* P)
{
    if(P)
    {
        free(P->tab);
        free(P);
    }
}

void liberer_index(t_Index* index)
{
    suppression_postfix(index->racine);
    for(int i = 0; i < index->nb_phrase; i++)
    {
        free(index->tab_phrases[i]);
    }
    free(index);
}

void suppression_postfix(t_Noeud* racine)
{
    if(racine == NULL)
        return;
    if(racine->filsGauche)suppression_postfix(racine->filsGauche);
    if(racine->filsDroit)suppression_postfix(racine->filsDroit);

    while(racine->positions.debut)
    {
        t_Position* tmp = racine->positions.debut->suivant;
        free(racine->positions.debut);
        racine->positions.debut = tmp;
    }
    free(&(racine->positions));
    free(racine->mot);
    free(racine);
}

void afficher_index(t_Index* index)
{   
    t_Pile* P = creer_pile(index->nb_mots_differents);
    t_Noeud* courant = index->racine;
    char first_letter = -1;

    while(courant != NULL || !pile_vide(P))
    {
        while(courant != NULL)
        {
            empiler(P, courant);
            courant = courant->filsGauche;
        }

        depiler(P, &courant);

        first_letter = afficher_lettre(courant, first_letter);
        
        courant = courant->filsDroit;
    }
    libere(P);
}

char afficher_lettre(t_Noeud* courant, char first_letter)
{
    if(first_letter == (courant->mot)[0])
    {   
        char res[100];
        strcpy(res,courant->mot);
        majuscule(res);
        printf("|-- %s\n", res);
        t_Position* position_index = courant->positions.debut;
        for(int i = 0; i < courant->nb_occurences; i++)
        {
            printf("|---- (l:%d, o:%d, p:%d)\n", position_index->numero_ligne, position_index->ordre, position_index->numero_phrase);
            position_index = position_index->suivant;
        }
        printf("|\n");
    }
    else
    {
        char res[100];
        strcpy(res, courant->mot);
        first_letter = res[0];
        printf("\n%C\n", toupper(res[0]));
        printf("|\n");
        majuscule(res);
        printf("|-- %s\n", res);
        t_Position* position_index = courant->positions.debut;
        for(int i = 0; i < courant->nb_occurences; i++)
        {
            printf("|---- (l:%d, o:%d, p:%d)\n", position_index->numero_ligne, position_index->ordre, position_index->numero_phrase);
            position_index = position_index->suivant;
        }
        printf("|\n");
    }
    return first_letter;
}

int arbre_equilibre(t_Index* index)
{
    int h_right = hauteur_arbre(index->racine->filsDroit);
    int h_left = hauteur_arbre(index->racine->filsGauche);
    int diff = h_left - h_right;
    if(diff == -1 || diff == 0 || diff == 1) return 1;
    else return 0;
}

int hauteur_arbre(t_Noeud* racine)
{
    if(racine)
    {
        t_Noeud* tmp = racine;
        return (1+max(hauteur_arbre(tmp->filsDroit), hauteur_arbre(tmp->filsGauche)));
    }
    else return 0;
}

int max(int a,int b)
{
    if(a>=b)
        return a;
    else
        return b;
}

t_Index* equilibrer_index(t_Index* index)
{
    int nb_noeud = index->nb_mots_differents;
    t_Noeud* tab[nb_noeud];
    int i = 0;
    
    t_Pile* P = creer_pile(index->nb_mots_differents);//on parcours l'abre infixe en ajoutant chaque noeud dans un tableau de noeud
    t_Noeud* courant = index->racine;

    while(courant != NULL || !pile_vide(P))
    {
        while(courant != NULL)
        {
            empiler(P, courant);
            courant = courant->filsGauche;
        }

        depiler(P, &courant);

        tab[i] = courant;
        i++;

        courant = courant->filsDroit;
    }
    libere(P);

    //on obtient alors un tableau trie dans l'odre alphabetique
    t_Index* index_eq = creer_index();
    index_eq->nb_mots_differents = index->nb_mots_differents;
    index_eq->nb_mots_total = index->nb_mots_total;
    for(int i = 0; i < index->nb_phrase; i++)
    {
        index_eq->tab_phrases[i] = index->tab_phrases[i];
    }
    index_eq->racine = placer_noeud(index_eq, tab, nb_noeud);
    liberer_index(index);
    return(index_eq);
}

t_Noeud* placer_noeud(t_Index* index, t_Noeud** tab, int sup)
{
    t_Noeud* n = NULL;
    if(sup > 0)
    {
        int half = sup / 2;
        n = creer_noeud(tab[half]->mot, tab[half]->positions.debut->ordre,tab[half]->positions.debut->numero_phrase,tab[half]->positions.debut->numero_ligne);
        n->nb_occurences = tab[half]->nb_occurences;
        if(n->nb_occurences > 1)
        {
            t_Position* tmp = tab[half]->positions.debut;
            tmp = tmp->suivant;
            for(int i = 1; i < tab[half]->nb_occurences; i++)
            {
                ajouter_position(&n->positions, tmp->numero_ligne, tmp->ordre, tmp->numero_phrase);
            }
        }

        n->filsGauche = placer_noeud(index, tab, half);
        n->filsDroit = placer_noeud(index, tab + half + 1, sup - half - 1);
    }
    return n;
}

void indexer_phrase(t_Index* index, char* filename, char** tab)
{
    FILE* file = NULL;
    char phrase[NB_LETTRES_PHRASE];
    phrase[0] = '\0';
    char caractere_actuel = 0;
    int cle = 1;;
    file = fopen(filename, "r+");

    if(!file)
    {
        printf("Fichier invalide\n\n");
        return;
    }

    for(int i = 0; i < index->nb_phrase; i++)
    {
        do
        {
            char caractere_actuel = fgetc(file);
            if(caractere_actuel == '\n') caractere_actuel = fgetc(file);
            addLetter(phrase, caractere_actuel);
            if(caractere_actuel == '.')
            {
                fgetc(file);
                break;
            }

        }while(caractere_actuel != EOF);
        char* new_phrase = malloc((strlen(phrase)+1)*sizeof(char));
        strcpy(new_phrase, phrase);

        tab[i] = new_phrase;
        
        phrase[0] = '\0';
    }

    fclose(file);
}

void afficher_occurences_mot(t_Index* new_index, char* mot_recherche)
{
    t_Noeud *noeud_trouve = rechercher_mot(new_index, mot_recherche);
    if (noeud_trouve == NULL)
        printf("Ce mot n'est pas indexe.\n");
    else
    {
        t_Position *position = noeud_trouve->positions.debut;
        printf("Mot = \"%s\"\n", noeud_trouve->mot);
        printf("Occurences = %d\n", noeud_trouve->nb_occurences);

        while(position)
        {
            printf("| Ligne %d, mot %d : ", position->numero_ligne, position->ordre);
            printf("%s\n", new_index->tab_phrases[position->numero_phrase - 1]);
            position = position->suivant;
        }
        printf("\n");
    }
}