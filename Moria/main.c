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

/* Variables globales du projet*/
SDL_Surface *ecran; // Ecran de jeu

/* Definitions des cartes du jeu*/
int carte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR];
int cartePersonnages[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
int carteObjets[NB_CASES_HAUTEUR][NB_CASES_LARGEUR];
int carteOdeurs[NB_CASES_HAUTEUR][NB_CASES_LARGEUR] = {{0}};

struct Heros heros;
struct Monstre* teteListeMonstre = NULL;

/*Variables de la police*/
TTF_Font *policeMessage = NULL;
TTF_Font *policeStatus = NULL;

/* Surfaces SDL à charger : Murs, objets et personnages*/
SDL_Surface *imgMur[15] = {NULL};
SDL_Surface *imgAnneau = NULL, *imgArgent = NULL, *imgArme = NULL, 
        *imgArmure = NULL, *imgBaguette = NULL, *imgEau = NULL, 
        *imgEscalier = NULL, *imgParchemin = NULL, *imgPotion = NULL, 
        *imgRation = NULL;
SDL_Surface *imgHeros = NULL, *imgRat = NULL;



void afficherMenu(){
    SDL_Surface *menu;
    SDL_Rect positionMenu;
    SDL_Event event;
    SDL_Color couleurJaune = {255,255,0,};
    
    int continuer = 1;
    
    menu = IMG_Load("images/menu.jpg");
    positionMenu.x = 0;
    positionMenu.y = 0;

    
    //police = TTF_OpenFont("/usr/share/fonts/truetype/DeutschGothic.ttf", 22);
    /*
    TTF_SetFontStyle(police, TTF_STYLE_ITALIC);
    texte = TTF_RenderText_Blended(police, "Vous avez droppé un anneau !", couleurJaune);
    */
    
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                continuer = 0;
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
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

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(menu,NULL,ecran,&positionMenu);
        SDL_Flip(ecran);
    }
    SDL_FreeSurface(menu);    
}

int main(int argc, char** argv) {

    SDL_Init(SDL_INIT_VIDEO);
    
    /*Initialisation de ttf*/
    TTF_Init();
    policeMessage = TTF_OpenFont("./police/bridge.ttf", 20);
    policeStatus = TTF_OpenFont("./police/bridge.ttf", 18);
    
    /* Initialisation des paramètres de l'écran de jeu*/
    SDL_WM_SetIcon(IMG_Load("Icone.jpg"),NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Moria",NULL);
    
    SDL_EnableKeyRepeat(100,100);
    
    afficherMenu();
    
    /* Fermeture de ttf*/
    TTF_CloseFont(policeMessage);
    TTF_CloseFont(policeStatus);
    TTF_Quit();
    
    SDL_Quit();
    
    return (EXIT_SUCCESS);
}

