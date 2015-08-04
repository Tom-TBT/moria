/*
objet.c
-----

Rôle : contient des fonction gérant les objets.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int poidsObjet(int codeObjet) {
    int resultat;
    
    switch(codeObjet) {
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

int restePlace(int codeObjet) {
    int poidsInventaire = 0;
    struct Objet *objCourant = heros.sac;
    
    while(objCourant != NULL) {
        poidsInventaire += poidsObjet(objCourant->codeObjet);
        objCourant = objCourant->objSuiv;
    }
    
    return (poidsInventaire + poidsObjet(codeObjet)) <= POIDS_INVENTAIRE_MAX;
}

int getType(int codeObjet) {
    int resultat;
    switch(codeObjet) {
        case EPEE_ACIER:
            resultat = ARME_EQ;
            break;
        case EPEE_FER:
            resultat = ARME_EQ;
            break;
        case ARMURE_CUIR:
            resultat = ARMURE_EQ;
            break;
        case ARMURE_FER:
            resultat = ARMURE_EQ;
            break;
        default:
            resultat = CONSOMMABLE;
            break;     
    }
    return resultat;
}

int ajoutInventaire(int codeObjet) {
    struct Objet *objCourant = heros.sac;
    int estAjoute = 0;
    
    if(heros.sac == NULL) {
        heros.sac = (struct Objet*)malloc(sizeof(struct Objet));
        heros.sac->codeObjet = codeObjet;
        heros.sac->objSuiv = NULL;
        heros.sac->modificateur = randModificateur();
        heros.sac->estDecouvert = 0;
        heros.sac->typeObjet = getType(codeObjet);
        
        estAjoute = 1;
    }
    else if(restePlace(codeObjet)) {
        while(objCourant->objSuiv != NULL) {
            objCourant = objCourant->objSuiv;            
        }
        objCourant->objSuiv = (struct Objet*)malloc(sizeof(struct Objet));
        objCourant->objSuiv->codeObjet = codeObjet;
        objCourant->objSuiv->objSuiv = NULL;
        objCourant->objSuiv->modificateur = randModificateur();
        objCourant->objSuiv->estDecouvert = 0;
        objCourant->objSuiv->typeObjet = getType(codeObjet);
        
        estAjoute = 1;
    }
    distribObjId();
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
            break;
        case RATION:
            resultat = RATION_ALIMENTAIRE;
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
                valeurRetour = ajoutInventaire(nouvelObjet(RATION));
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
        ecrireMessage(message, "", 1);
    }
    return valeurRetour;
}

char* getNomObjet(int codeObjet) {
    char * nomObjet = calloc(TAILLE_NOM_OBJET, sizeof(char));
    switch (codeObjet) {
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

struct Objet* getObjet(char lettreId) {
    struct Objet* objCourant = heros.sac;
    while(objCourant != NULL) {
        if(objCourant->id == lettreId) {
            break;
        }
        objCourant = objCourant->objSuiv;
    }
    return objCourant;
}

void enleverObjetSac(char lettreId) {
    struct Objet* objCourant = heros.sac;
    struct Objet* objPrecedant;
    if(objCourant->id == lettreId) {
        heros.sac = objCourant->objSuiv;
        free(objCourant);
    }
    else {
        objPrecedant = objCourant;
        objCourant = objCourant->objSuiv;
        while (objCourant != NULL) {
            if(objCourant->id == lettreId) {
                objPrecedant->objSuiv = objCourant->objSuiv;
                break;
            }
            objPrecedant = objCourant;
            objCourant = objCourant->objSuiv;
        }
    }
}

void rangerObjet(struct Objet* objet) {
    struct Objet* objetCourant = heros.sac;
    if(objetCourant == NULL) {
        heros.sac = objet;
    }
    else {
        while(objetCourant->objSuiv != NULL) {
            objetCourant = objetCourant->objSuiv;
        }
        objetCourant->objSuiv = objet;
    }    
    objet->objSuiv = NULL;
}

int equiperObjet(char lettreId) {
    int valeurRetour;
    struct Objet* tmpObj;
    struct Objet* monObjet = getObjet(lettreId);
    
    if(monObjet == NULL) {
        return 0;
    }
    else {
        if(monObjet->typeObjet < CONSOMMABLE) {
            tmpObj = heros.equipements[monObjet->typeObjet];            
            heros.equipements[monObjet->typeObjet] = monObjet; 
            enleverObjetSac(lettreId);
            if (tmpObj != NULL) {
                rangerObjet(tmpObj);
            }
            distribObjId();
        }
        else {
            return 0;
        }
    }
    return 1;
}