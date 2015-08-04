/*
heros.c
-----

Rôle : contient des fonction gérant le héros

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "variablesGlobales.h"

void passageNiveau(){
    heros.niveau++;
    heros.vieMax += (heros.niveau - 1) + (rand() % heros.niveau);
    heros.vie = heros.vieMax;
    
    // Inventer d'autres règles
}

void diffuserOdeur(int portee, int x, int y){
    if(portee != 1){
        if(carteObjets[y-1][x] != MUR && carteOdeurs[y-1][x] < portee){
            diffuserOdeur((portee-1),x,(y-1));
        }
        if(carteObjets[y+1][x] != MUR && carteOdeurs[y+1][x] < portee){
            diffuserOdeur((portee-1),x,(y+1));
        }
        if(carteObjets[y][x-1] != MUR && carteOdeurs[y][x-1] < portee){
            diffuserOdeur((portee-1),(x-1),y);
        }
        if(carteObjets[y][x+1] != MUR && carteOdeurs[y][x+1] < portee){
            diffuserOdeur((portee-1),(x+1),y);
        }
    }
    if(carteOdeurs[y][x] < portee){
        carteOdeurs[y][x] = portee;
    }
}

void deplacerOdeur(){
    int i,j;
    
    for(i = 0 ; i < NB_CASES_LARGEUR ; i++)
    {
        for(j = 0 ; j < NB_CASES_HAUTEUR ; j++)
        {
            carteOdeurs[j][i] = 0;
        }
    }
    diffuserOdeur(heros.odeur, heros.x, heros.y);
}

int deplacerJoueur(int direction){
    switch(direction){
        case HAUT:
            if(cartePersonnages[heros.y-1][heros.x] == MUR)
                return 1;
            else if(cartePersonnages[heros.y-1][heros.x] > HEROS){
                // Si c'est un monstre car après personnage c'est des monstres
                frappeMonstre(heros.y-1,heros.x);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y-1][heros.x] = HEROS;
                heros.y--;
            }
            break;
        case BAS:
            if(cartePersonnages[heros.y+1][heros.x] == MUR)
                return 1;
            else if(cartePersonnages[heros.y+1][heros.x] > HEROS){
                // Si c'est un monstre
                frappeMonstre(heros.y+1,heros.x);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y+1][heros.x] = HEROS;
                heros.y++;
            }
            break;
        case GAUCHE:
            if(cartePersonnages[heros.y][heros.x-1] == MUR)
                return 1;
            else if(cartePersonnages[heros.y][heros.x-1] > HEROS){
                // Si c'est un monstre
                frappeMonstre(heros.y,heros.x-1);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y][heros.x-1] = HEROS;
                heros.x--;
            }
            break;
        case DROITE:
            if(cartePersonnages[heros.y][heros.x+1] == MUR)
                return 1;
            else if(cartePersonnages[heros.y][heros.x+1] > HEROS){
                // Si c'est un monstre
                frappeMonstre(heros.y,heros.x+1);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y][heros.x+1] = HEROS;
                heros.x++;
            }
            break;
        case DESCENDRE:
            if(carteObjets[heros.y][heros.x] != ESCALIER){
                return 1;
            }
            break;
    }
    
    return 0;
}

void initialiserHeros() {
    heros.odeur = 10;
    heros.cash = 0;
    heros.vieMax = heros.vie = 6;
    heros.armure = 0;
    heros.force = 2;
    heros.niveau = 1;
    heros.etage = 1;
    heros.faim = 60;
    heros.soif = 40;
    heros.agilite = 2;
    heros.precision = 75;
    
    int i;
    for(i = 0; i < TAILLE_EQUIP; i++) {
        heros.equipements[i] = NULL;
    }
    heros.sac = NULL;

    ajoutInventaire(RATION_ALIMENTAIRE);
    ajoutInventaire(EPEE_FER);
    ajoutInventaire(EPEE_ACIER);
    
    distribObjId();    
    
    equiperObjet('c');
}
