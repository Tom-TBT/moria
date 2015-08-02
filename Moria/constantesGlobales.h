/* 
 * File:   constantesGlobales.h
 * Author: tom
 *
 * Created on 24 février 2015, 17:05
 */

#ifndef CONSTANTESGLOBALES_H
#define	CONSTANTESGLOBALES_H 
    
    /* liste des élements */enum {RIEN, MUR, ESCALIER, EAU, ARGENT, 
                                       ANNEAU, ARME, ARMURE, BAGUETTE, PARCHEMIN, 
                                       POTION, RATION, HEROS, RAT};
    #define NB_TYPES_OBJETS 12
    #define NB_TYPES_PERSONNES NB_TYPES_OBJETS+2
    /* liste direction */enum {HAUT, BAS, GAUCHE, DROITE, DESCENDRE};
                         
    /* liste murs */enum {MUR_D, MUR_G, MUR_B, MUR_H, MUR_DB, MUR_GB, MUR_GH, 
                    MUR_DH, MUR_DGB, MUR_GBH, MUR_DGH, MUR_DBH, MUR_DG, MUR_BH, 
                    MUR_S};

    /* taille message info*/
    #define TAILLE_MESSAGE 56  
                  
    /* Nombre de niveaux possibles (-1)*/
    #define NB_NIVEAUX 6
#endif	/* CONSTANTESGLOBALES_H */

