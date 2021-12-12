#include "../include/TP3.h"

T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom)
{
    T_Soigneur *new_soigneur;
    new_soigneur = malloc(sizeof(T_Soigneur));
    new_soigneur->id_soi = idSoi;
    new_soigneur->nom = nom;
    new_soigneur->prenom = prenom;
    new_soigneur->suivant = NULL;
    T_Soigneur* soigneur_index = listeSoigneurs;
    while(soigneur_index->suivant)
    {
        soigneur_index = soigneur_index->suivant;
    }
    soigneur_index->suivant = new_soigneur;

    T_Intervalle *nvInt = malloc(sizeof(T_Intervalle));
    nvInt->debut = 0;
    nvInt->fin = 100000;
    nvInt->suivant = NULL;

    new_soigneur->listeIntervalle = nvInt;

    return listeSoigneurs;
}

T_Soigneur* creerListeSoigneur(int idSoi, char* nom, char* prenom){
    T_Soigneur *newSoigneur = (T_Soigneur*)malloc(sizeof(T_Soigneur));

    newSoigneur->suivant = NULL;
    newSoigneur->nom = nom;
    newSoigneur->prenom = prenom;
    newSoigneur->id_soi = idSoi;

    T_Intervalle* newInter = malloc(sizeof(T_Intervalle));
    newInter->debut = 0;
    newInter->fin = 100000;
    newInter->suivant = NULL;
    newSoigneur->listeIntervalle = newInter;
    return newSoigneur;
}

T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom){
    T_Patient *new_patient;
    new_patient = malloc(sizeof(T_Patient));
    new_patient->id_pat = idPat;
    new_patient->nom = nom;
    new_patient->prenom = prenom;
    new_patient->listeRendezVous = NULL;
    new_patient->suivant = NULL;
    T_Patient* patient_index = listePatients;
    while(patient_index->suivant)
    {
        patient_index = patient_index->suivant;
    }
    patient_index->suivant = new_patient;
    return listePatients;
}

T_Patient* ajouterPatient_avecRDV(T_Patient* listePatients,T_RendezVous* rdv, Index_Patient idPat, char* nom, char* prenom){
    T_Patient *new_patient;
    new_patient = malloc(sizeof(T_Patient));
    new_patient->id_pat = idPat;
    new_patient->nom = nom;
    new_patient->prenom = prenom;
    new_patient->listeRendezVous = rdv;
    new_patient->suivant = NULL;
    T_Patient* patient_index = listePatients;
    while(patient_index->suivant)
    {
        patient_index = patient_index->suivant;
    }
    patient_index->suivant = new_patient;
    return listePatients;
}

T_Patient* creerListePatient(T_RendezVous* rdv, Index_Patient idPat, char* nom, char* prenom){
    T_Patient *newPatient = (T_Patient*)malloc(sizeof(T_Patient));
    newPatient->suivant = NULL;
    newPatient->id_pat = idPat;
    newPatient->nom = nom;
    newPatient->prenom = prenom;
    newPatient->listeRendezVous = rdv;
    return newPatient;
}

T_RendezVous* ajouterRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){

    T_RendezVous* new_Rdv = malloc(sizeof(T_RendezVous));
    new_Rdv->id_soi = idSoi;
    new_Rdv->debut_souhaitee = dateDebutSouhaitee;
    new_Rdv->fin_souhaitee = dateFinSouhaitee;
    new_Rdv->debut_affectee = 0;
    new_Rdv->fin_affectee= 0;
    new_Rdv->temps_deplacement = tempsDeplacement;
    new_Rdv->desc = desc;
    new_Rdv->suivant = NULL;
    T_RendezVous* rdv_index = listeRdV;
    while(rdv_index->suivant != NULL)
    {
        rdv_index = rdv_index->suivant;
    }
    rdv_index->suivant = new_Rdv;

    return listeRdV;
}

T_RendezVous* creerListeRendezVous(Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    T_RendezVous *newRDV = (T_RendezVous*) malloc(sizeof(T_RendezVous));
    newRDV->suivant = NULL;
    newRDV->id_soi = idSoi;
    newRDV->debut_souhaitee = dateDebutSouhaitee;
    newRDV->fin_souhaitee = dateFinSouhaitee;
    newRDV->temps_deplacement = tempsDeplacement;
    newRDV->desc = desc;
    newRDV->debut_affectee = 0;
    newRDV->fin_affectee = 0;
    return newRDV;
}

