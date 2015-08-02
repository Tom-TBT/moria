/*
affichage.c
-----

Rôle : gère toutes les fonctions d'affichage/rafraichissement de l'écran

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantesEcran.h"
#include "variablesGlobales.h"
#include "constantesGlobales.h"

/* Variables globales du projet*/
SDL_Surface *ecran; // Ecran de jeu

SDL_Surface *menu;

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

void initialiserSDL() {
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
    
    menu = IMG_Load("images/menu.jpg");
    
    imgAnneau = IMG_Load("images/Anneau.jpg");
    imgArgent = IMG_Load("images/Argent.jpg");
    imgArme = IMG_Load("images/Arme.jpg");
    imgArmure = IMG_Load("images/Armure.jpg");
    imgBaguette = IMG_Load("images/Baguette.jpg");
    imgEau = IMG_Load("images/Eau.jpg");
    imgEscalier = IMG_Load("images/Escalier.jpg");
    imgParchemin = IMG_Load("images/Parchemin.jpg");
    imgPotion = IMG_Load("images/Potion.jpg");
    imgRation = IMG_Load("images/Ration.jpg");
    
    imgHeros = IMG_Load("images/Personnage.jpg");
    imgRat = IMG_Load("images/Rat.jpg");
    
    imgMur[MUR_D] = IMG_Load("images/MurD.jpg");
    imgMur[MUR_G] = IMG_Load("images/MurG.jpg");
    imgMur[MUR_B] = IMG_Load("images/MurB.jpg");
    imgMur[MUR_H] = IMG_Load("images/MurH.jpg");
    imgMur[MUR_DB] = IMG_Load("images/MurDB.jpg");
    imgMur[MUR_GB] = IMG_Load("images/MurGB.jpg");
    imgMur[MUR_GH] = IMG_Load("images/MurGH.jpg");
    imgMur[MUR_DH] = IMG_Load("images/MurDH.jpg");
    imgMur[MUR_DGB] = IMG_Load("images/MurDGB.jpg");
    imgMur[MUR_GBH] = IMG_Load("images/MurGBH.jpg");
    imgMur[MUR_DGH] = IMG_Load("images/MurDGH.jpg");
    imgMur[MUR_DBH] = IMG_Load("images/MurDBH.jpg");
    imgMur[MUR_DG] = IMG_Load("images/MurDG.jpg");
    imgMur[MUR_BH] = IMG_Load("images/MurBH.jpg");
    imgMur[MUR_S] = IMG_Load("images/MurS.jpg");
}

void fermerSDL() {
    int i = 0;
    for (i = 0 ; i < 15 ; i++)
        SDL_FreeSurface(imgMur[i]);
    
    SDL_FreeSurface(imgAnneau);
    SDL_FreeSurface(imgArgent);
    SDL_FreeSurface(imgArme);
    SDL_FreeSurface(imgArmure);
    SDL_FreeSurface(imgBaguette);
    SDL_FreeSurface(imgEau);
    SDL_FreeSurface(imgEscalier);
    SDL_FreeSurface(imgParchemin);
    SDL_FreeSurface(imgPotion);
    SDL_FreeSurface(imgRation);
    
    SDL_FreeSurface(imgHeros);
    SDL_FreeSurface(imgRat);
    
    SDL_FreeSurface(menu); 
    
    /* Fermeture de ttf*/
    TTF_CloseFont(policeMessage);
    TTF_CloseFont(policeStatus);
    TTF_Quit();
    
    SDL_Quit();
}

void afficherMenu(){    
    SDL_Rect positionMenu;
    SDL_Color couleurJaune = {255,255,0,};

    positionMenu.x = 0;
    positionMenu.y = 0;  

    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(menu,NULL,ecran,&positionMenu);
    SDL_Flip(ecran);      
}

void afficherStatus(){
    SDL_Color couleurJaune = {255, 255, 0};
    SDL_Surface *messageSDL;
    SDL_Rect position;

    char varMess[10];
    char message[20];
    position.y = 396;
    
    sprintf(message, "Etage: ");
    sprintf(varMess, "%d", heros.etage);
    strcat(message, varMess);
    position.x = 20;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
    
    sprintf(message, "Vie: ");
    sprintf(varMess, "%d", heros.vie);
    strcat(message, varMess);
    position.x = 320;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
        
    sprintf(message, "Force: ");
    sprintf(varMess, "%d", heros.force);
    strcat(message, varMess);
    position.x = 400;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
    
    sprintf(message, "Armure: ");
    sprintf(varMess, "%d", heros.armure);
    strcat(message, varMess);
    position.x = 490;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
    
    sprintf(message, "Niveau: ");
    sprintf(varMess, "%d", heros.niveau);
    strcat(message, varMess);
    position.x = 600;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
        
    sprintf(message, "Argent: ");
    sprintf(varMess, "%d", heros.cash);
    strcat(message, varMess);
    position.x = 700;
    messageSDL = TTF_RenderText_Blended(policeStatus, message, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &position);
    
}

