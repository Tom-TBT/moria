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

ajoutInventaire(int objet) {
    int modificateur = randModificateur();
    int placeLibre;
    short estPlein = 1, estPlace = 0;
    int i;
    for(i = 0; i < TAILLE_SAC; i++) {
        if(objet == heros.sac[i][0] && modificateur == heros.sac[i][2]) {
            heros.sac[i][3] += 1;
            estPlace = 1;
        }
        else if( VIDE == heros.sac[i][0] && estPlein) {
            placeLibre = i;
            estPlein = 0;
        }
    }
    if(!estPlace && !estPlein) {
        heros.sac[placeLibre][0] = objet;
        heros.sac[placeLibre][2] = modificateur;
        heros.sac[placeLibre][3] = 1;
    }
}

nouvelObjet(int typeObjet) {
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
                ajoutInventaire(nouvelObjet(ARME));
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
                break;
        }
        valeurRetour = 1;
    } else if (typeObjet == EAU) {
        sprintf(message, "Plouf, votre armure est rouillee ...");
    }

    ecrireMessage(message, "");

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