void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    T_RendezVous* Rdv_index = listeRdV;
    while(Rdv_index->id_soi != idSoi)
    {
        Rdv_index = Rdv_index->suivant;
    }
    Rdv_index->debut_souhaitee = dateDebutSouhaitee;
    Rdv_index->fin_souhaitee = dateFinSouhaitee;
    Rdv_index->desc = desc;
    Rdv_index->temps_deplacement = tempsDeplacement;
}

T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi){
    T_RendezVous* Rdv_index = listeRdV;
    if(Rdv_index->id_soi == idSoi)
    {
        listeRdV = listeRdV->suivant;
        listeRdV->temps_deplacement = 0;
        free(Rdv_index);
        return listeRdV;
    }
    else
    {
        while(Rdv_index->suivant != NULL && Rdv_index->suivant->id_soi != idSoi)
        {
            Rdv_index = Rdv_index->suivant;
        }
            if(Rdv_index->suivant->suivant == NULL)
            {
                free(Rdv_index->suivant);
                Rdv_index->suivant = NULL;
            }
            else
            {
                struct RendezVous* suivant = Rdv_index->suivant->suivant;
                free(Rdv_index->suivant);
                Rdv_index->suivant = suivant;
                Rdv_index->suivant->temps_deplacement = sqrt(pow(Rdv_index->temps_deplacement,2) + pow(suivant->temps_deplacement,2));
            }
        return listeRdV;
    }
}

void affichage_Soigneurs(T_Soigneur* listeSoigneurs){
    printf("Les informations soigneurs sont:\n");
    T_Soigneur* soigneurs_index = listeSoigneurs;
    while(soigneurs_index != NULL)
    {
        printf("ID:%d, Nom:%s, Prenom:%s, Intervalles de temps disponibles:\n", soigneurs_index->id_soi, soigneurs_index->nom, soigneurs_index->prenom);
        T_Intervalle* Rdv_index = soigneurs_index->listeIntervalle;
        while(Rdv_index != NULL)
        {
            printf("    [%d;%d[\n", Rdv_index->debut, Rdv_index->fin);
            Rdv_index = Rdv_index->suivant;
        }

        soigneurs_index = soigneurs_index->suivant;
    }
}

void affichage_Patients(T_Patient* listePatients){
    printf("\nLes informations patients sont:\n");
    T_Patient* patients_index = listePatients;
    T_RendezVous* Rdv_index = patients_index->listeRendezVous;
    while(patients_index != NULL)
    {
        printf("ID: %d, Nom: %s, Prenom: %s, Ses RdV medicaux:\n", patients_index->id_pat, patients_index->nom, patients_index->prenom);
        Rdv_index = patients_index->listeRendezVous;
        while(Rdv_index != NULL)
        {
            printf("Desc: %s, ID Soigneur: %d, temps de deplacement depuis le RdV precedent: %d\n", Rdv_index->desc, Rdv_index->id_soi, Rdv_index->temps_deplacement);
            printf("    Rdv souhaite: [%d;%d[\n", Rdv_index->debut_souhaitee, Rdv_index->fin_souhaitee);
            printf("    Rdv affecte: [%d;%d[\n", Rdv_index->debut_affectee, Rdv_index->fin_affectee);
            Rdv_index = Rdv_index->suivant;
        }
        patients_index = patients_index->suivant;
    }
}

void affichage_RendezVous(T_RendezVous *rendezVous){
    printf("\nDesc: %s,  ID SOI: %d,  Temps de deplacement depuis le rdv precedent: %d\n", rendezVous->desc, rendezVous->id_soi, rendezVous->temps_deplacement);
    printf("    Rdv souhaite : [%d, %d[\n", rendezVous->debut_souhaitee, rendezVous->fin_souhaitee);
    printf("    Rdv affecte : [%d, %d[\n\n", rendezVous->debut_affectee, rendezVous->fin_affectee);
}

