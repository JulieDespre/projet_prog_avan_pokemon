#include "monstre.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//
// Created by juliedespre, dorapapai on 26/11/22.
//

monstre creerMonstre(int p,int d, int a,int pX,int pY){
    monstre monMonstre=(monstre)malloc(sizeof(struct monstre));
    monMonstre->pv=p;
    monMonstre->def=d;
    monMonstre->attaque=a;
    monMonstre->positionX=pX;
    monMonstre->positionY=pY;
    return monMonstre;
}
//création des monstres
listeEnnemi creationMonstre(int nbMonstre){
    monstre monstre1= creerMonstre((rand()%4)+1,(rand()%2)+1,(rand()%3)+1,(rand()%40)+2,(rand()%13)+2);
    listeEnnemi l=creerListeEnnemi(monstre1);
    for(int i = 1; i<nbMonstre; i++){
        monstre monMonstre= creerMonstre((rand()%50)+10,(rand()%5)+1,(rand()%10)+6,(rand()%40)+2,(rand()%13)+2);
        ajouterEnnemi(l,monMonstre);
            //monstre ennemi = creerMonstre(pv, def, att, pX, pY);
           // ajouterEnnemi(ennemis, ennemi);
    }
    return l;
}


listeEnnemi cleanEnnemi(monstre m1,listeEnnemi l){
    if (l==NULL) return NULL;
    else if (!collision(m1,l->e)) {
        l->next = cleanEnnemi(m1,l->next);
        return l;
    }
    else{
        listeEnnemi laux=l->next;
        free(l);
        return laux;
    }
}

bool combat(monstre m1,listeEnnemi l){// premiere étape
    if (l==NULL) return true;
    else if (!collision(m1,l->e)) return combat(m1,l->next);
    while (m1->pv>0 && l->e->pv>0){
        m1->pv-=l->e->attaque-m1->def;
        l->e->pv-=m1->attaque-l->e->def;
    }
    if (m1->pv>0) return true;
    else return false;
}

listeEnnemi creerListeEnnemi(monstre e){
    listeEnnemi l=(listeEnnemi)malloc(sizeof(struct Ennemi));
    l->e=e;
    l->next=NULL;
    return l;
}
listeEnnemi creerListeEnnemiVide(){
    listeEnnemi l=(listeEnnemi)malloc(sizeof(struct Ennemi));
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

bool collision(monstre m1,monstre m2){
    return m1->positionX==m2->positionX && m1->positionY==m2->positionY;
}

bool collisionListe(monstre m1,listeEnnemi l){
    if (l==NULL) return false;
    monstre m2=l->e;
    if (m1->positionX==m2->positionX && m1->positionY==m2->positionY) return true;
    else return collisionListe(m1,l->next);
}



