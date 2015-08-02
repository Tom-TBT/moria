/*
heros.c
-----

Rôle : contient des fonction gérant le héros

*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "variablesGlobales.h"

void passageNiveau(){
    heros.niveau++;
    heros.vieMax += (heros.niveau - 1) + (rand() % heros.niveau);
    heros.vie = heros.vieMax;
    
    // Inventer d'autres règles
}
