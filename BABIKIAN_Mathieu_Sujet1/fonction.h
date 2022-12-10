#ifndef FONCTION_H
#define FONCTION_H

/***** les librairies *****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fonction.h"

/***** les structures *****/
/**
 * \struct loge
 * \brief structure de description d'un logement Airbnb
 * 
 * Il contient le nom ;
 * 3 caractéristiques : le nombre de personne recevable, le nombre de chambre, le nombre de lits ;
 * un tableau de distance de similarité pour chaque caractéristiques.
 *
*/
typedef struct 
{
    int int_id;
    int int_nbrPers;
    int int_nbrCham;
    int int_nbrLits;
    int int_prix;
    float tabFloat_dist[3]; 
    // 0 pour la distance associée au nombre de personne
    // 1 pour la distance associée au nombre de chambre 
    // 2 pour la distance associée au nombre de lit 
    // 3 pour la moyenne des 3 distances
}loge;

/***** les prototypes *****/
int trouvNbrLigne(char* pchar_nomFichier);
loge saisieLogeX(void);
int recupData(loge* loge_y, loge loge_x, char* pchar_nomFichier);
void calcMoyDist(loge* ploge_y, int int_cptPositionLigne);
void randTabStruct(loge* ploge_y, int int_cptPositionLigne);
void triTabStruct(loge* ploge_y, int int_cptPositionLigne);
void triTabStructPers(loge* ploge_y, int int_cptPositionLigne);
void triTabStructCham(loge* ploge_y, int int_cptPositionLigne);
void triTabStructLits(loge* ploge_y, int int_cptPositionLigne);
void triTabStructMoye(loge* ploge_y, int int_cptPositionLigne);
int saisieKPrem(int int_nbrLigneFichier);
loge calcPrixMoy(loge* ploge_y, loge loge_x, int int_kPrem);
void affichageLogeX(loge loge_x, int int_kPrem);
void choixSujet(void);
void Sujet1(void);
void Sujet1Bonus(void);
void recupDataNoComparaison(loge* loge_y, char* pchar_nomFichier);
int calcMAE(int* pint_pred, int* pint_prix, int int_nbrLigneTest);
void afficherMAE(int int_MAE_Moye, int int_MAE_Pers, int int_MAE_Cham, int int_MAE_Lits);

#endif // FONCTION_H_INCLUDED