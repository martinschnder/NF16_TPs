

#ifndef TP3_TP3_H
#define TP3_TP3_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Définir le type d'identifiant d'un soigneur comme "unsigned int"
typedef unsigned int Index_Soigneur;
// Définir le type d'identifiant d'un patient comme "unsigned int"
typedef unsigned int Index_Patient;
// Définir le type du temps en minute comme "unsigned int"
typedef unsigned int Time;
// Définir une structure d'une intervalle du temps où elle contient une date de début, une date de fin
// et un pointeur qui pointe l'élément suivant.
typedef struct Intervalle {
    // la date début d'une intervalle en minute, inclus
    Time debut;
    // la date fin d'une intervalle en minute, exclus
    Time fin;
    // un pointeur du type structure Intervalle qui pointe l'élément suivant.
    struct Intervalle *suivant;
} T_Intervalle;
// Définir une structure d'un soigneur où elle contient un identifiant unique,
// un nom et un prénom présenté par une chaîne de caractère,
// une liste d'intervalles du temps disponible,
// et un pointeur qui pointe l'élément suivant.
typedef struct Soigneur{
    // un identifiant unique d'un soigneur.
    Index_Soigneur id_soi;
    // le nom d'un soigneur (Max 40 caractères)
    char* nom;
    // le prenom d'un soigneur (Max 40 caractères)
    char* prenom;
    // une liste d'intervalle du temps disponbile
    T_Intervalle *listeIntervalle;
    // un pointeur du type structure Soigneur qui pointe l'élément suivant.
    struct Soigneur * suivant;
} T_Soigneur;
// Définir une structure d'un RdV médical où elle contient une description brève,
// une date de début souhaitée, une date de fin souhaitée, une date de début affectée, une date de fin affectée,
// le temps de déplacement depuis le rendez-vous précédent, un identifiant du soigneur associé, un pointeur qui pointe l'élément suivant.
typedef struct RendezVous{
    // une description brève (Max 125 caractères)
    char*desc;
    // la date de début souhaitée en minutes, inclus
    Time debut_souhaitee;
    // la date de fin souhaitée en minutes, exclus
    Time fin_souhaitee;
    // la date de début affectée en minutes, inclus
    Time debut_affectee;
    // la date de fin affectée en minutes, exclus
    Time fin_affectee;
    // le temps de déplacement depuis le RdV précédent, s'il existe; zéro sinon.
    Time temps_deplacement;
    // l'identifiant d'un soigneur associé.
    Index_Soigneur id_soi;
    // un pointeur du type structure RendezVous qui pointe l'élément suivant.
    struct RendezVous* suivant;
} T_RendezVous;

// Définir une structure d'un patient où elle contient un identifiant unique,
// un nom et un prénom présenté par une chaîne de caractère,
// une liste de RdV médicaux,
// et un pointeur qui pointe l'élément suivant.
typedef struct Patient{
    // un identifiant unique d'un patient.
    Index_Patient id_pat;
    // le nom d'un patient (Max 40 caractères)
    char* nom;
    // le nom d'un patient (Max 40 caractères)
    char* prenom;
    // la liste de RdV médicaux.
    T_RendezVous *listeRendezVous;
    // un pointeur du type structure Patient qui pointe l'élément suivant.
    struct Patient* suivant;
} T_Patient;

// Définir une structure d'un ordonnancement où elle contient une date de création, une liste de soigneurs, et une liste de patients.
typedef struct Ordonnancement{
    // la date de création d'un ordonnancement, en forme "AAAA-MM-JJ".
    char* date;
    // une liste de soigneurs.
    T_Soigneur *listeSoigneurs;
    // une liste de patients.
    T_Patient *listePatients;
} T_Ordonnancement;

void ordonnancer(T_Ordonnancement* solution);

Time somme_duree_rdv(T_Patient* patient);

void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur);

void affichage_RendezVous(T_RendezVous *rendezVous);

void affichage_Patients(T_Patient* listePatients);

void affichage_Soigneurs(T_Soigneur* listeSoigneurs);

T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi);

void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc);

T_RendezVous* ajouterRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc);

T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom);

T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom);

void exportSolution(T_Ordonnancement* solution, char* filename);

bool exist_fichier(const char *fname);

void FrontBackSplit(T_Patient* source, T_Patient** frontRef, T_Patient** backRef);

void MergeSort(T_Patient** headRef);

T_Patient* SortedMerge(T_Patient* a, T_Patient* b);

void menuPrincipal(void);

T_Soigneur* getSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur id_Soi);

void liberer_ressources(T_Ordonnancement* ordonnancement);

void liberer_resource_Intervalles(T_Intervalle * listeIntervalles);

void liberer_resource_Soigneurs(T_Soigneur * listeSoigneurs);

void liberer_resource_RendezVous(T_RendezVous * listeRendezVous);

void liberer_resource_Patients(T_Patient * listePatients);

T_Patient* creerListePatient(T_RendezVous* rdv, Index_Patient idPat, char* nom, char* prenom);

T_Patient* ajouterPatient_avecRDV(T_Patient* listePatients,T_RendezVous* rdv, Index_Patient idPat, char* nom, char* prenom);

T_Ordonnancement* creerInstance(char* filename);

#endif
