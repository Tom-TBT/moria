/* 
 * File:   structPerso.h
 * Author: tom
 *
 * Created on 1 août 2015, 11:46
 */

#ifndef STRUCTPERSO_H
#define	STRUCTPERSO_H

#define TAILLE_SAC 10
#define TAILLE_EQUIP 7  // 1 casque, 1 armure, 1 bottes, 1 collier, 2 anneaux,
// 1 arme, 1 carquois

struct Objet{
    int nomObjet;
    int modificateur;
    int estDecouvert;
    char id;
    struct Objet* objSuiv;
}Objet;

struct Heros {
    int x;
    int y;
    int cash;
    int odeur;
    int force;
    int vie;
    int vieMax;
    int armure;
    int niveau;
    int etage;
    int faim;
    int soif;
    int agilite;
    int experience;
    int precision;
    struct Objet *sac;
    struct Objet *equipements[TAILLE_EQUIP];
} Heros;

enum {
    CASQUE_EQ, ARMURE_EQ, BOTTES_EQ, ANNEAU_EQ,COLLIER_EQ, ARME_EQ, CARQUOIS_EQ
};

struct Monstre {
    int id;
    int type;
    int x;
    int y;
    int cap;
    struct Monstre* suiv;
    int vie;
    int force;
    int armure;
    int agilite;
    int valeur;
    int odorat;
    int precision;
};

#endif	/* STRUCTPERSO_H */

