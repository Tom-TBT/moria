/*
niveau.c
----------

Rôle : fonctions gérant le chargement d'une carte

*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "variablesGlobales.h"
#include "carte.h"

int chargerCarte()
{
    
    
    FILE* fichierCarte = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    int i, j;
    char caractereLu;
    int numMap; /* Numéro de la carte choisie */
    
    fichierCarte = fopen("carte.txt", "r");
    if (fichierCarte == NULL)
        return 0;


    srand(time(NULL));
    numMap = (rand() % NOMBRE_LIGNE_FICHIER);
    
    while (numMap > 0)
    {
        caractereLu = fgetc(fichierCarte);
        if (caractereLu == '\n')
            numMap--;
    }

    fgets(ligneFichier, NB_BLOCS_HAUTEUR * NB_BLOCS_LARGEUR + 1, fichierCarte);
    for(i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for(j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_HAUTEUR) + j])
            {
                case 'a':
                    carte[j][i] = MUR_D;
                    break;
                case 'b':
                    carte[j][i] = MUR_G;
                    break;
                case 'c':
                    carte[j][i] = MUR_B;
                    break;
                case 'd':
                    carte[j][i] = MUR_H;
                    break;
                case 'e':
                    carte[j][i] = MUR_DB;
                    break;
                case 'f':
                    carte[j][i] = MUR_GB;
                    break;
                case 'g':
                    carte[j][i] = MUR_GH;
                    break;
                case 'h':
                    carte[j][i] = MUR_DH;
                    break;
                case 'i':
                    carte[j][i] = MUR_DGB;
                    break;
                case 'j':
                    carte[j][i] = MUR_GBH;
                    break;
                case 'k':
                    carte[j][i] = MUR_DGH;
                    break;
                case 'l':
                    carte[j][i] = MUR_DBH;
                    break;
                case 'm':
                    carte[j][i] = MUR_DG;
                    break;
                case 'n':
                    carte[j][i] = MUR_BH;
                    break;
                case 'o':
                    carte[j][i] = MUR_S;
                    break;

            }
        }
    }
    rewind(fichierCarte);
    fclose(fichierCarte);
    
    
    /*Réinitialisation des cartes*/
    for(i=0 ; i<NB_CASES_LARGEUR ; i++){
        for(j=0 ; j<NB_CASES_HAUTEUR ; j++){
            carteObjets[j][i] = RIEN;
            cartePersonnages[j][i] = RIEN;
        }
    }
    

    int k = 0, l = 0; /* Necessaire pour mettre dans bonnes cases */

    for(i = 1 ; i < NB_BLOCS_LARGEUR ; i++)  // chargement des murs
    {
        for(j = 2 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            k = (i-1)*2;
            l = (j-2)*2;

            switch (carte[j][i])
            {
                case MUR_D:
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_G:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    break;
                case MUR_B:
                    carteObjets[l+2][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    break;
                case MUR_H:
                    carteObjets[l][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DB:
                    carteObjets[l+2][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    break;
                case MUR_GB:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    break;
                case MUR_GH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DGB:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_GBH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DGH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DBH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_DG:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+1][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+1][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_BH:
                    carteObjets[l][k] = MUR;
                    carteObjets[l+2][k] = MUR;
                    carteObjets[l][k+1] = MUR;
                    carteObjets[l][k+2] = MUR;
                    cartePersonnages[l][k] = MUR;
                    cartePersonnages[l+2][k] = MUR;
                    cartePersonnages[l][k+1] = MUR;
                    cartePersonnages[l][k+2] = MUR;
                    break;
                case MUR_S:
                    break;

            }
        }
    }

    return 1;

}

void spawnObjets(){
    int minObjet[NB_TYPES_OBJETS], maxObjet[NB_TYPES_OBJETS]; // Il existe 12 objets différents
    int typeObjet, nombreObjets, xObj, yObj;
    int i;
    
    minObjet[ANNEAU] = 0;
    maxObjet[ANNEAU] = 3;
    minObjet[ARGENT] = 6;
    maxObjet[ARGENT] = 12;
    minObjet[ARME] = 1;
    maxObjet[ARME] = 3;
    minObjet[BAGUETTE] = 0;
    maxObjet[BAGUETTE] = 3;
    minObjet[EAU] = 0;
    maxObjet[EAU] = 2;
    minObjet[ARMURE] = 1;
    maxObjet[ARMURE] = 3;
    minObjet[PARCHEMIN] = 4;
    maxObjet[PARCHEMIN] = 9;
    minObjet[POTION] = 4;
    maxObjet[POTION] = 7;
    minObjet[RATION] = 1;
    maxObjet[RATION] = 3;
    minObjet[ESCALIER] = 1;
    maxObjet[ESCALIER] = 1;
    
    for(typeObjet=2 ; typeObjet < NB_TYPES_OBJETS ; typeObjet++){
        nombreObjets = (rand() % (maxObjet[typeObjet] - minObjet[typeObjet] + 1)) + minObjet[typeObjet];
        i=0;
        while (i < nombreObjets)
        {
            xObj = (rand() % (NB_CASES_LARGEUR-4)) + 1;
            yObj = (rand() % (NB_CASES_HAUTEUR-4)) + 1;
            if (carteObjets[yObj][xObj] == RIEN)
            {
                carteObjets[yObj][xObj] = typeObjet;
                i++;
            }
        }
    }
}
