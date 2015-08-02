/*
gestionPartie.c
-----

Rôle : contient des fonction gérant le jeu

*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "variablesGlobales.h"

struct Heros heros;

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

void initialiserJeu(){
    heros.odeur = 10;
    heros.cash = 0;
    heros.vie = 6;
    heros.armure = 0;
    heros.force = 2;
    heros.niveau = 1;
    heros.etage = 1;
    heros.faim = 60;
    heros.soif = 40;
    heros.agilite = 2;
    heros.precision = 75;
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

void attendreCommande(int* signal){
    SDL_Event event;
    int deplacementImpossible;
    
    do{
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *signal = 1;
                deplacementImpossible = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        *signal = 1;
                        deplacementImpossible = 0;
                        break;
                    case SDLK_UP:
                        deplacementImpossible = deplacerJoueur(HAUT);
                        *signal = 0;
                        break;
                    case SDLK_DOWN:
                        deplacementImpossible = deplacerJoueur(BAS);
                        *signal = 0;
                        break;
                    case SDLK_RIGHT:
                        deplacementImpossible = deplacerJoueur(DROITE);
                        *signal = 0;
                        break;
                    case SDLK_LEFT:
                        deplacementImpossible = deplacerJoueur(GAUCHE);
                        *signal = 0;
                        break;
                    case SDLK_SPACE:
                        deplacementImpossible = 0;
                        *signal = 0;
                        break;
                    case SDLK_LESS:
                        deplacementImpossible = deplacerJoueur(DESCENDRE);
                        *signal = 2;
                        break;
                }
                break;
            default:
                deplacementImpossible = 1;
                
        }
    }while(deplacementImpossible);
}

void jouer(){
    int signalCommande=0;
    int etage = 1;
    
    initialiserJeu();    
    initialiserCarte();
    afficherCarte();
    
    do{
        do{
            actionMonstres();
            afficherCarte();
            attendreCommande(&signalCommande);
            deplacerOdeur();            
            afficherCarte();
            if(carteObjets[heros.y][heros.x]!= RIEN){
                if(dropObjet(carteObjets[heros.y][heros.x])){
                    //if(ajoutInventaire(carteObjets[yPerso][xPerso]))
                    carteObjets[heros.y][heros.x] = RIEN;
                }
            }
        }while(signalCommande == 0);
        resetMonstres();

        if(signalCommande == 1){
            return;
        }
        etage++;
        initialiserCarte();
        afficherCarte();
        if(etage == 10){
            // TODO dernier étage
        }
    }while(signalCommande == 2 && etage <= 10);
    
}