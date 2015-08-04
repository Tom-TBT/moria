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

char readCharSDL() {
    SDL_Event event;
    int attente = 1;
    char caractereLu;
    
    while (attente)
    {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_a:
                caractereLu = 'a';
            break;
            case SDLK_b:
                caractereLu = 'b';
            break;           
            case SDLK_c:
                caractereLu = 'c';
            break;
            case SDLK_d:
                caractereLu = 'd';
            break;            
            case SDLK_e:
                caractereLu = 'e';
            break;
            case SDLK_f:
                caractereLu = 'f';
            break;           
            case SDLK_g:
                caractereLu = 'g';
            break;
            case SDLK_h:
                caractereLu = 'h';
            break;           
            case SDLK_i:
                caractereLu = 'i';
            break;
            case SDLK_j:
                caractereLu = 'j';
            break;       
            case SDLK_k:
                caractereLu = 'k';
            break;
            case SDLK_l:
                caractereLu = 'l';
            break; 
            case SDLK_m:
                caractereLu = 'm';
            break;
            case SDLK_n:
                caractereLu = 'n';
            break;           
            case SDLK_o:
                caractereLu = 'o';
            break;
            case SDLK_p:
                caractereLu = 'p';
            break;       
            case SDLK_q:
                caractereLu = 'q';
            break;
            case SDLK_r:
                caractereLu = 'r';
            break;
            case SDLK_s:
                caractereLu = 's';
            break;
            case SDLK_t:
                caractereLu = 't';
            break;       
            case SDLK_u:
                caractereLu = 'u';
            break;
            case SDLK_v:
                caractereLu = 'v';
            break;
            case SDLK_w:
                caractereLu = 'w';
            break;
            case SDLK_x:
                caractereLu = 'x';
            break;       
            case SDLK_y:
                caractereLu = 'y';
            break;
            case SDLK_z:
                caractereLu = 'z';
            break;
            default:
                caractereLu = '?';
                break;
            }           
            attente = 0;
         break;
        }
    } 
    return caractereLu;
}

void attendreCommande(int* signal){
    SDL_Event event;
    int deplacementImpossible;
    
    char lettreObjet;
    
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
                        break;
                    case SDLK_e:
                        deplacementImpossible = 1;
                        *signal = 0;
                        ecrireMessage("Quel objet voulez vous equiper ?",
                                "(appuyez sur la touche correspondante)", 0);
                        if(!equiperObjet(readCharSDL())){
                            afficherCarte();
                            ecrireMessage("Vous ne pouvez pas equiper cela !","",1);
                        }
                        afficherCarte();
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
        heros.etage++;
        
        initialiserCarte();
        afficherCarte();
        if(heros.etage == 10){
            // TODO dernier étage
        }
    }while(signalCommande == 2 && heros.etage <= 10);
    
}