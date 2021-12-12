#include "TP4.h"

int main()
{
    menu_principal();
    return 0;
}

void menu_principal(void)
{

    int choix;
    int continuer = 1;
    int fichier_charge = 0;
    char filename[125];
    t_Index* new_index = NULL;

    while (continuer == 1)
    {
        printf("=================================================================================\n");
        printf("||                                       MENU                                  ||\n");
        printf("=================================================================================\n");
        printf("||  1. Charger un fichier.                                                     ||\n");
        printf("||  2. Afficher les caracteristiques de l'index.                               ||\n");
        printf("||  3. Afficher l'index.                                                       ||\n");
        printf("||  4. Rechercher un mot.                                                      ||\n");
        printf("||  5. Afficher les occurences d'un mot.                                       ||\n");
        printf("||  6. Equilibrer l'index.                                                     ||\n");
        printf("||  7. Quitter.                                                                ||\n");
        printf("=================================================================================\n\n");

        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            printf("Veuillez choisir un fichier.\n");
            scanf("%124s", filename);
            new_index = creer_index();

            if (new_index)
            {   
                int nb_mot_indexe = indexer_fichier(new_index, filename);
                if(nb_mot_indexe)
                {
                    printf("\n%d mots ont ete indexes\n\n", nb_mot_indexe);
                }
                indexer_phrase(new_index, filename, new_index->tab_phrases);
            }
            else printf("\nAucun mot n'a pu etre indexe\n");
            break;

        case 2:
            if(new_index)
            {
                printf("Caracteristiques de l'index : \n\n");
                printf("    Nombre total de mots contenus dans l'index : %d\n", new_index->nb_mots_total);
                printf("    Nombre de mot differents : %d\n", new_index->nb_mots_differents);
                printf("    Hauteur de l'abre : %d\n", hauteur_arbre(new_index->racine));
                if(arbre_equilibre(new_index)) printf("    L'abre est equilibre\n\n");
                else printf("    L'arbre n'est pas equilibre\n\n");
            }
            else
                printf("Veuillez indexer un fichier\n");
            break;

        case 3:
            if (new_index)
                afficher_index(new_index);
            else 
                printf("Veuillez indexer un fichier\n");
            break;

        case 4:{
            if(new_index)
            {
                char mot_recherche[100];
                printf("Quel mot voulez vous rechercher ?\n");
                scanf("%s", mot_recherche);

                for (int i = 0; i <= strlen(mot_recherche); i++)
                {
                    mot_recherche[i] = tolower(mot_recherche[i]);
                }

                t_Noeud *noeud_trouve = rechercher_mot(new_index, mot_recherche);
                if (noeud_trouve == NULL)
                    printf("\nCe mot n'est pas indexe.\n");
                else
                {
                    t_Position *position = noeud_trouve->positions.debut;
                    printf("\nCe mot apparait %d fois : \n\n", noeud_trouve->nb_occurences);
                    for (int i = 1; i <= noeud_trouve->nb_occurences; i++)
                    {
                        printf("    Num de ligne : %d\n", position->numero_ligne);
                        printf("    Ordre dans la ligne : %d\n", position->ordre);
                        printf("    Num de phrase : %d\n\n", position->numero_phrase);
                        position = position->suivant;
                    }
                }
            }
            else
                printf("Veuillez indexer un fichier\n");
            break;
        }

        case 5:
            if(new_index)
            {
                char mot_recherche[100];
                printf("Quel mot voulez vous rechercher ?\n");
                scanf("%s", mot_recherche);

                for (int i = 0; i <= strlen(mot_recherche); i++)
                {
                    mot_recherche[i] = tolower(mot_recherche[i]);
                }

                afficher_occurences_mot(new_index, mot_recherche);
            }
            break;

        case 6:
            if(new_index)
            {
                if(arbre_equilibre(new_index))
                {
                    printf("L'arbre est deja equilibre\n\n");
                    break;
                }
                new_index = equilibrer_index(new_index);
                if(new_index) printf("L'index a bien ete equilibre\n\n");
            }
            else
                printf("Veuillez indexer un fichier\n");
            break;

        case 7:
            if(new_index)
            {
                liberer_index(new_index);
                new_index = NULL;
            }
            continuer = 0;
            break;

        default:
            break;
        }
    }
}
