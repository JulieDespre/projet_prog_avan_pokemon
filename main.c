//
// Created by juliedespre, dorapapai on 14/11/22.
//
#include <time.h>
#include "fonctions_fichiers.h"
#include "monstre.h"

int main(void) {

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
    int nbLig = 0;
    int nbCol = 0;
    srand(time(NULL)); // initialisation de rand pour placement des monstres aléatoire

    taille_fichier("terrain.txt", &nbLig, &nbCol);
    char **tab = lire_fichier("terrain.txt"); // passer fichier d'entrée txt en tab
    afficher_tab_2D(tab, nbLig, nbCol);


    //code tp1 ouvrir une fenêtre
    SDL_Window *fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

// Créer la fenêtre
    // dimension de la fenetre de jeux dimension en fonction du nombre de cases du fichier txt
    int fenetreW = 1505, fenetreH = 640;
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, fenetreW, fenetreH, SDL_WINDOW_RESIZABLE);
    if (fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer *ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture *fond = charger_image("pavage_perso.bmp", ecran);
    //Récupérer largeur et largeur de la texture avec SDL_QueryTexture
    int objetW;
    int objetH;
    //recupère taille objet
    SDL_QueryTexture(fond, NULL, NULL, &objetW, &objetH);
    SDL_Rect DestR_sprite[nbLig][nbCol], SrcR_sprite[nbLig][nbCol];
    //placement du pavages du plateau a partir du fichier txt
    for (int i = 0; i < nbLig; i++) {
        for (int j = 0; j < nbCol; j++) {
            SrcR_sprite[i][j].x = objetW / 9 * (((int) tab[i][j] - 48) % 9); // car char en int codé en ascii 0 = 48
            SrcR_sprite[i][j].y = objetH / 5 * (((int) tab[i][j] - 48) / 5);
            SrcR_sprite[i][j].w = objetW / 9; // Largeur de l’objet en pixels de la texture
            SrcR_sprite[i][j].h = objetH / 5; // Hauteur de l’objet en pixels de la texture
            DestR_sprite[i][j].x = fenetreW / nbCol * j;
            DestR_sprite[i][j].y = fenetreH / nbLig * i;
            DestR_sprite[i][j].w = fenetreW / nbCol; // Largeur du sprite
            DestR_sprite[i][j].h = fenetreH / nbLig; // Hauteur du sprite
        }
    }
    //placement du rectangle attaque 1
    SDL_Rect DestR_touche1, SrcR_touche1;
    SrcR_touche1.x = objetW / 9 * (( 6 ) % 9);
    SrcR_touche1.y = objetH / 5 * (( 6 ) / 5);
    SrcR_touche1.w = objetW / 9; // Largeur de l’objet en pixels de la texture
    SrcR_touche1.h = objetH / 5; // Hauteur de l’objet en pixels de la texture
    DestR_touche1.x = 7*fenetreW/12;
    DestR_touche1.y = 4*fenetreH/6 ;
    DestR_touche1.w = fenetreW/6 ; // Largeur du sprite
    DestR_touche1.h = fenetreH/20 ; // Hauteur du sprite

    //placement du rectangle attaque 2
    SDL_Rect DestR_touche2, SrcR_touche2;
    SrcR_touche2.x = objetW / 9 * (( 6 ) % 9);
    SrcR_touche2.y = objetH / 5 * (( 6 ) / 5);
    SrcR_touche2.w = objetW / 9; // Largeur de l’objet en pixels de la texture
    SrcR_touche2.h = objetH / 5; // Hauteur de l’objet en pixels de la texture
    DestR_touche2.x = 7*fenetreW/12;
    DestR_touche2.y = 5*fenetreH/6 ;
    DestR_touche2.w = fenetreW/6 ; // Largeur du sprite
    DestR_touche2.h = fenetreH/20 ; // Hauteur du sprite

    //mise en place d'un fond_spécial pour les combats
    SDL_Texture *fond2 = charger_image("combat_ombre.bmp", ecran);
    int objet2W;
    int objet2H;
    //recupère taille objet
    SDL_QueryTexture(fond, NULL, NULL, &objet2W, &objet2H);
    SDL_Rect DestR_fond2, SrcR_fond2;
    //placement du fond dans la fenètre de jeux
    SrcR_fond2.x = 0;
    SrcR_fond2.y = 0;
    SrcR_fond2.w = objet2W;
    SrcR_fond2.h = objet2H;
    DestR_fond2.x = 0;
    DestR_fond2.y = 0;
    DestR_fond2.w = fenetreW;
    DestR_fond2.h = fenetreH;

// Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
        SDL_Texture *sprites = charger_image_transparente("perso.bmp", ecran, r, g, b);
        //Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
        SDL_Surface *surface = SDL_LoadBMP("perso.bmp");
        Uint32 key = SDL_MapRGB(surface->format, r, g, b);
        SDL_QueryTexture(sprites, &key, NULL, &objetW, &objetH);
        SDL_Rect DestR_perso, SrcR_perso;
        //positionner le sprite du personnage sur la carte
        SrcR_perso.x = 0;
        SrcR_perso.y = 0;
        SrcR_perso.w = objetW / 3; // Largeur de l’objet en pixels de la texture
        SrcR_perso.h = objetH / 4; // Hauteur de l’objet en pixels de la texture
        DestR_perso.x = 0;
        DestR_perso.y = 0;
        DestR_perso.w = objetW / nbCol * 2; // Largeur du sprite
        DestR_perso.h = objetH / nbLig / 1.5; // Hauteur du sprite

        //creation "aléatoire" des monstes
        int nbMonstre=20;
        //liste qui stocke les ennemis sur la carte
        listeEnnemi ennemis = creationMonstre(nbMonstre);

        // Charger l’image avec la transparence
        r = 255, g = 255, b = 255;
        SDL_Texture *smoke = charger_image_transparente("smoke.bmp", ecran, r, g, b);
        //récupérer objet (fumees), sert visualisation emplacement des monstres
        int smokeW;
        int smokeH;
        //charger l'image permettant la visualisation des monstres
        SDL_Surface *surfaceCit = SDL_LoadBMP("smoke.bmp");
        Uint32 keyCit = SDL_MapRGB(surfaceCit->format, r, g, b);
        SDL_QueryTexture(smoke, &keyCit, NULL, &smokeW, &smokeH);
        SDL_Rect SrcRSmo[nbMonstre], DestRSmo[nbMonstre];
        spritesEnnemis(ennemis,nbMonstre,SrcRSmo,DestRSmo,smokeW,smokeH,fenetreW,fenetreH,nbCol,nbLig);

        //Variable du jeu
        //int etat = 0;
        bool encombat=false;
        int action=0;
        //créer mon Monstre qui combat les ennemis
        monstre monMonstre = creerMonstre(170, 5, 10,0,0);

    // Boucle principale

        while (!terminer) {

            if (collisionListe(monMonstre, ennemis)) encombat = true;
            else encombat=false;
            SDL_RenderClear(ecran);

            for (int i = 0; i < nbLig; i++) {
                for (int j = 0; j < nbCol; j++) {
                    if (!encombat) {
                        SDL_RenderCopy(ecran, fond, &SrcR_sprite[i][j], &DestR_sprite[i][j]);
                        spritesEnnemis(ennemis,nbMonstre,SrcRSmo,DestRSmo,smokeW,smokeH,fenetreW,fenetreH,nbCol,nbLig);
                        for (int i=0;i<nbMonstre;i++) {
                            SDL_RenderCopy(ecran, smoke, &SrcRSmo[i], &DestRSmo[i]);
                        }
                        SDL_RenderCopy(ecran, sprites, &SrcR_perso, &DestR_perso);
                    }
                    else {
                        SDL_RenderCopy(ecran, fond2, &SrcR_fond2, &DestR_fond2);
                        SDL_RenderCopy(ecran, fond, &SrcR_touche1, &DestR_touche1);
                        SDL_RenderCopy(ecran, fond, &SrcR_touche2, &DestR_touche2);
                    }
                }
            }
            if (encombat) {
                encombat=combat(monMonstre, ennemis,action);
                if (!(monMonstre->pv>0)) {
                    printf("Vous êtes mort !\n");
                    terminer = true;
                } else {
                    printf("Il te reste %d pv.\n", monMonstre->pv);
                    if (ennemis->next == NULL) printf("Vous avez gagnez!");
                }
                ennemis=cleanEnnemi(monMonstre,ennemis,&nbMonstre);
                action=0;
            }

            while (SDL_PollEvent(&evenements)) {
                if (encombat) {
                    int x,y;
                    switch (evenements.type) {
                        case SDL_MOUSEBUTTONDOWN:
                            switch(evenements.button.button)
                            {
                                case SDL_BUTTON_LEFT:
                                    SDL_GetMouseState(&x,&y);
                                    if (x>=7*fenetreW/12 && x<=7*fenetreW/12+fenetreW/6 && y>=4*fenetreH/6 && y<=4*fenetreH/6+fenetreH/20){
                                        action=1;
                                    }
                                    else if (x>=7*fenetreW/12 && x<=7*fenetreW/12+fenetreW/6 && y>=5*fenetreH/6 && y<=5*fenetreH/6+fenetreH/20){
                                        action=2;
                                    }
                                    break;
                                case SDL_BUTTON_RIGHT:
                                    encombat=false;
                                    (SrcR_perso).x = 0;
                                    (SrcR_perso).y = objetH/2;
                                    if ((DestR_perso).x + fenetreW / nbCol < fenetreW &&
                                        (tab[(DestR_perso).y / (fenetreH / nbLig)][(DestR_perso).x / (fenetreW / nbCol) + 1] == '0'||tab[(DestR_perso).y / (fenetreH / nbLig)][(DestR_perso).x / (fenetreW / nbCol) + 1] == '4')) {
                                        (DestR_perso).x = ((DestR_perso).x + fenetreW / nbCol);
                                        monMonstre->positionX++;
                                    }
                                    break;
                            }
                            break;
                    }
                } else {
                    switch (evenements.type) {
                        case SDL_QUIT:
                            terminer = true;
                            break;
                        case SDL_KEYUP:
                            //case SDL_KEYDOWN:
                            deplacement(monMonstre, &evenements, &DestR_perso, &SrcR_perso, tab, fenetreW,
                                               fenetreH, nbCol, nbLig,
                                               objetH, objetW);
                            if ((evenements.key.keysym.sym == SDLK_q) ||
                                (evenements.key.keysym.sym == SDLK_ESCAPE))
                                terminer = true;
                    }
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