char* date(){
    int jour, mois, an;
    time_t now;
    time(&now);

    char *c = malloc(100);

    struct tm *local = localtime(&now);
    jour = local->tm_mday;
    mois = local->tm_mon + 1;
    an = local->tm_year + 1900;

    sprintf(c,"%d-%d-%d", an, mois, jour);
    return c;
}

T_Ordonnancement* creerInstance(char* filename){
    T_Ordonnancement* new_ordonnancement = malloc(sizeof(T_Ordonnancement));
    new_ordonnancement->date = date();
    new_ordonnancement->listePatients = NULL;
    new_ordonnancement->listeSoigneurs = NULL;
    FILE* instance = NULL;

    int nbPat, nbSoi, pat, idPat, nbRdV, rdv, idSoi, debut, fin, depl, soi;

    instance = fopen(filename,"r");

    fscanf(instance,"%d %d\n", &nbPat, &nbSoi);

    for (pat = 0; pat < nbPat; pat++)
    {
        char* nom_p = malloc(40);
        char* prenom_p = malloc(40);
        T_RendezVous* rdV = (T_RendezVous*)malloc(sizeof(T_RendezVous));
        rdV = NULL;

        fscanf(instance,"%d %d %s %s\n", &idPat, &nbRdV, nom_p, prenom_p);

        for (rdv = 0; rdv < nbRdV; rdv++)
        {
            char *desc = malloc(125);

            fscanf(instance,"%d %d %d %d %s\n", &idSoi, &debut, &fin, &depl, desc);

            if (rdV == NULL)
            {
                rdV = creerListeRendezVous(idSoi, debut, fin, depl, desc);
            }
            else
            {
                rdV = ajouterRendezVous(rdV, idSoi, debut, fin, depl, desc);
            }
        }

        if (new_ordonnancement->listePatients == NULL)
        {
            new_ordonnancement->listePatients = creerListePatient(rdV, idPat, nom_p, prenom_p);
        }
        else
        {
            new_ordonnancement->listePatients = ajouterPatient_avecRDV(new_ordonnancement->listePatients, rdV, idPat, nom_p, prenom_p);
        }
    }
    for(soi = 0; soi < nbSoi; soi++)
    {
        char* nom_s = malloc(40);
        char* prenom_s = malloc(40);

        fscanf(instance,"%d %s %s\n", &idSoi, nom_s, prenom_s);

        if (new_ordonnancement->listeSoigneurs == NULL)
        {
            new_ordonnancement->listeSoigneurs = creerListeSoigneur(idSoi, nom_s, prenom_s);
        }
        else
        {
            new_ordonnancement->listeSoigneurs = ajouterSoigneur(new_ordonnancement->listeSoigneurs, idSoi, nom_s, prenom_s);
        }
    }
    return new_ordonnancement;
}

void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
    T_Intervalle* inter_index = soigneur->listeIntervalle;
    while(inter_index != NULL && (inter_index->debut > rdv->debut_souhaitee || inter_index->fin < rdv->fin_souhaitee))
    {
        inter_index = inter_index->suivant;
    }
    if(inter_index != NULL)
    {
        if(rdv->debut_souhaitee == inter_index->debut && rdv->fin_souhaitee == inter_index->fin)
        {
            if(soigneur->listeIntervalle == inter_index) soigneur->listeIntervalle = inter_index->suivant;
            else
            {
                T_Intervalle* inter_prec = soigneur->listeIntervalle;
                while(inter_prec->suivant != inter_index) inter_prec = inter_prec->suivant;
                inter_prec->suivant = inter_index->suivant;
            }
            free(inter_index);
            rdv->debut_affectee = rdv->debut_souhaitee;
            rdv->fin_affectee = rdv->fin_souhaitee;
        }
        else if(rdv->debut_souhaitee == inter_index->debut)
        {
            inter_index->debut = rdv->fin_souhaitee;
            rdv->debut_affectee = rdv->debut_souhaitee;
            rdv->fin_affectee = rdv->fin_souhaitee;
        }
        else if (rdv->fin_souhaitee == inter_index->fin)
        {
            inter_index->fin = rdv->debut_souhaitee;
            rdv->debut_affectee = rdv->debut_souhaitee;
            rdv->fin_affectee = rdv->fin_souhaitee;
        }
        else
        {
            T_Intervalle* new_inter = malloc(sizeof(T_Intervalle));
            new_inter->debut = rdv->fin_souhaitee;
            new_inter->fin = inter_index->fin;
            new_inter->suivant = inter_index->suivant;
            inter_index->fin = rdv->debut_souhaitee;
            inter_index->suivant = new_inter;
            rdv->debut_affectee = rdv->debut_souhaitee;
            rdv->fin_affectee = rdv->fin_souhaitee;
        }
    }

    else
    {
        inter_index = soigneur->listeIntervalle;
        while((inter_index != NULL) && ((inter_index->fin < rdv->fin_souhaitee) || ((inter_index->fin - inter_index->debut) < (rdv->fin_souhaitee - rdv->debut_souhaitee))))
        {
            inter_index = inter_index->suivant;
        }
        if(inter_index->fin == inter_index->debut + (rdv->fin_souhaitee - rdv->debut_souhaitee))
        {
            T_Intervalle* inter_prec = soigneur->listeIntervalle;
            rdv->debut_affectee = inter_index->debut;
            rdv->fin_affectee = inter_index->fin;

            while(inter_prec->suivant != inter_index) inter_prec = inter_prec->suivant;
            inter_prec->suivant = inter_index->suivant;
            free(inter_index);
        }
        else
        {
        rdv->debut_affectee = inter_index->debut;
        rdv->fin_affectee = (inter_index->debut + (rdv->fin_souhaitee - rdv->debut_souhaitee));
        inter_index->debut = rdv->fin_affectee;
        }
    }
}

