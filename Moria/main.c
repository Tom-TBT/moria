/* 
 * File:   main.c
 * Author: tom
 *
 * Created on 24 février 2015, 16:20
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantesEcran.h"
#include "structPersonnages.h"

int main(int argc, char** argv) {
    SDL_Event event;
    
    initialiserSDL();
    
    afficherMenu();
    
    int continuer = 1;
    while (continuer) {
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym) {
                    case SDLK_q :
                        continuer = 0;
                        break;
                    case SDLK_j :
                        jouer();
                        break;
                    case SDLK_ESCAPE :
                        continuer = 0;
                        break;
                    /*case SDLK_s :
                        score(ecran);
                        break;*/
                    /*case SDLK_e :
                        explications(ecran);
                        break;*/

                }
                break;
        }
        afficherMenu();
    }
    
    fermerSDL();
    
    return (EXIT_SUCCESS);
}

