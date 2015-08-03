/*
objet.c
-----

Rôle : contient des fonction gérant les objets.

*/
#include <stdio.h>
#include <stdlib.h>

#include "variablesGlobales.h"


int spawnArgent() {
    return (rand() % 50 + 20) * heros.niveau;
}

int randModificateur() {
    int random, resultat;
    random = rand()%12;
    if(random < 2) {
        resultat = -1;
    }
    else if(random < 6) {
        resultat = 0;
    }
    else if(random < 9) {
        resultat = 1;
    }
    else if(random < 10) {
        resultat = 2;
    }
    else {
        resultat = 3;
    }
    return resultat;
}

int poidsObjet(int objet) {
    int resultat;
    
    switch(objet) {
        case RATION_ALIMENTAIRE:
            resultat = 2;
            break;
        case EPEE_FER:
            resultat = 8;
            break;
        case EPEE_ACIER:
            resultat = 8;
            break;
        case POTION_JAUNE:
            resultat = 2;
            break;
        case ARMURE_CUIR:
            resultat = 5;
            break;
        case ARMURE_FER:
            resultat = 5;
            break;
        default:
            resultat = 0;
            break;
    }
    return resultat;
}

int restePlace(int objet) {
    int poidsInventaire = 0;
    struct Objet *objCourant = heros.sac;
    
    while(objCourant != NULL) {
        poidsInventaire += poidsObjet(objCourant->nomObjet);
        objCourant = objCourant->objSuiv;
    }
    
    return (poidsInventaire + poidsObjet(objet)) <= POIDS_INVENTAIRE_MAX;
}


int ajoutInventaire(int objet) {
    struct Objet *objCourant = heros.sac;
    int estAjoute = 0;
    
    if(heros.sac == NULL) {
        heros.sac = (struct Objet*)malloc(sizeof(struct Objet));
        heros.sac->nomObjet = objet;
        heros.sac->objSuiv = NULL;
        heros.sac->modificateur = randModificateur();
        heros.sac->estDecouvert = 0;
        
        estAjoute = 1;
    }
    else if(restePlace(objet)) {
        while(objCourant->objSuiv != NULL) {
            objCourant = objCourant->objSuiv;            
        }
        objCourant->objSuiv = (struct Objet*)malloc(sizeof(struct Objet));
        objCourant->objSuiv->nomObjet = objet;
        objCourant->objSuiv->objSuiv = NULL;
        objCourant->objSuiv->modificateur = randModificateur();
        objCourant->objSuiv->estDecouvert = 0;
        
        estAjoute = 1;
    }
    return estAjoute;
}

int nouvelObjet(int typeObjet) {
    int resultat;
    
    switch(typeObjet) {
        case ARME:
            if(rand()%1 == 0){ // Epée, lance, arc, ...
                if(rand()%2 == 0){ // Fer, acier, ...
                    resultat = EPEE_FER;
                }
                else {
                    resultat = EPEE_ACIER;
                }
            }
    }
    return resultat;
}

int dropObjet(int typeObjet) {
    char message[TAILLE_MESSAGE] = "";

    int valeurRetour = 0;

    int newCash;

    if (typeObjet >= ARGENT && typeObjet <= RATION) {
        switch (typeObjet) {
            case ANNEAU:
                sprintf(message, "Vous avez trouve un anneau");
                break;
            case ARME:
                sprintf(message, "Vous avez trouve une arme");
                valeurRetour = ajoutInventaire(nouvelObjet(ARME));
                break;
            case ARMURE:
                sprintf(message, "Vous avez trouve une armure");
                break;
            case BAGUETTE:
                sprintf(message, "Vous avez trouve une baguette");
                break;
            case PARCHEMIN:
                sprintf(message, "Vous avez trouve un parchemin");
                break;
            case POTION:
                sprintf(message, "Vous avez trouve une potion");
                break;
            case RATION:
                sprintf(message, "Vous avez trouve une ration alimentaire");
                break;
            case ARGENT:
                newCash = spawnArgent();
                sprintf(message, "Vous avez trouve %d pieces", newCash);
                heros.cash += newCash;
                valeurRetour = 1;
                break;
        }
    } else if (typeObjet == EAU) {
        sprintf(message, "Plouf, votre armure est rouillee ...");
    }

    if(strlen(message) > 0) {
        ecrireMessage(message, "");
    }
    return valeurRetour;
}

char* getNomObjet(int csteObj) {
    char * nomObjet = calloc(TAILLE_NOM_OBJET, sizeof(char));
    switch (csteObj) {
        case RATION_ALIMENTAIRE:
            sprintf(nomObjet,"Ration alimentaire");
            break;
        case EPEE_FER:
            sprintf(nomObjet,"Epee en fer");
            break;
        case EPEE_ACIER:
            sprintf(nomObjet,"Epee en acier");
            break;
        case POTION_JAUNE:
            sprintf(nomObjet,"Potion jaune");
            break;
        case ARMURE_CUIR:
            sprintf(nomObjet,"Armure en cuir");
            break;
        case ARMURE_FER:
            sprintf(nomObjet,"Armure en fer");
            break;
        default:
            break;
    }
    return nomObjet;
}

void distribObjId(){
    int i = 97;
    struct Objet *objCourant = heros.sac;
    while(objCourant != NULL) {
        objCourant->id = (char)i;
        objCourant = objCourant->objSuiv;
        i++;
    }
}