#include "monstre.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//
// Created by juliedespre, dorapapai on 26/11/22.
//

//création des monstres
monstre creerMonstre(int p,int d, int a,int pX,int pY){
    monstre monMonstre=(monstre)malloc(sizeof(struct monstre));
    //caractéristiques des monstres
    monMonstre->pv=p;
    monMonstre->def=d;
    monMonstre->attaque=a;
    monMonstre->positionX=pX;
    monMonstre->positionY=pY;
    return monMonstre;
}
//création d'une liste contenant les monstres
listeEnnemi creationMonstre(int nbMonstre){
    //creation des monstres avec des caractéristiques aleatoire
    monstre monstre1= creerMonstre((rand()%5)+1,(rand()%2)+1,(rand()%3)+1,(rand()%40)+2,(rand()%13)+2);
    listeEnnemi l=creerListeEnnemi(monstre1);
    for(int i = 1; i<nbMonstre; i++){
        monstre monMonstre= creerMonstre((rand()%30)+10,(rand()%5)+1,(rand()%6)+6,(rand()%40)+2,(rand()%13)+2);
        ajouterEnnemi(l,monMonstre);
    }
    return l;
}

//enlève monstre de la liste et désalloue la mémoire allouée lors de la creation du monstre
listeEnnemi cleanEnnemi(monstre m1,listeEnnemi l,int* n){
    if (l==NULL) return NULL;
    else if (!collision(m1,l->e)) {
        l->next = cleanEnnemi(m1,l->next,n);
        return l;
    }
    else if (l->e->pv<=0){//lorsque le monstre est mort
        (*n)--;
        listeEnnemi laux=l->next;
        free(l);
        return laux;
    }
    else return l;
}

bool combat(monstre m1,listeEnnemi l,int action){// premiere étape
    if (l==NULL) return true;
    else if (!collision(m1,l->e)) return combat(m1,l->next,action);
    //attaque 1 "classique"
    if (action==1){
        m1->pv-=l->e->attaque-m1->def;//mon monstre perd pv attaque du monstre - défense de mon monstre
        l->e->pv-=m1->attaque-l->e->def;//attaque monstre prenant en compte sa défense
    }
    else if (action ==2){
        m1->pv-=l->e->attaque; //pv mon monstre - attaque ennemi
        l->e->pv-=2*m1->attaque-l->e->def;//prete pv du monstre 2*attque de mon monstre - def du monstre
    }
    if (m1->pv>0 && l->e->pv>0) return true;//continu le combat tant que mon monstre ou l'ennemi on des pv
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

void spritesEnnemis(listeEnnemi ennemis,int nbMonstre,SDL_Rect* SrcRSmo,SDL_Rect* DestRSmo,int smokeW,int smokeH,int fenetreW,int fenetreH,int nbCol,int nbLig){
    listeEnnemi l=ennemis;
    for (int i=0;i<nbMonstre;i++) {
        //permet de mettre une image spéciale pour visualiser l'emplacement des monstres sur le plateau de jeux
        SrcRSmo[i].x = 0;
        SrcRSmo[i].y = smokeH/2;
        SrcRSmo[i].w = (smokeW / 4); // Largeur de l’objet en pixels de la texture
        SrcRSmo[i].h = smokeH / 4; // Hauteur de l’objet en pixels de la texture
        DestRSmo[i].x = fenetreW / nbCol * l->e->positionX;
        DestRSmo[i].y = fenetreH / nbLig * l->e->positionY;
        DestRSmo[i].w = smokeW / nbCol * 15;//largeur de la smoke
        DestRSmo[i].h = smokeH / nbLig * 4;//hauteur de la smoke
        l=l->next;
    }
}

