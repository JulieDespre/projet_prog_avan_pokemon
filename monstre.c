#include "monstre.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//
// Created by juliedespre, dorapapai on 26/11/22.
//
monstre creerMonstre(int p,int d, int a){
    monstre monMonstre=(monstre)malloc(sizeof(struct monstre));
    monMonstre->pv=p;
    monMonstre->def=d;
    monMonstre->attaque=a;
    return monMonstre;
}

monstre creerEnnemi(int p,int d, int a, int x, int y){
    monstre Ennemi=(monstre)malloc(sizeof(struct monstre));
    Ennemi->pv=p;
    Ennemi->def=d;
    Ennemi->attaque=a;
    Ennemi->positionX=x;
    Ennemi->positionY=y;
    return Ennemi;
}

int combat(monstre m1,monstre m2){// premiere étape
    while (m1->pv>0 && m2->pv>0){
        m1->pv-=m2->attaque-m1->def;
        m2->pv-=m1->attaque-m2->def;
    }
    if (m1->pv>0) return 1;
    else return 0;
}

/*int combat(monstre m1, listeEnnemi lm){
    while (m2 != NULL && m1->pv>0 && m2->pv>0){

        m1->pv-=m2->attaque-m1->def;
        m2->pv-=m1->attaque-m2->def;
    }
    if (m1->pv>0) return 1;
    else return 0;
}*/

listeEnnemi creerListeEnnemi(monstre e){
    listeEnnemi l=(listeEnnemi)malloc(sizeof(struct Ennemi));
    l->e=e;
    l->next=NULL;
    return l;
}

void ajouterEnnemi(listeEnnemi l,monstre e){
    if (l->next!=NULL){
        ajouterEnnemi(l->next,e);
    }
    else{
        listeEnnemi ladd=(listeEnnemi)malloc(sizeof(struct Ennemi));
        ladd->e=e;
        ladd->next=NULL;
        l->next=ladd;
    }
}

bool EstVide (listeEnnemi l){
    if (l->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}