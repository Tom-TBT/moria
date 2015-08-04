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


int calculDegats(int precisionAtt, int agiliteAtt, int forceAtt, int agiliteDef, 
        int armureDef) {
    int degats = 0;
    
    if (100 - (( 100 - precisionAtt ) * 
            (( agiliteDef / agiliteAtt ) / 2)) >= rand()%100) {
        degats = forceAtt - armureDef;
        if(degats <= 0) {
            degats = 1;
        }
    }
    return degats;
}

void messageFrappeMonstre(int degats, int vieMonstre, int typeMonstre){
    
    char nomMonstre[20];
    char message[TAILLE_MESSAGE];
    char messageAdd[TAILLE_MESSAGE] = {};
    
    getNomMonstre(typeMonstre, nomMonstre);
    
    if (degats == 0) {
        sprintf(message, "Vous manquez le %s.", nomMonstre);
    }
    else {
        sprintf(message, "Vous infligez %d degats au %s.",degats, nomMonstre);
        if (vieMonstre <= 0) {
            sprintf(messageAdd, "le %s est mort !", nomMonstre);
        }
    }    
    
    ecrireMessage(message, messageAdd, 1);    
    afficherCarte();
}

void frappeMonstre(int yMonstre, int xMonstre) {
    int degats;
    struct Monstre* monstre;
    int force = heros.force;

    monstre = getMonstre(xMonstre, yMonstre);
    
    degats = calculDegats(heros.precision, heros.agilite, heros.force, 
            monstre->agilite, monstre->armure);

    monstre->vie -= degats;
    messageFrappeMonstre(degats, monstre->vie, monstre->type);
    
    if(monstre->vie <= 0) {
        heros.experience += monstre->valeur;
        retirerMonstre(monstre->id);
    }
    
    if(heros.experience >= nivSuivant[heros.niveau]) {
        passageNiveau();
    }
}

void messageFrappeHeros(int degats, int typeMonstre) {
    char nomMonstre[20];
    char message[TAILLE_MESSAGE];
    char messageAdd[TAILLE_MESSAGE] = {};
    
    getNomMonstre(typeMonstre, nomMonstre);
    
    if (degats == 0) {
        sprintf(message, "Le %s vous rate.", nomMonstre);
    }
    else {
        sprintf(message, "Le %s vous inflige %d degats.", nomMonstre, degats);
        if (heros.vie <= 0) {
            sprintf(messageAdd, "Vous etes mort !");
        }
    }  
    
    ecrireMessage(message, messageAdd, 1);
    afficherCarte();
}

void frappeHeros(struct Monstre* monstre) {
    int degats;
    degats = calculDegats(monstre->precision, monstre->agilite, monstre->force, 
            heros.agilite, heros.armure);
    
    heros.vie -= degats;
    messageFrappeHeros(degats, monstre->type);
    
    if(heros.vie <= 0) {
        //Fin jeu
    }
    
}
