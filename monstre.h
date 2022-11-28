//
// Created by juliedespre, dorapapai on 26/11/22.
//

#ifndef MAIN_MONSTRE_H
#define MAIN_MONSTRE_H
#include<stdio.h>
#include<stdlib.h>

typedef struct monstre * monstre;

struct monstre{
    int pv;
    int def;
    int attaque;
    int positionX;
    int positionY;
};

typedef struct Ennemi * listeEnnemi;

struct Ennemi{
    monstre e;
    listeEnnemi next;
};

listeEnnemi creerListeEnnemi(monstre e);
void ajouterEnnemi(listeEnnemi l,monstre e);
monstre creerEnnemi(int p,int d, int a, int x, int y);
monstre creerMonstre(int p,int d, int a);
int combat(monstre m1,monstre m2);
#endif //MAIN_MONSTRE_H
