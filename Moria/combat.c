/* 
 * File:   combat.c
 * Author: tom
 *
 * Created on 1 août 2015, 16:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "structPersonnages.h"
#include "monstre.h"
#include "constantesGlobales.h"
#include "variablesGlobales.h"


void ecrireFrappeMonstre(int degats, int vieMonstre, int typeMonstre){
    SDL_Color couleurJaune = {255, 255, 0};
    SDL_Surface *messageSDL;
    SDL_Rect position1, position2;
    SDL_Event event;
    
    position1.x = 20;
    position1.y = 5;
    position2.x = 20;
    position2.y = 30;
    
    char nomMonstre[20];
    char message[TAILLE_MESSAGE];
    char messageAdd[TAILLE_MESSAGE];
    
    switch(typeMonstre) {
        case RAT:
            sprintf(nomMonstre, "rat");
            break;
    }
    
    if (degats == 0) {
        sprintf(message, "Vous manquez le %s.", nomMonstre);
    }
    else {
        if (vieMonstre > 0) {
            sprintf(message, "Vous infligez %d degats au %s.",degats, nomMonstre);
        }
        else {
            sprintf(message, "Vous infligez %d degats au %s,",degats, nomMonstre);
            sprintf(messageAdd, "le %s est mort !", nomMonstre);
        }
    }
    
    messageSDL = TTF_RenderText_Blended(policeMessage, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position1);
    messageSDL = TTF_RenderText_Blended(policeMessage, messageAdd, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position2);
    
    SDL_Flip(ecran);
    
    int pause = 1;
    while(pause) {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                pause = 0;  
        }
    }
}

void frappeMonstre(int yMonstre, int xMonstre) {
    int degats = 0;
    struct Monstre* monstre;
    monstre = getMonstre(xMonstre, yMonstre);
    
    if (100 - (( 100 - heros.precision ) * 
            (( monstre->agilite / heros.agilite ) / 2)) >= rand()%100) {
        degats = heros.force - monstre->armure;
        if(degats <= 0) {
            degats = 1;
        }
    }
    monstre->vie -= degats;
    ecrireFrappeMonstre(degats, monstre->vie, monstre->type);
    
    if(monstre->vie <= 0) {
        heros.experience += monstre->valeur;
        retirerMonstre(monstre->id);
    }
    
    // Passage niveau ??
}



