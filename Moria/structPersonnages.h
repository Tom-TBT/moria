/* 
 * File:   structPerso.h
 * Author: tom
 *
 * Created on 1 août 2015, 11:46
 */

#ifndef STRUCTPERSO_H
#define	STRUCTPERSO_H

#define TAILLE_SAC 10
#define TAILLE_EQUIP 8  // 1 casque, 1 armure, 1 bottes, 1 collier, 2 anneaux,
// 1 arme, 1 carquois

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
    int sac[TAILLE_SAC][4]; //1:Nom   2:DecouvertO/N   3:Modificateur   4:Qtité
    int equipements[TAILLE_EQUIP][3]; //1:Nom   2:DecouvertO/N   3:Modificateur
} Heros;

enum {
    CASQUE_EQ, ARMURE_EQ, BOTTES_EQ, ANNEAUG_EQ, ANNEAUD_EQ,
    COLLIER_EQ, ARME_EQ, CARQUOIS_EQ
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

