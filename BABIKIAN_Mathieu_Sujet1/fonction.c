/**
 * \file fonction.c
 * \brief Fichier contenant les fonctions et procédures du premier TP noté - algorithmique procedurale - ING1 GM1A
 * \author Mathieu B.
 * \version 0.3
 * \date 10 décembre 2022
 *
 * Sujet : Prédire le prix d’une habitation qu’on veut mettre en location dans la plateforme Airbnb
 *
*/

/***** les librairies *****/
#include "fonction.h"

/***** fonctions et procédures *****/

/**
 * \fn int trouvNbrLigne(char char_fichier)
 * \brief Fonction pour trouver le nombre de ligne contenu dans le fichier
 * \param pchar_nomFichier La chaîne de caractère contenant le nom du fichier
 * \return Retourne le nombre de ligne
*/
int trouvNbrLigne(char* pchar_nomFichier)
{
    FILE *pfile_fichier = NULL;
    char pchar_chaFichier[256];
    int int_nbrLigneFichier = 0;

    // ouverture en lecture du fichier "airbnb_donnees_propres.csv"
    pfile_fichier = fopen(pchar_nomFichier, "r");

    // si le fichier n'existe pas
    if (pfile_fichier == NULL) 
    {
        printf ("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // on cherche le nombre de ligne contenu dans le fichier "airbnb_donnees_propres.csv"
    while((fgets(pchar_chaFichier, 255, pfile_fichier)) != NULL)
    {
        int_nbrLigneFichier++;
    }

    // fermeture du fichier "airbnb_donnees_propres.csv"
    fclose(pfile_fichier);

    return(int_nbrLigneFichier);
}

/**
 * \fn loge saisieLogeX(loge loge_x)
 * \brief Fonction de recupération des données sur le logement à évaluer
 * \return Retourne le logement avec les données saisies
*/
loge saisieLogeX(void)
{
    loge loge_x;
    do{
        printf("Veuillez saisir le nombre de personne que peut accueillir le logement :\n");
        scanf("%d", &loge_x.int_nbrPers);
    }while(loge_x.int_nbrPers<0);
    do{
        printf("Veuillez saisir le nombre de chambres :\n");
        scanf("%d", &loge_x.int_nbrCham);
    }while(loge_x.int_nbrCham<0);
    do{
        printf("Veuillez saisir le nombre de lits :\n");
        scanf("%d", &loge_x.int_nbrLits);
    }while(loge_x.int_nbrLits<0);
    printf("Récapitulatif : %d personnes, %d chambres, %d lits.\n\n", loge_x.int_nbrPers, loge_x.int_nbrCham, loge_x.int_nbrLits);
    return(loge_x);
}

/**
 * \fn int recupData(loge* loge_y, loge loge_x, char* char_nomFichier)
 * \brief Fonction de recupération des données des logements du fichier et de son nombre de logement,
 * \brief tout en calculant la distance de similarité de chaque logement avec le logement de l'utilisateur
 * \param ploge_y Le tableau de logement du fichier
 * \param loge_x Le logement de l'utilisateur
 * \param pchar_nomFichier La chaîne de caractère contenant le nom du fichier
 * \return Retourne la position dans le fichier
*/
int recupData(loge* ploge_y, loge loge_x, char* pchar_nomFichier)
{
    FILE *pfile_fichier = NULL;
    int int_cptPosition = 0;
    char *pchar_chaLigne;
    int int_cptPositionLigne = 0;
    int int_val;
    char pchar_chaFichier[256];

    // ouverture en lecture du fichier
    pfile_fichier = fopen(pchar_nomFichier, "r");

    // si le fichier n'existe pas
    if (pfile_fichier == NULL) 
    {
        printf ("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // on passe l'entête du fichier 
    fgets(pchar_chaFichier, 255, pfile_fichier);

    // afficher une par une les lignes du fichier 
    while((fgets(pchar_chaFichier, 255, pfile_fichier)) != NULL)
    {
        // on recupère la première valeur
        pchar_chaLigne = strtok(pchar_chaFichier, ",");

        while(pchar_chaLigne != NULL) 
        {
            // on converti les valeurs en entier 
            int_val = atoi(pchar_chaLigne);

            // on rempli le tableau de structure
            switch(int_cptPosition)
            {
                case 0:
                    ploge_y[int_cptPositionLigne].int_id = int_val;
                    break;
                case 1:
                    ploge_y[int_cptPositionLigne].int_nbrPers = int_val;
                    ploge_y[int_cptPositionLigne].tabFloat_dist[0] = abs(int_val - loge_x.int_nbrPers);
                    break;
                case 2:
                    ploge_y[int_cptPositionLigne].int_nbrCham = int_val;
                    ploge_y[int_cptPositionLigne].tabFloat_dist[1] = abs(int_val - loge_x.int_nbrCham);
                    break;
                case 4:
                    ploge_y[int_cptPositionLigne].int_nbrLits = int_val;
                    ploge_y[int_cptPositionLigne].tabFloat_dist[2] = abs(int_val - loge_x.int_nbrLits);
                    break;
                case 5:
                    ploge_y[int_cptPositionLigne].int_prix = int_val;
                    break;
                default :
                    break;
            }
            // on recupère la valeur suivante
            pchar_chaLigne = strtok(NULL, ",");
            int_cptPosition++;
        }
        int_cptPosition = 0;
        int_cptPositionLigne++;
    }

    // on ferme le fichier 
    fclose(pfile_fichier);

    return(int_cptPositionLigne);
}


/**
 * \fn void calcMoyDist(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de calcule de la moyenne des distances
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void calcMoyDist(loge* ploge_y, int int_cptPositionLigne)
{
    int l;

    for(l=0 ; l<int_cptPositionLigne ; l++)
    {
        ploge_y[l].tabFloat_dist[3] = (ploge_y[l].tabFloat_dist[0]+ploge_y[l].tabFloat_dist[1]+ploge_y[l].tabFloat_dist[2])/3;
    }
}

/**
 * \fn void randTabStruct(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure pour randomiser le tableau de structure
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void randTabStruct(loge* ploge_y, int int_cptPositionLigne)
{
    int nbr;
    int i;
    loge tmp;
    srand(time(NULL));
    for(i=0 ; i<int_cptPositionLigne ; i++)
    {
        nbr = rand()% int_cptPositionLigne;

        tmp = ploge_y[i];
        ploge_y[i] = ploge_y[nbr];
        ploge_y[nbr] = tmp;
    }
}

/**
 * \fn void triTabStruct(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de choix de la méthode de tri
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void triTabStruct(loge* ploge_y, int int_cptPositionLigne)
{
    int int_choixTri = -1;

    do {
        printf("Veuillez choisir la méthode de tri :\n   [0] pour trier en fonction du nombre de personne\n");
        printf("   [1] pour trier en fonction du nombre de chambre\n   [2] pour trier en fonction du nombre de lit\n");
        printf("   [3] pour trier en fonction des trois critères\n");
        scanf("%d", &int_choixTri);
        printf("\n");
    } while(int_choixTri<0 || int_choixTri>3);

    switch(int_choixTri)
    {
        case 0:
            triTabStructPers(ploge_y, int_cptPositionLigne);
            break;
        case 1:
            triTabStructCham(ploge_y, int_cptPositionLigne);
            break;
        case 2:
            triTabStructLits(ploge_y, int_cptPositionLigne);
            break;
        default :
            triTabStructMoye(ploge_y, int_cptPositionLigne);
            break;
    }
}

/**
 * \fn void triTabStructPers(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de tri du tableau de structure, en fonction de la distance associée au nombre de personne
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void triTabStructPers(loge* ploge_y, int int_cptPositionLigne)
{
    loge e;
    int j;
    int k;
    for(j=0 ; j<int_cptPositionLigne ; j++)
    {
        e = ploge_y[j];
        for(k=j ; k>0 && ploge_y[k-1].tabFloat_dist[0]>e.tabFloat_dist[0]; k--)
        {
            ploge_y[k]= ploge_y[k-1];
        }
        ploge_y[k] = e;
    }
}

/**
 * \fn void triTabStructCham(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de tri du tableau de structure, en fonction de la distance associée au nombre de chambre
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void triTabStructCham(loge* ploge_y, int int_cptPositionLigne)
{
    loge e;
    int j;
    int k;
    for(j=0 ; j<int_cptPositionLigne ; j++)
    {
        e = ploge_y[j];
        for(k=j ; k>0 && ploge_y[k-1].tabFloat_dist[1]>e.tabFloat_dist[1]; k--)
        {
            ploge_y[k]= ploge_y[k-1];
        }
        ploge_y[k] = e;
    }
}

/**
 * \fn void triTabStructLits(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de tri du tableau de structure, en fonction de la distance associée au nombre de lit
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void triTabStructLits(loge* ploge_y, int int_cptPositionLigne)
{
    loge e;
    int j;
    int k;
    for(j=0 ; j<int_cptPositionLigne ; j++)
    {
        e = ploge_y[j];
        for(k=j ; k>0 && ploge_y[k-1].tabFloat_dist[2]>e.tabFloat_dist[2]; k--)
        {
            ploge_y[k]= ploge_y[k-1];
        }
        ploge_y[k] = e;
    }
}

/**
 * \fn void triTabStructMoye(loge* ploge_y, int int_cptPositionLigne)
 * \brief Procédure de tri du tableau de structure, en fonction de la moyenne des distances
 * \param ploge_y Le tableau de logement du fichier
 * \param int_cptPositionLigne La position dans le fichier
*/
void triTabStructMoye(loge* ploge_y, int int_cptPositionLigne)
{
    loge e;
    int j;
    int k;
    for(j=0 ; j<int_cptPositionLigne ; j++)
    {
        e = ploge_y[j];
        for(k=j ; k>0 && ploge_y[k-1].tabFloat_dist[3]>e.tabFloat_dist[3]; k--)
        {
            ploge_y[k]= ploge_y[k-1];
        }
        ploge_y[k] = e;
    }
}

/**
 * \fn int saisieKPrem(int int_nbrLigneFichier)
 * \brief Fonction de saisie des k premiers logement à utiliser
 * \return Retourne le nombre de logement à utiliser pour l'évaluation
 * \param int_nbrLigneFichier Le nombre de ligne dans le fichier
*/
int saisieKPrem(int int_nbrLigneFichier)
{
    int int_kPrem;
    do {
        printf("Saisir les k premiers logements du tableau qui seront pris en compte :\n(Le maximum étant le nombre de logement dans la base : %d)\n", int_nbrLigneFichier);
        scanf("%d", &int_kPrem);
    } while(int_kPrem <= 0 || int_kPrem > int_nbrLigneFichier);
    printf("\n");
    return(int_kPrem);
}

/**
 * \fn loge calcPrixMoy(loge* ploge_y, loge loge_x, int int_kPrem)
 * \brief Fonction de calcul du prix du logement de l'utilisateur
 * \return Retourne le logement de l'utilisateur avec l'estimation de son prix
 * \param ploge_y Le tableau de logement du fichier
 * \param loge_x Le logement de l'utilisateur
 * \param int_kPrem Le nombre de logement avec lesquels comparer le logement de l'utilisateur
*/
loge calcPrixMoy(loge* ploge_y, loge loge_x, int int_kPrem)
{
    int m;
    for(m=0 ; m<int_kPrem ; m++)
    {
        loge_x.int_prix = loge_x.int_prix + ploge_y[m].int_prix;
    }
    loge_x.int_prix = loge_x.int_prix/int_kPrem;
    return(loge_x);
}

/**
 * \fn void affichageLogeX(loge loge_x, int int_kPrem)
 * \brief Procédure d'affichage des données du logement saisie
 * \param loge_x Le logement de l'utilisateur
 * \param int_kPrem Le nombre de logement avec lesquels comparer le logement de l'utilisateur
*/
void affichageLogeX(loge loge_x, int int_kPrem)
{
    printf("A partir des caractéristiques saisient : %d personnes, %d chambres, %d lits.\n", loge_x.int_nbrPers, loge_x.int_nbrCham, loge_x.int_nbrLits);
    printf("Suite à une étude comparative effectuée sur %d logements similaires.\n", int_kPrem);
    printf("Votre logement est évalué à %d € la nuit.\n", loge_x.int_prix);
}

/**
 * \fn void choixSujet(void)
 * \brief Procédure de choix du sujet
*/
void choixSujet(void)
{
    int int_choix = -1;

    do {
        printf("Veuillez choisir le sujet :\n   [1] Sujet 1\n   [2] Sujet 1 Bonus\n");
        scanf("%d", &int_choix);
        printf("\n");
    } while(int_choix!=1 && int_choix!=2);

    switch(int_choix)
    {
        case 1:
            Sujet1();
            break;
        default :
            Sujet1Bonus();
            break;
    }
}

/**
 * \fn void Sujet1(void)
 * \brief Procédure d'exécution du sujet 1
*/
void Sujet1(void)
{
    // on cherche le nombre de ligne
    int int_nbrLigneFichier = trouvNbrLigne("airbnb_donnees_propres.csv");

    // on demande les informations sur le logement de l'utilisateur
    loge loge_x = saisieLogeX();

    // allocation dynamique de l'espace pour le tableau de loge
    loge* ploge_y = (loge*)malloc(int_nbrLigneFichier*sizeof(loge));

    // si l'espace pour le tableau de loge n'a pas été alloué
    if (ploge_y == NULL) 
    {
        fprintf(stderr, "Erreur allocation memoire\n");
        exit(1);
    }
    // on recupère les données des logements
    int int_cptPositionLigne = recupData(ploge_y, loge_x, "airbnb_donnees_propres.csv"); 

    // on calcule les distances moyennes
    calcMoyDist(ploge_y, int_cptPositionLigne); 

    // on randomise le tableau de logement 
    randTabStruct(ploge_y, int_cptPositionLigne); 

    // on demande la méthode de tri et on l'effectue sur le tableau de logement  
    triTabStruct(ploge_y, int_cptPositionLigne);
    
    // on demande le nombre de logement avec lesquels comparer le logement de l'utilisateur
    int int_kPrem = saisieKPrem(int_nbrLigneFichier);

    // on calcule le prix moyen du logement de l'utilisateur
    loge_x = calcPrixMoy(ploge_y, loge_x, int_kPrem);

    // on affiche les données et l'évaluation du prix du logement de l'utilisateur
    affichageLogeX(loge_x, int_kPrem);

    // on libère l'espace
    free(ploge_y);
}

/**
 * \fn void Sujet1Bonus(void)
 * \brief Procédure d'exécution du bonus du sujet 1
*/
void Sujet1Bonus(void)
{
    // on cherche le nombre de ligne des deux fichiers
    int int_nbrLigneEntrainement = trouvNbrLigne("airbnbEntrainement.csv");
    int int_nbrLigneTest = trouvNbrLigne("airbnbTest.csv");

    // allocation dynamique de l'espace pour les tableaux de loge
    loge* ploge_entr = (loge*)malloc(int_nbrLigneEntrainement*sizeof(loge));
    loge* ploge_test = (loge*)malloc(int_nbrLigneTest*sizeof(loge));
    int* pint_prix = (int*)malloc(int_nbrLigneTest*sizeof(int));
    int* pint_pred = (int*)malloc(int_nbrLigneTest*sizeof(int));

    // si l'espace pour les tableaux de loge n'a pas été alloué
    if (ploge_entr == NULL || ploge_test == NULL || pint_pred == NULL || pint_prix == NULL) 
    {
        fprintf(stderr, "Erreur allocation memoire\n");
        exit(2);
    }

    printf("Calcul des MAE en cours, cela peut prendre un certain temps...\nMerci de votre compréhension.\n\n");

    recupDataNoComparaison(ploge_test, "airbnbTest.csv"); // on recupère les données des logements test

    int int_cptPositionLigne;
    int int_kPrem;
    int int_MAE_Moye = 0;
    int int_MAE_Pers = 0;
    int int_MAE_Cham = 0;
    int int_MAE_Lits = 0;

    for(int i=0 ; i<int_nbrLigneTest ; i++) // pour tous les logements test
    {
        pint_prix[i] = ploge_test[i].int_prix;

        int_cptPositionLigne = recupData(ploge_entr, ploge_test[i], "airbnbEntrainement.csv"); // on recupère les données des logements entrainement

        calcMoyDist(ploge_entr, int_cptPositionLigne); // on calcule les distances moyennes

        randTabStruct(ploge_entr, int_cptPositionLigne); // on randomise le tableau de logement entrainement
        triTabStructMoye(ploge_entr, int_cptPositionLigne); // on trie le tableau de logement entrainement en fonction de tous les critères
        ploge_test[i] = calcPrixMoy(ploge_entr, ploge_test[i], 10); // on calcule le prix du logement test moyen en fonction des 10 premiers logements
        pint_pred[i] = ploge_test[i].int_prix; 
        int_MAE_Moye = int_MAE_Moye + abs(pint_pred[i]-pint_prix[i]); // on "pré-calcule" la MAE

        // on fait de même pour le critère du nombre de personne
        randTabStruct(ploge_entr, int_cptPositionLigne);
        triTabStructPers(ploge_entr, int_cptPositionLigne);
        ploge_test[i] = calcPrixMoy(ploge_entr, ploge_test[i], 10);
        pint_pred[i] = ploge_test[i].int_prix;
        int_MAE_Pers = int_MAE_Pers + abs(pint_pred[i]-pint_prix[i]);

        // on fait de même pour le critère du nombre de chambre
        randTabStruct(ploge_entr, int_cptPositionLigne);
        triTabStructCham(ploge_entr, int_cptPositionLigne);
        ploge_test[i] = calcPrixMoy(ploge_entr, ploge_test[i], 10);
        pint_pred[i] = ploge_test[i].int_prix;
        int_MAE_Cham = int_MAE_Cham + abs(pint_pred[i]-pint_prix[i]);

        // on fait de même pour le critère du nombre de lit
        randTabStruct(ploge_entr, int_cptPositionLigne);
        triTabStructLits(ploge_entr, int_cptPositionLigne);
        ploge_test[i] = calcPrixMoy(ploge_entr, ploge_test[i], 10);
        pint_pred[i] = ploge_test[i].int_prix;
        int_MAE_Lits = int_MAE_Lits + abs(pint_pred[i]-pint_prix[i]);
    }

    // on calcule les MAE
    int_MAE_Moye = int_MAE_Moye/int_nbrLigneTest;
    int_MAE_Pers = int_MAE_Pers/int_nbrLigneTest;
    int_MAE_Cham = int_MAE_Cham/int_nbrLigneTest;
    int_MAE_Lits = int_MAE_Lits/int_nbrLigneTest;

    // on affiche les MAE
    afficherMAE(int_MAE_Moye, int_MAE_Pers, int_MAE_Cham, int_MAE_Lits);

    // on libère l'espace
    free(ploge_entr); 
    free(ploge_test);
    free(pint_prix);
    free(pint_pred);      
}

/**
 * \fn void recupDataNoComparaison(loge* ploge_y, char* pchar_nomFichier)
 * \brief Procédure de recupération des données des logements du fichier
 * \param ploge_y Le tableau de logement du fichier 
 * \param pchar_nomFichier La chaîne de caractère contenant le nom du fichier
*/
void recupDataNoComparaison(loge* ploge_y, char* pchar_nomFichier)
{
    FILE *pfile_fichier = NULL;
    int int_cptPosition = 0;
    char *pchar_chaLigne;
    int int_cptPositionLigne = 0;
    int int_val;
    char pchar_chaFichier[256];

    // ouverture en lecture du fichier
    pfile_fichier = fopen(pchar_nomFichier, "r");

    // si le fichier n'existe pas
    if (pfile_fichier == NULL) 
    {
        printf ("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // on passe l'entête du fichier
    fgets(pchar_chaFichier, 255, pfile_fichier);

    // afficher une par une les lignes du fichier 
    while((fgets(pchar_chaFichier, 255, pfile_fichier)) != NULL)
    {
        // on recupère la première valeur
        pchar_chaLigne = strtok(pchar_chaFichier, ",");

        while(pchar_chaLigne != NULL) 
        {
            // on converti les valeurs en entier 
            int_val = atoi(pchar_chaLigne);

            // on rempli le tableau de structure
            switch(int_cptPosition)
            {
                case 0:
                    ploge_y[int_cptPositionLigne].int_id = int_val;
                    break;
                case 1:
                    ploge_y[int_cptPositionLigne].int_nbrPers = int_val;
                    break;
                case 2:
                    ploge_y[int_cptPositionLigne].int_nbrCham = int_val;
                    break;
                case 4:
                    ploge_y[int_cptPositionLigne].int_nbrLits = int_val;
                    break;
                case 5:
                    ploge_y[int_cptPositionLigne].int_prix = int_val;
                    break;
                default :
                    break;
            }
            // on recupère la valeur suivante
            pchar_chaLigne = strtok(NULL, ",");
            int_cptPosition++;
        }
        int_cptPosition = 0;
        int_cptPositionLigne++;
    }

    // on ferme le fichier
    fclose(pfile_fichier);
}

/**
 * \fn int calcMAE(int* pint_pred, int* pint_prix, int int_nbrLigneTest)
 * \brief Fonction de calcul de la MAE
 * \param pint_pred Le prix prédit
 * \param pint_prix Le prix donné
 * \param int_nbrLigneTest Le nombre de ligne dans le fichier
 * \return la valeur de la MAE
*/
int calcMAE(int* pint_pred, int* pint_prix, int int_nbrLigneTest)
{
    int int_MAE = 0;

    for(int i=0 ; i<int_nbrLigneTest ; i++)
    {
        int_MAE = int_MAE + abs(pint_pred[i]-pint_prix[i]);
    }

    int_MAE = int_MAE/int_nbrLigneTest;
}

/**
 * \fn void afficherMAE(int int_MAE_Moye, int int_MAE_Pers, int int_MAE_Cham, int int_MAE_Lits)
 * \brief Procédure pour afficher les 4 MAE en fonction des critères de calcul des distances
 * \param int_intMAE_Moye La valeur de la MAE en fonction de tous les critères
 * \param int_intMAE_Pers La valeur de la MAE en fonction du critère du nombre de personne
 * \param int_intMAE_Cham La valeur de la MAE en fonction du critère du nombre de chambre
 * \param int_intMAE_Lits La valeur de la MAE en fonction du critère du nombre de lit 
*/
void afficherMAE(int int_MAE_Moye, int int_MAE_Pers, int int_MAE_Cham, int int_MAE_Lits)
{
    printf("LA MAE selon la moyenne des critères vaut : %d\n", int_MAE_Moye);
    printf("LA MAE selon le nombre de personne vaut : %d\n", int_MAE_Pers);
    printf("LA MAE selon le nombre de chambre vaut : %d\n", int_MAE_Cham);
    printf("LA MAE selon le nombre de lit vaut : %d\n", int_MAE_Lits);
}