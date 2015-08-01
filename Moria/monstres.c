/* 
 * File:   monstres.c
 * Author: tom
 *
 * Created on 24 février 2015, 16:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "variablesGlobales.h"
#include "structPersonnages.h"

    int distribId = 1;

void deplacementsMonstres(){
    /*deplacement selon odeur*/
    int maxOdeur, odeurX, odeurY;
    /*deplacement aleatoire*/
    int direction,aBouge;
    
    struct Monstre* monstreCourant;

    if(teteListeMonstre != NULL){
        monstreCourant = teteListeMonstre;
        
        while(monstreCourant != NULL){            
            maxOdeur = carteOdeurs[monstreCourant->y+1][monstreCourant->x];
            odeurX = monstreCourant->x;
            odeurY = monstreCourant->y+1;
            if(carteOdeurs[monstreCourant->y-1][monstreCourant->x] > maxOdeur){
                maxOdeur = carteOdeurs[monstreCourant->y-1][monstreCourant->x];
                odeurX = monstreCourant->x;
                odeurY = monstreCourant->y-1;
            }
            if(carteOdeurs[monstreCourant->y][monstreCourant->x+1] > maxOdeur){
                maxOdeur = carteOdeurs[monstreCourant->y][monstreCourant->x+1];
                odeurX = monstreCourant->x+1;
                odeurY = monstreCourant->y;
            }
            if(carteOdeurs[monstreCourant->y][monstreCourant->x-1] > maxOdeur){
                maxOdeur = carteOdeurs[monstreCourant->y][monstreCourant->x-1];
                odeurX = monstreCourant->x-1;
                odeurY = monstreCourant->y;
            }
            if(maxOdeur > 10 - monstreCourant->odorat){
                if(cartePersonnages[odeurY][odeurX] < PERSONNAGE){
                    cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                    cartePersonnages[odeurY][odeurX] = monstreCourant->type;
                    monstreCourant->x = odeurX;
                    monstreCourant->y = odeurY;   
                }
            }
            else{
                aBouge = 0;
                while(!aBouge){
                    direction = rand() % 4;
                    switch (direction){
                        case HAUT:
                            if(cartePersonnages[monstreCourant->y-1][monstreCourant->x] != MUR && (monstreCourant->cap != BAS || (cartePersonnages[monstreCourant->y+1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x-1] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x+1] == MUR))){
                                cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                                cartePersonnages[monstreCourant->y-1][monstreCourant->x] = monstreCourant->type;
                                monstreCourant->y--;
                                monstreCourant->cap = HAUT;
                                aBouge = 1;
                            }
                            break;
                        case BAS:
                            if(cartePersonnages[monstreCourant->y+1][monstreCourant->x] != MUR && (monstreCourant->cap != HAUT || (cartePersonnages[monstreCourant->y-1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x-1] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x+1] == MUR))){
                                cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                                cartePersonnages[monstreCourant->y+1][monstreCourant->x] = monstreCourant->type;
                                monstreCourant->y++;
                                monstreCourant->cap = BAS;
                                aBouge = 1;
                            }
                            break;
                        case GAUCHE:
                            if(cartePersonnages[monstreCourant->y][monstreCourant->x-1] != MUR && (monstreCourant->cap != DROITE || (cartePersonnages[monstreCourant->y+1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y-1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x+1] == MUR))){
                                cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                                cartePersonnages[monstreCourant->y][monstreCourant->x-1] = monstreCourant->type;
                                monstreCourant->x--;
                                monstreCourant->cap = GAUCHE;
                                aBouge = 1;
                            }
                            break;
                        case DROITE:
                            if(cartePersonnages[monstreCourant->y][monstreCourant->x+1] != MUR && (monstreCourant->cap != GAUCHE || (cartePersonnages[monstreCourant->y+1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y-1][monstreCourant->x] == MUR && cartePersonnages[monstreCourant->y][monstreCourant->x-1] == MUR))){
                                cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                                cartePersonnages[monstreCourant->y][monstreCourant->x+1] = monstreCourant->type;
                                monstreCourant->x++;
                                monstreCourant->cap = DROITE;
                                aBouge = 1;
                            }
                            break;
                    }
                }
            }
            /* On passe au monstre suivant */
            monstreCourant = monstreCourant->suiv;
        }
    }
    
    
}

