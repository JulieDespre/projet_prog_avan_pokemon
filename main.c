//
// Created by juliedespre on 01/11/22.
//
#include "fonctions_fichiers.h"

int main(void){
    char** tab=initialiser_tab_2D(5,10);
    //afficher_tab_2D(tab,5,10);
    int nbLig =0;
    int nbCol=0;
    taille_fichier("tabCaracteres.txt",&nbLig,&nbCol);
    printf ("%d--%d \n", nbLig, nbCol);
    char** tab2=lire_fichier("tabCaracteres.txt");
    afficher_tab_2D(tab2,nbLig,nbCol);
}