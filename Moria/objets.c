#include "variablesGlobales.h"

int spawnArgent(){  
    return (rand()%50 + 20) * heros.niveau;
}

int actionObjet(int typeObjet){
    SDL_Event event;
    char message[TAILLE_MESSAGE];
    SDL_Rect position;
    SDL_Surface *messageSDL;
    SDL_Color couleurJaune = {255, 255, 0};
    
    int valeurRetour = 0;
    
    int newCash;
    
    position.x = 20;
    position.y = 5;
    
    if(typeObjet >= ARGENT && typeObjet<=RATION){
        switch(typeObjet){
            case ANNEAU:
                sprintf(message,"Vous avez trouve un anneau");
                break;
            case ARME:
                sprintf(message,"Vous avez trouve une arme");
                break;
            case ARMURE:
                sprintf(message,"Vous avez trouve une armure");
                break;
            case BAGUETTE:
                sprintf(message,"Vous avez trouve une baguette");
                break;
            case PARCHEMIN:
                sprintf(message,"Vous avez trouve un parchemin");
                break;
            case POTION:
                sprintf(message,"Vous avez trouve une potion");
                break;
            case RATION:
                sprintf(message,"Vous avez trouve une ration alimentaire");
                break;
            case ARGENT:
                newCash = spawnArgent();
                sprintf(message,"Vous avez trouve %d pieces", newCash);
                heros.cash += newCash;
                break;
        }  
        valeurRetour = 1;
    }
    else if(typeObjet == EAU){
        sprintf(message,"Plouf, votre armure est rouillee ...");
    }
    messageSDL = TTF_RenderText_Blended(policeMessage, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
    SDL_Flip(ecran);
    
    return valeurRetour;
}