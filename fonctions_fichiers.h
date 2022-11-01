//
// Created by juliedespre on 01/11/22.
//

#ifndef PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
#define PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
#include<stdio.h>
#include<stdlib.h>

char** allouer_tab_2D(int n, int m);
char** initialiser_tab_2D(int n, int m);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);

#endif //PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
