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
    #include <SDL/SDL_ttf.h>
    #include "structPersonnages.h"

    /* Variables globales du projet*/
    extern SDL_Surface *ecran; // Ecran de jeu
    extern TTF_Font *policeMessage, *policeStatus;

    /* Definitions des cartes du jeu*/
    extern int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR];
    extern int cartePersonnages[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    extern int carteObjets[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    extern int carteOdeurs[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
    
    extern struct Heros heros;
    extern struct Monstre* teteListeMonstre;

    /* Surfaces SDL à charger : Murs, objets et personnages*/
    extern SDL_Surface *imgMur[15];
    extern SDL_Surface *imgAnneau, *imgArgent, *imgArme, *imgArmure, 
            *imgBaguette, *imgEau, *imgEscalier, *imgParchemin, *imgPotion, 
            *imgRation;
    extern SDL_Surface *imgHeros, *imgRat;


#endif	/* VARIABLESGLOBALES_H */