Time somme_duree_rdv(T_Patient* patient){
    T_RendezVous* Rdv_index = patient->listeRendezVous;
    int somme = 0;
    while(Rdv_index != NULL)
    {
        somme = somme + (Rdv_index->fin_souhaitee - Rdv_index->debut_souhaitee);
        Rdv_index = Rdv_index->suivant;
    }
    return somme;
}

T_Soigneur* getSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur id_Soi){
    T_Soigneur* soigneur_index = listeSoigneurs;
    while(soigneur_index != NULL && soigneur_index->id_soi != id_Soi)
    {
        soigneur_index = soigneur_index->suivant;
    }
    if(soigneur_index == NULL) return 0;
    else return soigneur_index;
}

void ordonnancer(T_Ordonnancement* solution){
    T_Patient** ptr_liste_triee = &(solution->listePatients);
    MergeSort(ptr_liste_triee);
    T_Patient* liste_triee = *ptr_liste_triee;
    while(liste_triee != NULL)
    {
        T_RendezVous* Rdv_index = liste_triee->listeRendezVous;
        while(Rdv_index != NULL)
        {
            affecterRdV(Rdv_index, getSoigneur(solution->listeSoigneurs, Rdv_index->id_soi));
            Rdv_index = Rdv_index->suivant;
        }
        liste_triee = liste_triee->suivant;
    }
}

void MergeSort(T_Patient** headRef){
    T_Patient* tete = *headRef;
    T_Patient* l1 = NULL;
    T_Patient* l2 = NULL;

    if ((tete == NULL) || (tete->suivant == NULL))
    {
        return;
    }

    FrontBackSplit(tete, &l1, &l2);

    MergeSort(&l1);
    MergeSort(&l2);
    *headRef = SortedMerge(l1, l2);
}

void FrontBackSplit(T_Patient* source, T_Patient** frontRef, T_Patient** backRef){
    T_Patient* end;
    T_Patient* middle;
    middle = source;
    end = source->suivant;

    while (end != NULL)
    {
        end = end->suivant;
        if (end != NULL)
        {
            middle = middle->suivant;
            end = end->suivant;
        }
    }

    *frontRef = source;
    *backRef = middle->suivant;
    middle->suivant = NULL;
}

void ajouterFin(T_Patient** c, T_Patient* elmt){
    T_Patient* new = elmt;
    T_Patient* q;
    new->suivant = NULL;
    if (*c == NULL)*c = new;
    else
    {
        q = *c;
        while (q->suivant != NULL) q = q->suivant;
        q->suivant = new;
    }
}

