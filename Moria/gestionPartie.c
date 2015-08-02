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
int nivSuivant[NB_NIVEAUX] = {0,5,12,20,35,60};

void initialiserJeu(){
    srand(time(NULL));
    
    initialiserHeros();
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
                    case SDLK_i:
                        deplacementImpossible = 1;
                        *signal = 0;
                        afficherInventaire();
                        afficherCarte();
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