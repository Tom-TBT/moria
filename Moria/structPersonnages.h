/* 
 * File:   structPerso.h
 * Author: tom
 *
 * Created on 1 août 2015, 11:46
 */

#ifndef STRUCTPERSO_H
#define	STRUCTPERSO_H

    struct Heros{int x; int y; int cash; int odeur; int force; int vie; 
        int vieMax; int armure; int niveau; int etage; int faim; int soif;
        int agilite; int experience; int precision;}Heros;
    
    struct Monstre{int id; int type; int x; int y; int cap; struct Monstre* suiv;
        int vie; int force; int armure; int agilite; int valeur;
        int odorat; int precision;};

#endif	/* STRUCTPERSO_H */