T_Patient* SortedMerge(T_Patient* l1, T_Patient* l2){
    T_Patient* c = NULL;
    T_Patient* p = l1;
    T_Patient* q = l2;
    while(p && q)
    {
        if(somme_duree_rdv(p) >= somme_duree_rdv(q))
        {
            ajouterFin(&c, p);
            p = p->suivant;
        }
        else
        {
            ajouterFin(&c, q);
            q = q->suivant;
        }
    }
    while(p)
    {
        ajouterFin(&c, p);
        p = p->suivant;
    }
    while(q)
    {
        ajouterFin(&c, q);
        q = q->suivant;
    }
    return c;
}

unsigned int compter_nb_patients(T_Patient* listePatients){
    unsigned int nbr = 0;
    T_Patient* patient_index = listePatients;
    while(patient_index != NULL)
    {
        nbr++;
        patient_index = patient_index->suivant;
    }
    return nbr;
}

void exportSolution(T_Ordonnancement* solution, char* filename){
    //on commence par définir le nom du fichier que l'on va créer
    char* nomfichier = filename;
    strcat(nomfichier, ".");
    strcat(nomfichier, solution->date);
    strcat(nomfichier, ".txt");


    //On commence par récupérer le nombre de Patients et le nombre de soigneurs
    int nbPat=0, nbSoi=0;
    T_Soigneur* soigneurActuel = solution->listeSoigneurs; //pointeur vers le premier soigneur de la liste de soigneurs que contient l'ordonnancement
    T_Patient* patientActuel = solution->listePatients; //pointeur idem avec liste des patients de l'ordonnancement
    while(soigneurActuel != NULL){
        nbSoi++;
        soigneurActuel = soigneurActuel->suivant;
    }

    //ici nbSoi contient le nombre de soigneurs dans la liste

    while(patientActuel !=NULL){
        nbPat++;
        patientActuel = patientActuel->suivant;
    }

    //ici nbPat contient le nombre de Patients dans la liste

    //On peut dores et déjà écrire ces 2 nombres dans le fichier à crée
    //ouverture du fichier en écriture qui créée un fichier dans le dossier où est placé le code
    FILE* newfichier = fopen(nomfichier, "w");

    if(newfichier==NULL) printf("Erreur ouverture fichier");

    fprintf(newfichier, "%d %d\n", nbPat, nbSoi); //ecriture dans le fichier créer

   //On va ensuite écrire les informations de chaque patient:
   int i;
   T_Patient* patienti = solution->listePatients;
   T_RendezVous* rdvi = NULL;
   T_RendezVous* rdvj = NULL;
   int nbRDVPatienti=0;
   for(i=1; i<=nbPat; i++)
    {
        rdvi = patienti->listeRendezVous;
        rdvj = patienti->listeRendezVous;
        nbRDVPatienti=0;
        while(rdvi != NULL){
            nbRDVPatienti++;
            rdvi = rdvi->suivant;
        }
        //ici nbRDVPatienti contient le nb de rdv du ième patient

        fprintf(newfichier, "%d %d\n", patienti->id_pat, nbRDVPatienti); //on affiche id Patient et nb de RDV



        int j;
        for(j=1; j<=nbRDVPatienti; j++){ //cette boucle affiche les infos de chaque rdv du patient

            fprintf(newfichier, "%d %d %d %d\n", rdvj->id_soi, rdvj->debut_affectee, rdvj->fin_affectee, rdvj->temps_deplacement);

            rdvj = rdvj->suivant;
        }
    patienti = patienti->suivant;
   }
   fclose(newfichier);
}

bool exist_fichier(const char *fname){
    FILE * fichier = fopen(fname, "r+");

    if (fichier == NULL)
    {
        return 0;
    }
    else
    {
        fclose(fichier);
        return 1;
    }
}

void liberer_ressources(T_Ordonnancement* ordonnancement){
    T_Soigneur* soigneur_index = ordonnancement->listeSoigneurs;
    while(soigneur_index != NULL)
    {
        liberer_resource_Intervalles(soigneur_index->listeIntervalle);
        soigneur_index = soigneur_index->suivant;
    }

    liberer_resource_Soigneurs(ordonnancement->listeSoigneurs);
    T_Patient* patient_index = ordonnancement->listePatients;
    while(patient_index != NULL)
    {
        liberer_resource_RendezVous(patient_index->listeRendezVous);
        patient_index = patient_index->suivant;
    }
    liberer_resource_Patients(ordonnancement->listePatients);
}

