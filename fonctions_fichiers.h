//
// Created by juliedespre on 01/11/22.
//

#ifndef PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
#define PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
#include<stdio.h>
#include<stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_ttf.h>

char** allouer_tab_2D(int n, int m);
char** initialiser_tab_2D(int n, int m);
void desallouer_tab_2D(char** tab, int n);
void afficher_tab_2D(char** tab, int n, int m);
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol);
char** lire_fichier(const char* nomFichier);
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau);
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m);
SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer);
SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b);
SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color);
void deplacement (SDL_Event *evenements,SDL_Rect *DestR_chat,SDL_Rect *SrcR_chat,char** tab,int fenetreW,int fenetreH,int nbCol,int nbLig,int objetH,int objetW);
#endif //PROJET_PROG_AVAN_FONCTIONS_FICHIERS_H