void initialiserMonstre(struct Monstre* monstreCourant){
    monstreCourant->id = distribId++;
    switch(monstreCourant->type){
        case RAT:
            monstreCourant->force = 1;
            monstreCourant->armure = 0;
            monstreCourant->agilite = 1;
            monstreCourant->precision = 50;
            monstreCourant->valeur = rand()%2 + 1;
            monstreCourant->vie = rand()%1 + 5;
            monstreCourant->odorat = 10;
            break;
    }
}

void ajouterMonstre(int typeMonstre, int x, int y){
    struct Monstre* monstreCourant = teteListeMonstre;
    
    if(teteListeMonstre == NULL){
        teteListeMonstre = (struct Monstre*)malloc(sizeof(struct Monstre));
        
        teteListeMonstre->x = x;
        teteListeMonstre->y = y;
        teteListeMonstre->cap = 5;
        teteListeMonstre->suiv = NULL;
        teteListeMonstre->type = typeMonstre;
        initialiserMonstre(teteListeMonstre);
    }
    else{
        while(monstreCourant->suiv != NULL){
            monstreCourant = monstreCourant->suiv;
        }
        monstreCourant->suiv = (struct Monstre*) malloc(sizeof(struct Monstre));
        monstreCourant = monstreCourant->suiv;
        monstreCourant->type = typeMonstre;
        monstreCourant->suiv = NULL;
        monstreCourant->x = x;
        monstreCourant->cap = 5;
        monstreCourant->y = y;
        initialiserMonstre(monstreCourant);
    }
}

void retirerMonstre(int id) {
    struct Monstre* monstreCourant;
    struct Monstre* monstrePrecedant;
    monstreCourant = teteListeMonstre;
    if(monstreCourant->id == id) {
        teteListeMonstre = monstreCourant->suiv;
        cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
        free(monstreCourant);
    }
    else {
        monstrePrecedant = monstreCourant;
        monstreCourant = monstrePrecedant->suiv;
        while(monstreCourant != NULL) {  
            if(monstreCourant->id == id) {
                monstrePrecedant->suiv = monstreCourant->suiv;
                cartePersonnages[monstreCourant->y][monstreCourant->x] = RIEN;
                free(monstreCourant);
                break;
            }
            monstrePrecedant = monstreCourant;
            monstreCourant = monstrePrecedant->suiv;
        }
    }
    
}

void spawnMonstres(){
    int xMonst, yMonst;
    int nonPlace = 1;
    
    if(rand()%10 == 0){
        while(nonPlace){
            xMonst = (rand() % (NB_CASES_LARGEUR-4)) + 1;
            yMonst = (rand() % (NB_CASES_HAUTEUR-4)) + 1;
            if(cartePersonnages[yMonst][xMonst] == RIEN && ((yMonst >= heros.y+10 || yMonst <= heros.y-10)&&(xMonst >= heros.x+10 || xMonst <= heros.x-10))){
                cartePersonnages[yMonst][xMonst] = RAT;
                ajouterMonstre(RAT,xMonst,yMonst);
                nonPlace = 0;
            }
        }
    }
    
}

struct Monstre* getMonstre(int xMonstre, int yMonstre) {
    struct Monstre* monstreCourant = teteListeMonstre;
    while(monstreCourant != NULL) {
        if(monstreCourant->x == xMonstre && monstreCourant->y == yMonstre) {
            break;
        }
        monstreCourant = monstreCourant->suiv;
    }
    return monstreCourant;
}

void actionMonstres(){
    spawnMonstres();
    deplacementsMonstres();
}

void libererMonstres(){
    struct Monstre *monstrePrecedant = teteListeMonstre;
    struct Monstre *monstreSuivant;
    
    if(monstrePrecedant != NULL){
        if(monstrePrecedant->suiv != NULL){
            monstreSuivant = monstrePrecedant->suiv;
            while(monstreSuivant != NULL){
                free(monstrePrecedant);
                monstrePrecedant = monstreSuivant;
                monstreSuivant = monstreSuivant->suiv;
            }
            free(monstrePrecedant);
        }
        else{
            free(monstrePrecedant);
        }
    }
    teteListeMonstre = NULL;
}