void liberer_resource_Intervalles(T_Intervalle * listeIntervalles){
    T_Intervalle* tmp;
    while(listeIntervalles != NULL)
    {
       tmp = listeIntervalles->suivant;
       free(listeIntervalles);
       listeIntervalles = tmp;
    }
}

void liberer_resource_Soigneurs(T_Soigneur * listeSoigneurs){
    T_Soigneur* tmp;
    while(listeSoigneurs != NULL)
    {
       tmp = listeSoigneurs->suivant;
       free(listeSoigneurs);
       listeSoigneurs = tmp;
    }
}

void liberer_resource_RendezVous(T_RendezVous * listeRendezVous){
    T_RendezVous* tmp;
    while(listeRendezVous != NULL)
    {
       tmp = listeRendezVous->suivant;
       free(listeRendezVous);
       listeRendezVous = tmp;
    }
}

void liberer_resource_Patients(T_Patient * listePatients){
    T_Patient* tmp;
    while(listePatients != NULL)
    {
       tmp = listePatients->suivant;
       free(listePatients);
       listePatients = tmp;
    }
}

void menuPrincipal(void){

    int choix;
    bool continuer = true;
    int instance = 0;
    char filename[125];


    while (continuer == true)
        {
            printf("=================================================================================\n");
            printf("||    Bienvenu au menu principal d'une application d'ordonnancement medicale   ||\n");
            printf("=================================================================================\n");
            printf("||  1. Creer une instance a partir d'un fichier.                               ||\n");
            printf("||  2. Afficher tous les patients et leurs rendez-vous.                        ||\n");
            printf("||  3. Afficher tous les soigneurs et leurs intervalles de temps disponibles.  ||\n");
            printf("||  4. Afficher un rendez-vous en indiquant l'id du patient et du soigneur.    ||\n");
            printf("||  5. Modifier un rendez-vous en indiquant l'id du patient et du soigneur.    ||\n");
            printf("||  6. Supprimer un rendez-vous en indiquant l'id du patient et du soigneur.   ||\n");
            printf("||  7. Ordonnancer.                                                            ||\n");
            printf("||  8. Exporter la solution d'un ordonnancement.                               ||\n");
            printf("||  9. Quitter.                                                                ||\n");
            printf("=================================================================================\n\n");

            scanf("%d", &choix);
            switch (choix){
                case 1:
                    printf("Veuillez choisir un fichier.\n");
                    scanf("%124s", filename);
                    if (!exist_fichier(filename))
                    {
                        printf("Echec de l'importation.\n\n");
                        break;
                    }
                    T_Ordonnancement* new_ordonnancement = creerInstance(filename);
                    printf("Importation reussie ! \n\n");
                    instance = 1;
                    break;

                case 2:
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }
                    else
                    {
                        affichage_Patients(new_ordonnancement->listePatients);
                    }
                    break;

                case 3:
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }
                    else
                    {
                        affichage_Soigneurs(new_ordonnancement->listeSoigneurs);
                    }
                    break;

                case 4:{
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }

                    else
                    {
                        int choix_pat = 0, choix_pat_max = 0, choix_soi_max = 0;
                        printf("Les patients disponibles sont : \n");
                        T_Patient* patient_index = new_ordonnancement->listePatients;
                        while (patient_index != NULL)
                        {
                            printf("ID PAT: %d  ", patient_index->id_pat);
                            choix_pat_max = patient_index->id_pat;
                            patient_index = patient_index->suivant;
                        }
                        printf("\n");
                        scanf("%d", &choix_pat);
                        while(choix_pat < 1 || choix_pat > choix_pat_max)
                        {
                            printf("Veuillez choisir un patient dans la liste.\n");
                            scanf("%d", &choix_pat);
                        }

                        patient_index = new_ordonnancement->listePatients;
                        while(patient_index->id_pat != choix_pat)
                        {
                            patient_index= patient_index->suivant;
                        }

                        int choix_soi = 0;
                        printf("Les soigneurs de ce patient sont : \n");
                        T_RendezVous* Rdv_index = patient_index->listeRendezVous;
                        while (Rdv_index != NULL)
                        {
                            printf("ID SOI: %d  ", Rdv_index->id_soi);
                            choix_soi_max = Rdv_index->id_soi;
                            Rdv_index = Rdv_index->suivant;
                        }
                        printf("\n");
                        scanf("%d", &choix_soi);
                        while(choix_soi < 1 || choix_soi > choix_soi_max)
                        {
                            printf("Veuillez choisir un soigneur dans la liste.\n");
                            scanf("%d", &choix_soi);
                        }

                        Rdv_index = patient_index->listeRendezVous;

                        while (Rdv_index->id_soi != choix_soi)
                        {
                            Rdv_index = Rdv_index->suivant;
                        }

                        affichage_RendezVous(Rdv_index);
                    }

                    break;}


                case 5:{
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }

                    else
                    {
                        int choix_pat = 0, choix_pat_max = 0, choix_soi_max = 0;
                        printf("Les patients disponibles sont : \n");
                        T_Patient* patient_index = new_ordonnancement->listePatients;
                        while (patient_index!= NULL)
                        {
                            printf("ID PAT: %d  ", patient_index->id_pat);
                            choix_pat_max = patient_index->id_pat;
                            patient_index = patient_index->suivant;
                        }
                        printf("\n");
                        scanf("%d", &choix_pat);
                        while(choix_pat < 1 || choix_pat > choix_pat_max)
                        {
                            printf("Veuillez choisir un patient dans la liste.\n");
                            scanf("%d", &choix_pat);
                        }

                        patient_index = new_ordonnancement->listePatients;
                        while(patient_index->id_pat != choix_pat)
                        {
                            patient_index = patient_index->suivant;
                        }

                        int choix_soi = 0;
                        printf("Les soigneurs de ce patient sont : \n");
                        T_RendezVous* Rdv_index = patient_index->listeRendezVous;
                        while (Rdv_index != NULL)
                        {
                            printf("ID SOI: %d  ", Rdv_index->id_soi);
                            choix_soi_max = Rdv_index->id_soi;
                            Rdv_index = Rdv_index->suivant;
                        }

                        printf("\n");
                        scanf("%d", &choix_soi);
                        while(choix_soi < 1 || choix_soi > choix_soi_max)
                        {
                            printf("Veuillez choisir un soigneur dans la liste.\n");
                            scanf("%d", &choix_soi);
                        }

                        Rdv_index = patient_index->listeRendezVous;
                        while (Rdv_index->id_soi != choix_soi)
                        {
                            Rdv_index = Rdv_index->suivant;
                        }

                        printf("1. Modifier date debut\n");
                        printf("2. Modifier date fin\n");
                        printf("3. Modifier description\n");
                        int choix_modif;
                        scanf("%d", &choix_modif);
                        switch(choix_modif){
                            case 1:{
                                int choix_new_dateDebut;
                                printf("Quelle est la nouvelle date de debut du rendez-vous ?\n");
                                printf("Elle doit etre inferieure a la date de fin : %d\n", Rdv_index->fin_souhaitee);
                                scanf("%d", &choix_new_dateDebut);

                                int dateFinPrecedente;
                                T_RendezVous* Rdv_index_prec = patient_index->listeRendezVous;//creation d'un nouvel index pour trouver la date de fin du rdv precedent
                                if(Rdv_index_prec->id_soi == choix_soi) //si le rendrez-vous est le premier rdv du patient
                                    {
                                        dateFinPrecedente = 0;
                                        modifierRendezVous(Rdv_index, Rdv_index->id_soi, choix_new_dateDebut, Rdv_index->fin_souhaitee, 0, Rdv_index->desc);
                                    }
                                else
                                {
                                    while(Rdv_index_prec->suivant->id_soi != choix_soi)
                                    {
                                        Rdv_index_prec = Rdv_index_prec->suivant;
                                    }
                                    dateFinPrecedente = Rdv_index_prec->fin_souhaitee;
                                    modifierRendezVous(Rdv_index, Rdv_index->id_soi, choix_new_dateDebut, Rdv_index->fin_souhaitee, choix_new_dateDebut - dateFinPrecedente, Rdv_index->desc);
                                }
                                break;}
                            case 2:{
                                int choix_new_dateFin = -1;
                                printf("Quelle est la nouvelle datchoix_new_dateDebut - dateFinPrecedentee de fin du rendez-vous ?\n");
                                printf("Elle doit etre superieure a la date de debut : %d\n", Rdv_index->debut_souhaitee);
                                scanf("%d", &choix_new_dateFin);
                                modifierRendezVous(Rdv_index, Rdv_index->id_soi, Rdv_index->debut_souhaitee, choix_new_dateFin, Rdv_index->temps_deplacement, Rdv_index->desc);
                                if(Rdv_index->suivant != NULL)
                                {
                                    Rdv_index = Rdv_index->suivant;
                                    modifierRendezVous(Rdv_index, Rdv_index->id_soi, Rdv_index->debut_souhaitee, Rdv_index->fin_souhaitee, Rdv_index->debut_souhaitee - choix_new_dateFin, Rdv_index->desc);
                                }
                                break;}
                            case 3:
                                {
                                char choix_new_desc[125];
                                printf("Quelle nouvelle description voulez-vous associez ?\n");
                                scanf("%124s", choix_new_desc);
                                modifierRendezVous(Rdv_index, Rdv_index->id_soi, Rdv_index->debut_souhaitee, Rdv_index->fin_souhaitee, Rdv_index->temps_deplacement, choix_new_desc);
                                break;}
                            default:
                                printf("Veuillez saisir une entree valide\n");
                                break;
                            }
                    }
                    break;}

                case 6:
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }

                    else
                    {
                        int choix_pat = 0, choix_pat_max = 0, choix_soi_max = 0;
                        printf("Les patients disponibles sont : \n");
                        T_Patient* patient_index = new_ordonnancement->listePatients;
                        while (patient_index != NULL)
                        {
                            printf("ID PAT: %d  ", patient_index->id_pat);
                            choix_pat_max = patient_index->id_pat;
                            patient_index = patient_index->suivant;
                        }
                        printf("\n");
                        scanf("%d", &choix_pat);
                        while(choix_pat < 1 || choix_pat > choix_pat_max)
                        {
                            printf("Veuillez choisir un patient dans la liste.\n");
                            scanf("%d", &choix_pat);
                        }

                        patient_index = new_ordonnancement->listePatients;
                        while(patient_index->id_pat != choix_pat)
                        {
                            patient_index = patient_index->suivant;
                        }

                        int choix_soi = 0;
                        printf("Les soigneurs disponibles sont : \n");
                        T_RendezVous* soigneur_index = patient_index->listeRendezVous;
                        while (soigneur_index != NULL)
                        {
                            printf("ID SOI: %d  ", soigneur_index->id_soi);
                            choix_soi_max = soigneur_index->id_soi;
                            soigneur_index = soigneur_index->suivant;
                        }

                        printf("\n");
                        scanf("%d", &choix_soi);
                        while(choix_soi < 1 || choix_soi > choix_soi_max)
                        {
                            printf("Veuillez choisir un soigneur dans la liste.\n");
                            scanf("%d", &choix_soi);
                        }

                        patient_index->listeRendezVous = supprimerRendezVous(patient_index->listeRendezVous, choix_soi);
                        printf("Rendez-vous supprime !\n\n");
                    }

                    break;

                case 7:
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }
                    else
                    {
                        ordonnancer(new_ordonnancement);
                        printf("Ordonnancement termine !\n\n");
                    }
                    break;

                case 8:
                    if (instance == 0)
                    {
                        printf("Il n'y a pas d'instance, veuillez en importer une.\n");
                    }
                    else
                    {
                        char nomFichierExport[20];
                        printf("Comment voulez-vous appeler votre fichier?\n");
                        while(getchar()!='\n');
                        scanf("%s", nomFichierExport);
                        printf("export de la solution:\n\n");
                        exportSolution(new_ordonnancement, nomFichierExport);
                        printf("Solution exportee.\n\n");
                    }
                    break;
                case 9:
                    liberer_ressources(new_ordonnancement);
                    continuer = false;
                    break;
                default:
                    printf("Veuillez saisir une entree valide\n");
                    break;

                case 10:
                    ajouterPatient(new_ordonnancement->listePatients, 3, "PEE", "PFF");
                    break;
            }
        }
}


