/*
gestionPartie.c
-----

Rôle : contient des fonction gérant le jeu

*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "variablesGlobales.h"
#include "combat.h"

void initialiserOdeur(){
    int i,j;
    
    for(i = 0 ; i < NB_CASES_LARGEUR ; i++)
    {
        for(j = 0 ; j < NB_CASES_HAUTEUR ; j++)
        {
            carteOdeurs[j][i] = 0;
        }
    }
}

void initialiserJeu(){
    heros.cash = 0;
    heros.vie = 6;
    heros.armure = 0;
    heros.force = 2;
    heros.niveau = 1;
    heros.etage = 1;
    heros.faim = 60;
    heros.soif = 40;
    heros.agilite = 2;
    heros.precision = 75;
}

/* Charge une carte et y met les objets*/
void initialiserCarte(){
    int nonPlace = 1;
    
    if(!chargerCarte()){
        exit(EXIT_FAILURE);
    }
    while(nonPlace)
    {
        heros.x = (rand() % (NB_CASES_LARGEUR-4)) + 1;
        heros.y = (rand() % (NB_CASES_HAUTEUR-4)) + 1;
        if ((carteObjets[heros.y][heros.x] == RIEN) && 
                (cartePersonnages[heros.y][heros.x] == RIEN))
        {
            cartePersonnages[heros.y][heros.x] = PERSONNAGE;
            nonPlace = 0;
        }
    }
    /*En descendant le personnage retrouve une odeur normale*/
    heros.odeur = 10;
    initialiserOdeur();
    
    spawnObjets();
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
    for (i = 0 ; i < NB_CASES_LARGEUR ; i++) // Blits des objets
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

void chargerImages(){
    
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

void libererImages(){
    int i = 0;
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

    for (i = 0 ; i < 15 ; i++)
        SDL_FreeSurface(imgMur[i]);
    
}


int deplacerJoueur(int direction){
    switch(direction){
        case HAUT:
            if(cartePersonnages[heros.y-1][heros.x] == MUR)
                return 1;
            else if(cartePersonnages[heros.y-1][heros.x] > PERSONNAGE){
                // Si c'est un monstre car après personnage c'est des monstres
                frappeMonstre(heros.y-1,heros.x);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y-1][heros.x] = PERSONNAGE;
                heros.y--;
            }
            break;
        case BAS:
            if(cartePersonnages[heros.y+1][heros.x] == MUR)
                return 1;
            else if(cartePersonnages[heros.y+1][heros.x] > PERSONNAGE){
                // Si c'est un monstre
                frappeMonstre(heros.y+1,heros.x);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y+1][heros.x] = PERSONNAGE;
                heros.y++;
            }
            break;
        case GAUCHE:
            if(cartePersonnages[heros.y][heros.x-1] == MUR)
                return 1;
            else if(cartePersonnages[heros.y][heros.x-1] > PERSONNAGE){
                // Si c'est un monstre
                frappeMonstre(heros.y,heros.x-1);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y][heros.x-1] = PERSONNAGE;
                heros.x--;
            }
            break;
        case DROITE:
            if(cartePersonnages[heros.y][heros.x+1] == MUR)
                return 1;
            else if(cartePersonnages[heros.y][heros.x+1] > PERSONNAGE){
                // Si c'est un monstre
                frappeMonstre(heros.y,heros.x+1);
            }
            else{
                cartePersonnages[heros.y][heros.x] = RIEN;
                cartePersonnages[heros.y][heros.x+1] = PERSONNAGE;
                heros.x++;
            }
            break;
        case DESCENDRE:
            if(carteObjets[heros.y][heros.x] != ESCALIER){
                return 1;
            }
            break;
    }
    
    return 0;
}

void attendreCommande(int* signal){
    SDL_Event event;
    int deplacementImpossible;
    
    do{
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *signal = 1;
                deplacementImpossible = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        *signal = 1;
                        deplacementImpossible = 0;
                        break;
                    case SDLK_UP:
                        deplacementImpossible = deplacerJoueur(HAUT);
                        *signal = 0;
                        break;
                    case SDLK_DOWN:
                        deplacementImpossible = deplacerJoueur(BAS);
                        *signal = 0;
                        break;
                    case SDLK_RIGHT:
                        deplacementImpossible = deplacerJoueur(DROITE);
                        *signal = 0;
                        break;
                    case SDLK_LEFT:
                        deplacementImpossible = deplacerJoueur(GAUCHE);
                        *signal = 0;
                        break;
                    case SDLK_LESS:
                        deplacementImpossible = deplacerJoueur(DESCENDRE);
                        *signal = 2;
                        break;
                }
                break;
            default:
                deplacementImpossible = 1;
                
        }
    }while(deplacementImpossible);
}

void diffuserOdeur(int portee, int x, int y){
    if(portee != 1){
        if(carteObjets[y-1][x] != MUR && carteOdeurs[y-1][x] < portee){
            diffuserOdeur((portee-1),x,(y-1));
        }
        if(carteObjets[y+1][x] != MUR && carteOdeurs[y+1][x] < portee){
            diffuserOdeur((portee-1),x,(y+1));
        }
        if(carteObjets[y][x-1] != MUR && carteOdeurs[y][x-1] < portee){
            diffuserOdeur((portee-1),(x-1),y);
        }
        if(carteObjets[y][x+1] != MUR && carteOdeurs[y][x+1] < portee){
            diffuserOdeur((portee-1),(x+1),y);
        }
    }
    if(carteOdeurs[y][x] < portee){
        carteOdeurs[y][x] = portee;
    }
}

void jouer(){
    int signal=0;
    int etage = 1;
    
    chargerImages();
    
    initialiserJeu();
    
    initialiserCarte();
    afficherCarte();
    
    do{
        do{
            attendreCommande(&signal);
            initialiserOdeur();
            diffuserOdeur(heros.odeur, heros.x, heros.y);
            actionMonstres();
            afficherCarte();
            if(carteObjets[heros.y][heros.x]!= RIEN){
                if(actionObjet(carteObjets[heros.y][heros.x])){
                    //if(ajoutInventaire(carteObjets[yPerso][xPerso]))
                    carteObjets[heros.y][heros.x] = RIEN;
                }
            }
        }while(signal == 0);
        libererMonstres();

        if(signal == 1){
            return;
        }
        etage++;
        initialiserCarte();
        afficherCarte();
        if(etage == 10){
            
        }
    }while(signal == 2 && etage <= 10);
    libererImages();
    
}