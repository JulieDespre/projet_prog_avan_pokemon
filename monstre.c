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
    monMonstre->lvl=0;
    return monMonstre;
}
//création d'une liste contenant les monstres et remplis avec des monstres automatiquement
listeEnnemi creationMonstre(int nbMonstre,char** tab,int nbLig,int nbCol,int diff){//nblig et nbcol
    //creation des monstres avec des caractéristiques aleatoire
    monstre monstre1= creerMonstre(40+40*diff,7+3*diff,10+5*diff,(nbCol-1)/diff,nbLig/2);
    listeEnnemi l=creerListeEnnemi(monstre1);
    for(int i = 1; i<nbMonstre; i++){
        int pX=(rand()%nbCol),pY=(rand()%nbLig);
        while ((tab[pY][pX]!='0'&&tab[pY][pX]!='4')||pX+pY==0){
            pX=(rand()%nbCol);
            pY=(rand()%nbLig);
        }
        monstre monMonstre= creerMonstre((rand()%30)*diff+10,(rand()%5)*diff+1,(rand()%6)*diff+6,pX,pY);
        ajouterEnnemi(l,monMonstre);
    }
    return l;
}

//enlève monstre de la liste et désalloue la mémoire allouée lors de la creation du monstre
listeEnnemi cleanEnnemi(monstre m1,listeEnnemi l,int* n,int* ecr,SDL_Rect* DestR_perso){
    if (l==NULL) return NULL;
    else if (!collision(m1,l->e)) {
        l->next = cleanEnnemi(m1,l->next,n,ecr,DestR_perso);
        return l;
    }
    else if (l->e->pv<=0){//lorsque le monstre est mort
        if (l->e->def>9) {
            (*ecr)++;
            DestR_perso->x=0;
            m1->pv+=100;
        }
        (*n)--;
        listeEnnemi laux=l->next;
        free(l);
        m1->lvl++;//lorsque monstre est mort perso gagne 1 niveau
        return laux;
    }
    else return l;
}

bool combat(monstre m1,listeEnnemi l,int action){// premiere étape
    if (l==NULL) return true;
    else if (!collision(m1,l->e)) return combat(m1,l->next,action);
    //attaque 1 "classique"
    if (action==1){
        if (l->e->attaque-(m1->def+m1->lvl/2)>0) m1->pv-=l->e->attaque-(m1->def+m1->lvl/2);//mon monstre perd pv attaque du monstre - défense de mon monstre
        if ((m1->attaque+m1->lvl)-l->e->def>0) l->e->pv-=(m1->attaque+m1->lvl)-l->e->def;
    }
    else if (action ==2){
        m1->pv-=l->e->attaque; //pv mon monstre - attaque ennemi
        l->e->pv-=2*(m1->attaque+m1->lvl)-l->e->def;//prete pv du monstre 2*attque de mon monstre ne prend pas notre def en compte
    }
    if (m1->pv>0 && l->e->pv>0) return true;//continu le combat tant que mon monstre ou l'ennemi on des pv
    else return false;
}
//creer une liste d'ennemis
listeEnnemi creerListeEnnemi(monstre e){
    listeEnnemi l=(listeEnnemi)malloc(sizeof(struct Ennemi));
    l->e=e;
    l->next=NULL;
    return l;
}
//créer uen liste vide
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
//vérifie si la liste des ennemis est vide ou non
bool EstVide (listeEnnemi l){
    if (l->next == NULL) {
        return 1;
    } else {
        return 0;
    }
}
//savoir si perso et monstre sont sur la même case
bool collision(monstre m1,monstre m2){
    return m1->positionX==m2->positionX && m1->positionY==m2->positionY;
}
//savoir si perso et monstre aléatoire de la liste d'ennemis sont sur la même case
bool collisionListe(monstre m1,listeEnnemi l,char*msg){
    if (l==NULL) return false;
    monstre m2=l->e;
    if (m1->positionX==m2->positionX && m1->positionY==m2->positionY) {
        sprintf(msg,"PV: %d Attaque: %d Defense: %d", m2->pv,m2->attaque+m2->lvl,m2->def+m2->lvl/2);
        return true;
    }
    else return collisionListe(m1,l->next,msg);
}
//permet de visualiser le placement des monstres sur la carte pour tous les monstres de la liste ennemis
void spritesEnnemis(listeEnnemi ennemis,int nbMonstre,SDL_Rect* SrcRSmo,SDL_Rect* DestRSmo,int smokeW,int smokeH,int fenetreW,int fenetreH,int nbCol,int nbLig){
    listeEnnemi l=ennemis;
    l=l->next;
    for (int i=1;i<nbMonstre;i++) {
        //permet de mettre une image spéciale pour visualiser l'emplacement des monstres sur le plateau de jeux
        SrcRSmo[i].x = 0;
        SrcRSmo[i].y = smokeH/2;
        SrcRSmo[i].w = smokeW / 4; // Largeur de l’objet en pixels de la texture
        SrcRSmo[i].h = smokeH / 4; // Hauteur de l’objet en pixels de la texture
        DestRSmo[i].x = fenetreW / nbCol * l->e->positionX;
        DestRSmo[i].y = fenetreH / nbLig * l->e->positionY-10;
        DestRSmo[i].w = fenetreW / nbCol ;//largeur de la smoke
        DestRSmo[i].h = fenetreH / nbLig *1.5;//hauteur de la smoke
        l=l->next;
    }
}

void save(int ecr,monstre m1,listeEnnemi ennemis){
    listeEnnemi l=ennemis;
    FILE *fichier = NULL;
    fichier = fopen("save.txt", "w");//a pour écrire dans un fichier déjà écrit sinon w pour écrire dans un fichier
    fputc((char)ecr,fichier);
    fputc((char)(m1->pv),fichier);
    fputc((char)(m1->attaque),fichier);
    fputc((char)(m1->def),fichier);
    fputc((char)(m1->positionX),fichier);
    fputc((char)(m1->positionY),fichier);
    fputc((char)(m1->lvl),fichier);
    while (l!=NULL){
        fputc((char)(l->e->pv),fichier);
        fputc((char)(l->e->def),fichier);
        fputc((char)(l->e->attaque),fichier);
        fputc((char)(l->e->positionX),fichier);
        fputc((char)(l->e->positionY),fichier);
        l=l->next;
    }
    fputc(255,fichier);
    fclose(fichier);
}

listeEnnemi load(int* ecr,monstre m1,int* nb){
    FILE* fichier = NULL ;
    fichier = fopen("save.txt", "r") ;
    *ecr=fgetc(fichier);
    m1->pv=fgetc(fichier);
    m1->attaque=fgetc(fichier);
    m1->def=fgetc(fichier);
    m1->positionX=fgetc(fichier);
    m1->positionY=fgetc(fichier);
    m1->lvl=fgetc(fichier);
    int c = fgetc(fichier);
    int d=fgetc(fichier);
    int a=fgetc(fichier);
    int pX=fgetc(fichier);
    int pY=fgetc(fichier);
    monstre m = creerMonstre(c,d,a,pX,pY);
    c = fgetc(fichier);
    listeEnnemi  l = creerListeEnnemi(m);
    printf("%d\n",c);
    *nb=1;
    while (c!=255 && c!=0){
        d=fgetc(fichier);
        a=fgetc(fichier);
        pX=fgetc(fichier);
        pY=fgetc(fichier);
        monstre m = creerMonstre(c,d,a,pX,pY);
        ajouterEnnemi(l,m);
        c = fgetc(fichier);
        (*nb)++;
    }
    fclose(fichier);
    return l;
}

