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
#include "constantesGlobales.h"
#include "variablesGlobales.h"


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
    messageCombat(degats, monstre->vie, monstre->type);
    
    if(monstre->vie <= 0) {
        heros.experience += monstre->valeur;
        retirerMonstre(monstre->id);
    }
    
    // Passage niveau ??
}

void messageCombat(int degats, int vieMonstre, int typeMonstre){
    
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
    
    ecrireMessage(message, messageAdd);
    
    attendrePressionTouche();    
}

