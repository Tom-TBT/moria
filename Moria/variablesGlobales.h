/* 
 * File:   variablesGlobales.h
 * Author: tom
 *
 * Created on 24 février 2015, 18:08
 */

#ifndef VARIABLESGLOBALES_H
#define	VARIABLESGLOBALES_H

    #include "constantesGlobales.h"
    #include "constantesEcran.h"
    #include "structPersonnages.h"

    /* Definitions des cartes du jeu*/
    extern int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR];
    extern int cartePersonnages[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    extern int carteObjets[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    extern int carteOdeurs[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    
    extern struct Heros heros;
    extern struct Monstre* teteListeMonstre;
    
    extern int nivSuivant[NB_NIVEAUX];

#endif	/* VARIABLESGLOBALES_H */