void afficherCarte(){
    
    SDL_Rect position;   
    int i, j;
    
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++) // Blits de la carte
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            position.x = i * LARGEUR_BLOC;
            position.y = j * HAUTEUR_BLOC;

            switch(carte[j][i])
            {
                case MUR_D:
                    SDL_BlitSurface(imgMur[MUR_D], NULL, ecran, &position);
                    break;
                case MUR_G:
                    SDL_BlitSurface(imgMur[MUR_G], NULL, ecran, &position);
                    break;
                case MUR_B:
                    SDL_BlitSurface(imgMur[MUR_B], NULL, ecran, &position);
                    break;
                case MUR_H:
                    SDL_BlitSurface(imgMur[MUR_H], NULL, ecran, &position);
                    break;
                case MUR_DB:
                    SDL_BlitSurface(imgMur[MUR_DB], NULL, ecran, &position);
                    break;
                case MUR_GB:
                    SDL_BlitSurface(imgMur[MUR_GB], NULL, ecran, &position);
                    break;
                case MUR_GH:
                    SDL_BlitSurface(imgMur[MUR_GH], NULL, ecran, &position);
                    break;
                case MUR_DH:
                    SDL_BlitSurface(imgMur[MUR_DH], NULL, ecran, &position);
                    break;
                case MUR_DGB:
                    SDL_BlitSurface(imgMur[MUR_DGB], NULL, ecran, &position);
                    break;
                case MUR_GBH:
                    SDL_BlitSurface(imgMur[MUR_GBH], NULL, ecran, &position);
                    break;
                case MUR_DGH:
                    SDL_BlitSurface(imgMur[MUR_DGH], NULL, ecran, &position);
                    break;
                case MUR_DBH:
                    SDL_BlitSurface(imgMur[MUR_DBH], NULL, ecran, &position);
                    break;
                case MUR_DG:
                    SDL_BlitSurface(imgMur[MUR_DG], NULL, ecran, &position);
                    break;
                case MUR_BH:
                    SDL_BlitSurface(imgMur[MUR_BH], NULL, ecran, &position);
                    break;
                case MUR_S:
                    SDL_BlitSurface(imgMur[MUR_S], NULL, ecran, &position);
                    break;

            }
        }
    }
    for (i = 0 ; i < NB_CASES_LARGEUR ; i++) // Blits des objets et persos
    {
        for (j = 0 ; j < NB_CASES_HAUTEUR ; j++)
        {
            position.x = (i * LARGEUR_OBJET) + (LARGEUR_BLOC-5);
            position.y = (j * HAUTEUR_OBJET) + ((HAUTEUR_BLOC * 2)-6);


            switch(carteObjets[j][i])
            {
                case ANNEAU:
                    SDL_BlitSurface(imgAnneau, NULL, ecran, &position);
                    break;
                case ARGENT:
                    SDL_BlitSurface(imgArgent, NULL, ecran, &position);
                    break;
                case ARME:
                    SDL_BlitSurface(imgArme, NULL, ecran, &position);
                    break;
                case ARMURE:
                    SDL_BlitSurface(imgArmure, NULL, ecran, &position);
                    break;
                case BAGUETTE:
                    SDL_BlitSurface(imgBaguette, NULL, ecran, &position);
                    break;
                case EAU:
                    SDL_BlitSurface(imgEau, NULL, ecran, &position);
                    break;
                case ESCALIER:
                    SDL_BlitSurface(imgEscalier, NULL, ecran, &position);
                    break;
                case PARCHEMIN:
                    SDL_BlitSurface(imgParchemin, NULL, ecran, &position);
                    break;
                case POTION:
                    SDL_BlitSurface(imgPotion, NULL, ecran, &position);
                    break;
                case RATION:
                    SDL_BlitSurface(imgRation, NULL, ecran, &position);
                    break;

            }
            switch(cartePersonnages[j][i])
            {
                case PERSONNAGE:
                    SDL_BlitSurface(imgHeros, NULL, ecran, &position);
                    break;

                case RAT:
                    SDL_BlitSurface(imgRat, NULL, ecran, &position);
                    break;
            }
        }
    }
    
    afficherStatus();

    SDL_Flip(ecran);    
}

void attendrePressionTouche(){
    int pause = 1;
    SDL_Event event;
    
    while(pause) {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_KEYDOWN:
                pause = 0;  
        }
    }
}

void ecrireMessage(char ligneHaut[], char ligneBas[]) {
    SDL_Color couleurJaune = {255, 255, 0};
    SDL_Rect positionLigneHaut, positionLigneBas;
    SDL_Surface *messageSDL;
    
    positionLigneHaut.x = 20;
    positionLigneHaut.y = 5;
    positionLigneBas.x = 20;
    positionLigneBas.y = 30;
    
    messageSDL = TTF_RenderText_Blended(policeMessage, ligneHaut, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &positionLigneHaut);
    messageSDL = TTF_RenderText_Blended(policeMessage, ligneBas, couleurJaune);
    SDL_BlitSurface(messageSDL, NULL, ecran, &positionLigneBas);
    
    SDL_Flip(ecran);
}
