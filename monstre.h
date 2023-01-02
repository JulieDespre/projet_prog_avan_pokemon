//
// Created by juliedespre, dorapapai on 26/11/22.
//

#ifndef MAIN_MONSTRE_H
#define MAIN_MONSTRE_H
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct monstre * monstre;

struct monstre{
    int pv;
    int def;
    int attaque;
    int positionX;
    int positionY;
    int lvl;
};

typedef struct Ennemi * listeEnnemi;

struct Ennemi{
    monstre e;
    listeEnnemi next;
};

listeEnnemi creerListeEnnemi(monstre e);
listeEnnemi creerListeEnnemiVide();
void ajouterEnnemi(listeEnnemi l,monstre e);
listeEnnemi cleanEnnemi(monstre m1,listeEnnemi l,int* nbMonstre,int* ecr,SDL_Rect* DestR_perso);
monstre creerMonstre(int p,int d, int a,int pX,int pY);
bool combat(monstre m1,listeEnnemi e,int action);
bool collision(monstre m1,monstre m2);
bool collisionListe(monstre m1,listeEnnemi l,char* msg);
listeEnnemi creationMonstre(int nbMonstre,char** tab,int nbLig,int nbCol,int diff);
void spritesEnnemis(listeEnnemi ennemis,int nbMonstre,SDL_Rect* SrcRCit,SDL_Rect* DestRCit,int citrouilleW,int citrouilleH,int fenetreW,int fenetreH,int nbCol,int nbLig);

#endif //MAIN_MONSTRE_H
