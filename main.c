//
// Created by juliedespre on 01/11/22.
//
#include "fonctions_fichiers.h"

int main(void){
    //exercice 1 et 2
    //char** tab=initialiser_tab_2D(5,10);
    //afficher_tab_2D(tab,5,10);
    //int nbLig =0;
    //int nbCol=0;
    //taille_fichier("tabCaracteres.txt",&nbLig,&nbCol);
    //printf ("%d--%d \n", nbLig, nbCol);
    //char** tab2=lire_fichier("tabCaracteres.txt");
    //afficher_tab_2D(tab2,nbLig,nbCol);
    //char** tab3=modifier_caractere(tab2, nbLig, nbCol, 'b', '2');
    //afficher_tab_2D(tab3,nbLig,nbCol);
    //ecrire_fichier("bob", tab3, nbLig, nbCol);
    //ecrire_fichier("bob", tab2, nbLig, nbCol);


    //exercice 3
    int nbLig =0;
    int nbCol=0;
    taille_fichier("terrain.txt",&nbLig,&nbCol);
    char** tab = lire_fichier("terrain.txt");
    afficher_tab_2D(tab,nbLig,nbCol);


    //code tp1 ouvrir une fenêtre
    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

// Créer la fenêtre
int fenetreW=1224,fenetreH=640;
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, fenetreW, fenetreH, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "pavage.bmp", ecran );

    //Récupérer largeur et hargeur de la texture avec SDL_QueryTexture
    int objetW;
    int objetH;
    //recupère taille objet
    SDL_QueryTexture(fond,NULL,NULL,&objetW,&objetH);
    SDL_Rect DestR_sprite[nbLig][nbCol], SrcR_sprite[nbLig][nbCol];
    printf("%d %d\n",objetW,objetH);
    for(int i=0; i<nbLig; i++){
        for(int j=0; j<nbCol; j++) {
            SrcR_sprite[i][j].x = objetW / 16 * (((int)tab[i][j]-48)%16);
            SrcR_sprite[i][j].y = objetH / 10 * (((int)tab[i][j]-48)/16);
            SrcR_sprite[i][j].w = objetW / 16; // Largeur de l’objet en pixels de la texture
            SrcR_sprite[i][j].h = objetH / 10; // Hauteur de l’objet en pixels de la texture
            DestR_sprite[i][j].x = fenetreW / nbCol * j;
            DestR_sprite[i][j].y = fenetreH / nbLig * i;
            DestR_sprite[i][j].w = fenetreW / nbCol; // Largeur du sprite
            DestR_sprite[i][j].h = fenetreH / nbLig; // Hauteur du sprite
        }
    }



// Boucle principale
    while(!terminer) {
        SDL_RenderClear(ecran);
       for(int i=0; i<nbLig; i++) {
            for (int j = 0; j < nbCol; j++) {
                SDL_RenderCopy(ecran, fond, &SrcR_sprite[i][j], &DestR_sprite[i][j]);
            }
        }
        SDL_PollEvent(&evenements);
        switch (evenements.type) {
            case SDL_QUIT:
                terminer = true;
                break;
            case SDL_KEYDOWN:
                switch (evenements.key.keysym.sym) {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                    case SDLK_i:
                        terminer = true;
                        break;
                    case SDLK_j:
                        printf("coucou");
                        break;
                }
        }
        SDL_RenderPresent(ecran);
    }

// Libérer de la mémoire
    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(ecran);
// Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return 0;

}

