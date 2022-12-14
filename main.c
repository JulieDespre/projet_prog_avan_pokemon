//
// Created by juliedespre, dorapapai on 14/11/22.
//
#include <time.h>
#include "fonctions_fichiers.h"
#include "monstre.h"

int main(void) {

    int nbLig = 0;
    int nbCol = 0;
    int nbLig2 = 0;
    int nbCol2 = 0;
    srand(time(NULL)); // initialisation de rand pour placement des monstres aléatoire

    taille_fichier("terrain.txt", &nbLig, &nbCol);
    taille_fichier("terrain2.txt", &nbLig2, &nbCol2);
    char **tab = lire_fichier("terrain.txt"); // passer fichier d'entrée txt en tab
    char **tab2 = lire_fichier("terrain2.txt"); // passer fichier d'entrée txt en tab

    //code tp1 ouvrir une fenêtre
    SDL_Window *fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initadapter taille de fenètre a taille fichier d'entrée SDL langage Cialisation de la SDL: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

// Créer la fenêtre
    // dimension de la fenetre de jeux dimension en fonction du nombre de cases du fichier txt
    int fenetreW = nbCol*60, fenetreH = nbLig*80;
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, fenetreW, fenetreH, SDL_WINDOW_MINIMIZED);
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
            SrcR_sprite[i][j].y = objetH / 4 * (((int) tab[i][j] - 48) / 9);
            SrcR_sprite[i][j].w = objetW / 9.5; // Largeur de l’objet en pixels de la texture
            SrcR_sprite[i][j].h = objetH / 4.1; // Hauteur de l’objet en pixels de la texture
            DestR_sprite[i][j].x = fenetreW / nbCol * j;
            DestR_sprite[i][j].y = fenetreH / nbLig * i;
            DestR_sprite[i][j].w = fenetreW / nbCol; // Largeur du sprite
            DestR_sprite[i][j].h = fenetreH / nbLig; // Hauteur du sprite
        }
    }

    SDL_Rect DestR_sprite2[nbLig2][nbCol2], SrcR_sprite2[nbLig2][nbCol2];
    //placement du pavages du plateau a partir du fichier txt
    for (int i = 0; i < nbLig2; i++) {
        for (int j = 0; j < nbCol2; j++) {
            SrcR_sprite2[i][j].x = objetW / 9 * (((int) tab2[i][j] - 48) % 9); // car char en int codé en ascii 0 = 48
            SrcR_sprite2[i][j].y = objetH / 4 * (((int) tab2[i][j] - 48) / 9);
            SrcR_sprite2[i][j].w = objetW / 9.5; // Largeur de l’objet en pixels de la texture
            SrcR_sprite2[i][j].h = objetH / 4.1; // Hauteur de l’objet en pixels de la texture
            DestR_sprite2[i][j].x = fenetreW / nbCol2 * j;
            DestR_sprite2[i][j].y = fenetreH / nbLig2 * i;
            DestR_sprite2[i][j].w = fenetreW / nbCol2; // Largeur du sprite
            DestR_sprite2[i][j].h = fenetreH / nbLig2; // Hauteur du sprite
        }
    }
    //placement du rectangle attaque 1
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* monMons = charger_image_transparente("mon_fantome.bmp", ecran,r,g,b);
//Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
    int monstW;
    int monstH;
    SDL_Surface* surfaceMons1 = SDL_LoadBMP("mon_fantome.bmp");
    Uint32 key = SDL_MapRGB(surfaceMons1->format,r,g,b);
    SDL_QueryTexture(monMons,&key,NULL,&monstW,&monstH);
    SDL_Rect DestR_monMons1, SrcR_monMons1;
    SrcR_monMons1.x = 0;
    SrcR_monMons1.y = 0;
    SrcR_monMons1.w = monstW; // Largeur de l’objet en pixels de la texture
    SrcR_monMons1.h = monstH; // Hauteur de l’objet en pixels de la texture
    DestR_monMons1.x = 2*fenetreW/12;
    DestR_monMons1.y = fenetreH/2-100 ;
    DestR_monMons1.w = fenetreW/4 ; // Largeur du sprite
    DestR_monMons1.h = fenetreH/3 ; // Hauteur du sprite

    SDL_Texture* atta1 = charger_image_transparente("attaque1.bmp", ecran,r,g,b);
//Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
    int attaW;
    int attaH;
    SDL_Surface* surface1 = SDL_LoadBMP("attaque1.bmp");
    key = SDL_MapRGB(surface1->format,r,g,b);
    SDL_QueryTexture(atta1,&key,NULL,&attaW,&attaH);
    SDL_Rect DestR_touche1, SrcR_touche1;
    SrcR_touche1.x = 0;
    SrcR_touche1.y = attaW/5;
    SrcR_touche1.w = attaW; // Largeur de l’objet en pixels de la texture
    SrcR_touche1.h = attaH/2; // Hauteur de l’objet en pixels de la texture
    DestR_touche1.x = 7*fenetreW/12;
    DestR_touche1.y = 4*fenetreH/6 ;
    DestR_touche1.w = fenetreW/6 ; // Largeur du sprite
    DestR_touche1.h = fenetreH/15 ; // Hauteur du sprite

    //placement du rectangle attaque 2
    SDL_Texture* atta2 = charger_image_transparente("attaque2.bmp", ecran,r,g,b);
//Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
    SDL_Surface* surface2 = SDL_LoadBMP("attaque2.bmp");
    key = SDL_MapRGB(surface2->format,r,g,b);
    SDL_QueryTexture(atta1,&key,NULL,&attaW,&attaH);
    SDL_Rect DestR_touche2, SrcR_touche2;
    SrcR_touche2.x = 0;
    SrcR_touche2.y = attaW/5;
    SrcR_touche2.w = attaW; // Largeur de l’objet en pixels de la texture
    SrcR_touche2.h = attaH/2; // Hauteur de l’objet en pixels de la texture
    DestR_touche2.x = 7*fenetreW/12;
    DestR_touche2.y = 9*fenetreH/12 ;
    DestR_touche2.w = fenetreW/6 ; // Largeur du sprite
    DestR_touche2.h = fenetreH/15 ; // Hauteur du sprite

    //mise en place d'un fond_spécial pour les combats
    SDL_Texture *fond2 = charger_image("combat_ombre.bmp", ecran);
    int objet2W;
    int objet2H;
    //recupère taille objet
    SDL_QueryTexture(fond2, NULL, NULL, &objet2W, &objet2H);
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

    SDL_Texture *fonddeb = charger_image("deb_ok.bmp", ecran);
    //recupère taille objet
    SDL_QueryTexture(fonddeb, NULL, NULL, &objet2W, &objet2H);
    SDL_Rect DestR_fonddeb, SrcR_fonddeb;
    //placement du fond dans la fenètre de jeux
    SrcR_fonddeb.x = 0;
    SrcR_fonddeb.y = 0;
    SrcR_fonddeb.w = objet2W;
    SrcR_fonddeb.h = objet2H;
    DestR_fonddeb.x = 0;
    DestR_fonddeb.y = 0;
    DestR_fonddeb.w = fenetreW;
    DestR_fonddeb.h = fenetreH;

    SDL_Texture *fondwin = charger_image("fond_win.bmp", ecran);
    //recupère taille objet
    SDL_QueryTexture(fondwin, NULL, NULL, &objet2W, &objet2H);
    SDL_Rect DestR_fondwin, SrcR_fondwin;
    //placement du fond dans la fenètre de jeux
    SrcR_fondwin.x = 0;
    SrcR_fondwin.y = 0;
    SrcR_fondwin.w = objet2W;
    SrcR_fondwin.h = objet2H;
    DestR_fondwin.x = 0;
    DestR_fondwin.y = 0;
    DestR_fondwin.w = fenetreW;
    DestR_fondwin.h = fenetreH;

    SDL_Texture *fondgo = charger_image("fond_game_over.bmp", ecran);
    //recupère taille objet
    SDL_QueryTexture(fondgo, NULL, NULL, &objet2W, &objet2H);
    SDL_Rect DestR_fondgo, SrcR_fondgo;
    //placement du fond dans la fenètre de jeux
    SrcR_fondgo.x = 0;
    SrcR_fondgo.y = 0;
    SrcR_fondgo.w = objet2W;
    SrcR_fondgo.h = objet2H;
    DestR_fondgo.x = 0;
    DestR_fondgo.y = 0;
    DestR_fondgo.w = fenetreW;
    DestR_fondgo.h = fenetreH;

    // suivi des points de vie
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./angelina.TTF",28);
    SDL_Color color = {255,255,255,0};
    char msg[100] = "UwU";
    SDL_Texture* texte = charger_texte(msg,ecran,font,color);
    SDL_QueryTexture(texte,&key,NULL,&objetW,&objetH);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = fenetreW/5;
    text_pos.y = fenetreH-100;
    text_pos.w = objetW; // Largeur du texte en pixels (à récupérer)
    text_pos.h = objetH; // Hauteur du texte en pixels (à récupérer)

    SDL_Rect text_pos2; // Position du texte
    text_pos2.x = 3*fenetreW/5-40;
    text_pos2.y = fenetreH/2;
    text_pos2.w = objetW; // Largeur du texte en pixels (à récupérer)
    text_pos2.h = objetH; // Hauteur du texte en pixels (à récupérer)

// Charger l’image avec la transparence pour le personnage
    //Uint8 r = 255, g = 255, b = 255;
        SDL_Texture *sprites = charger_image_transparente("perso.bmp", ecran, r, g, b);
        //Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
        SDL_Surface *surfacePerso = SDL_LoadBMP("perso.bmp");
        Uint32 keyPerso = SDL_MapRGB(surfacePerso->format, r, g, b);
        SDL_QueryTexture(sprites, &keyPerso, NULL, &objetW, &objetH);
        SDL_Rect DestR_perso, SrcR_perso;
        //positionner le sprite du personnage sur la carte
        SrcR_perso.x = 0;
        SrcR_perso.y = 0;
        SrcR_perso.w = objetW / 3; // Largeur de l’objet en pixels de la texture
        SrcR_perso.h = objetH / 4; // Hauteur de l’objet en pixels de la texture
        DestR_perso.x = 0;
        DestR_perso.y = 0;
        DestR_perso.w = fenetreW / nbCol; // Largeur du sprite
        DestR_perso.h = fenetreH / nbLig ; // Hauteur du sprite

        //creation "aléatoire" des monstes
        int nbMonstre=9; // peut être mis en constante, varie selon les niveau ?
        //liste qui stocke les ennemis sur la carte
        listeEnnemi ennemis = creationMonstre(nbMonstre,tab,nbLig,nbCol,1);
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

        SDL_Texture *boss = charger_image_transparente("boss.bmp", ecran, r, g, b);
        int bossW;
        int bossH;
        //charger l'image permettant la visualisation des monstres
        SDL_Surface *surfaceBoss = SDL_LoadBMP("boss.bmp");
        Uint32 keyBoss = SDL_MapRGB(surfaceBoss->format, r, g, b);
        SDL_QueryTexture(boss, &keyBoss, NULL, &bossW, &bossH);
        SDL_Rect SrcRBoss, DestRBoss;
        SrcRBoss.x = 0;
        SrcRBoss.y = 0;
        SrcRBoss.w = bossW; // Largeur de l’objet en pixels de la texture
        SrcRBoss.h = bossH; // Hauteur de l’objet en pixels de la texture
        DestRBoss.x = fenetreW / nbCol * ennemis->e->positionX;
        DestRBoss.y = fenetreH / nbLig * ennemis->e->positionY+10;
        DestRBoss.w = fenetreW / nbCol ;//largeur de la smoke
        DestRBoss.h = fenetreH / nbLig ;//hauteur de la smoke
        SDL_Rect SrcRBosscb, DestRBosscb;
        SrcRBosscb.x = 0;
        SrcRBosscb.y = 0;
        SrcRBosscb.w = bossW; // Largeur de l’objet en pixels de la texture
        SrcRBosscb.h = bossH; // Hauteur de l’objet en pixels de la texture
        DestRBosscb.x = fenetreW / 2+60;
        DestRBosscb.y = fenetreH / 6-50;
        DestRBosscb.w = fenetreW / 4 ;//largeur de la smoke
        DestRBosscb.h = fenetreH / 3 ;//hauteur de la smoke

        SDL_Texture *smokecb = charger_image_transparente("ennemi.bmp", ecran, r, g, b);
        //récupérer objet (fumees), sert visualisation emplacement des monstres
        int smokecbW;
        int smokecbH;
        //charger l'image permettant la visualisation des monstres
        SDL_Surface *surfaceCb = SDL_LoadBMP("ennemi.bmp");
        Uint32 keyCb = SDL_MapRGB(surfaceCb->format, r, g, b);
        SDL_QueryTexture(smokecb, &keyCb, NULL, &smokecbW, &smokecbH);
        SDL_Rect SrcRSmocb, DestRSmocb;
        SrcRSmocb.x = 0;
        SrcRSmocb.y = 0;
        SrcRSmocb.w = smokecbW; // Largeur de l’objet en pixels de la texture
        SrcRSmocb.h = smokecbH; // Hauteur de l’objet en pixels de la texture
        DestRSmocb.x = fenetreW / 2+60;
        DestRSmocb.y = fenetreH / 6-50;
        DestRSmocb.w = fenetreW / 4 ;//largeur de la smoke
        DestRSmocb.h = fenetreH / 3 ;//hauteur de la smoke

        //Variable du jeu
        //int etat = 0;
        bool encombat=false;
        int ecr=0;
        int action=0;
        //créer mon Monstre qui combat les ennemis
        monstre monMonstre = creerMonstre(180, 5, 10,0,0);
        char msg2[100]="UwU";

    // Boucle principale
        while (!terminer) {

            if (collisionListe(monMonstre, ennemis,msg2) && (ecr==1 || ecr==2)) encombat = true;
            else encombat=false;
            SDL_RenderClear(ecran);

            if (!encombat) {
                if (ecr==0){
                    SDL_RenderCopy(ecran, fonddeb, &SrcR_fonddeb, &DestR_fonddeb);
                }
                else if (ecr==1) {
                    for (int i = 0; i < nbLig; i++) {
                        for (int j = 0; j < nbCol; j++) {
                            SDL_RenderCopy(ecran, fond, &SrcR_sprite[i][j], &DestR_sprite[i][j]);
                        }
                    }
                    spritesEnnemis(ennemis, nbMonstre, SrcRSmo, DestRSmo, smokeW, smokeH, fenetreW,fenetreH,nbCol, nbLig);
                    SDL_RenderCopy(ecran, boss, &SrcRBoss, &DestRBoss);
                    for (int i = 1; i < nbMonstre; i++) {
                        SDL_RenderCopy(ecran, smoke, &SrcRSmo[i], &DestRSmo[i]);
                    }
                    SDL_RenderCopy(ecran, sprites, &SrcR_perso, &DestR_perso);
                }
                else if (ecr==2) {
                    for (int i = 0; i < nbLig2; i++) {
                        for (int j = 0; j < nbCol2; j++) {
                            SDL_RenderCopy(ecran, fond, &SrcR_sprite2[i][j], &DestR_sprite2[i][j]);
                        }
                    }
                    spritesEnnemis(ennemis, nbMonstre, SrcRSmo, DestRSmo, smokeW, smokeH, fenetreW, fenetreH,nbCol, nbLig);
                    SDL_RenderCopy(ecran, boss, &SrcRBoss, &DestRBoss);
                    for (int i = 1; i < nbMonstre; i++) {
                        SDL_RenderCopy(ecran, smoke, &SrcRSmo[i], &DestRSmo[i]);
                    }
                    SDL_RenderCopy(ecran, sprites, &SrcR_perso, &DestR_perso);
                }
                else if (ecr==3){
                    SDL_RenderCopy(ecran, fondwin, &SrcR_fondwin, &DestR_fondwin);
                }
                else if(ecr==4){
                    SDL_RenderCopy(ecran, fondgo, &SrcR_fondgo, &DestR_fondgo);
                }
            }
            else {//affichage encombat
                SDL_RenderCopy(ecran, fond2, &SrcR_fond2, &DestR_fond2);
                SDL_RenderCopy(ecran, monMons, &SrcR_monMons1, &DestR_monMons1);
                if (ennemis->e->positionX==monMonstre->positionX && ennemis->e->positionY==monMonstre->positionY) {
                    SDL_RenderCopy(ecran, boss, &SrcRBosscb, &DestRBosscb);
                } else {
                    SDL_RenderCopy(ecran, smokecb, &SrcRSmocb, &DestRSmocb);
                }
                SDL_RenderCopy(ecran, atta1, &SrcR_touche1, &DestR_touche1);
                SDL_RenderCopy(ecran, atta2, &SrcR_touche2, &DestR_touche2);
            }
            if (encombat) {
                encombat=combat(monMonstre, ennemis,action);
                if (!(monMonstre->pv>0)) {
                    ecr=4;
                    encombat=false;
                } else {
                    sprintf(msg, "PV: %d Attaque: %d Defense: %d", monMonstre->pv,
                            monMonstre->attaque + monMonstre->lvl, monMonstre->def + monMonstre->lvl / 2);
                    texte = charger_texte(msg, ecran, font, color);
                    int objetW2, objetH2;
                    SDL_QueryTexture(texte, &key, NULL, &objetW2, &objetH2);
                    text_pos.w = objetW2;
                    text_pos.h = objetH2;
                    SDL_RenderCopy(ecran, texte, NULL, &text_pos);

                    texte = charger_texte(msg2, ecran, font, color);
                    SDL_QueryTexture(texte, &key, NULL, &objetW2, &objetH2);
                    text_pos2.w = objetW2; // Largeur du texte en pixels (à récupérer)
                    text_pos2.h = objetH2;
                    SDL_RenderCopy(ecran, texte, NULL, &text_pos2);

                    int ecrnow = ecr;
                    ennemis = cleanEnnemi(monMonstre, ennemis, &nbMonstre, &ecr, &DestR_perso);
                    if (ecr != ecrnow) {
                        ennemis = creationMonstre(5, tab2, nbLig2, nbCol2, ecr);
                        nbMonstre = 5;
                        monMonstre->positionX = 0;
                        DestRBoss.x = fenetreW / nbCol * ennemis->e->positionX;
                        DestRBoss.y = fenetreH / nbLig * ennemis->e->positionY+10;
                    }
                    action = 0;
                }
            }

            while (SDL_PollEvent(&evenements)) {
                if (ecr == 1 || ecr == 2) {
                    if (encombat) {
                        int x, y;
                        switch (evenements.type) {
                            case SDL_MOUSEBUTTONDOWN:
                                switch (evenements.button.button) {
                                    case SDL_BUTTON_LEFT:
                                        SDL_GetMouseState(&x, &y);
                                        if (x >= 7 * fenetreW / 12 && x <= 7 * fenetreW / 12 + fenetreW / 6 &&
                                            y >= 4 * fenetreH / 6 && y <= 4 * fenetreH / 6 + fenetreH / 15) {
                                            action = 1;
                                        } else if (x >= 7 * fenetreW / 12 && x <= 7 * fenetreW / 12 + fenetreW / 6 &&
                                                   y >= 9 * fenetreH / 12 && y <= 9 * fenetreH / 12 + fenetreH / 15) {
                                            action = 2;
                                        }
                                        break;
                                    case SDL_BUTTON_RIGHT:
                                        encombat = false;
                                        (SrcR_perso).x = 0;
                                        (SrcR_perso).y = objetH / 2;
                                        if ((DestR_perso).x + fenetreW / nbCol < fenetreW &&
                                            (tab[(DestR_perso).y / (fenetreH / nbLig)][
                                                     (DestR_perso).x / (fenetreW / nbCol) + 1] == '0' ||
                                             tab[(DestR_perso).y / (fenetreH / nbLig)][
                                                     (DestR_perso).x / (fenetreW / nbCol) + 1] == '4')) {
                                            (DestR_perso).x = ((DestR_perso).x + fenetreW / nbCol);
                                            monMonstre->positionX++;
                                        }
                                        break;
                                    default:
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
                                if (ecr == 1)
                                    deplacement(monMonstre, &evenements, &DestR_perso, &SrcR_perso, tab, fenetreW,
                                                fenetreH, nbCol, nbLig, objetH, objetW);
                                else
                                    deplacement(monMonstre, &evenements, &DestR_perso, &SrcR_perso, tab2, fenetreW,
                                                fenetreH, nbCol, nbLig, objetH, objetW);
                                if ((evenements.key.keysym.sym == SDLK_q) ||
                                    (evenements.key.keysym.sym == SDLK_ESCAPE))
                                    terminer = true;
                                else if (evenements.key.keysym.sym == SDLK_s){
                                    save(ecr,monMonstre,ennemis);
                                    terminer=true;
                                }
                                else if (evenements.key.keysym.sym == SDLK_l){
                                    ennemis=load(&ecr,monMonstre,&nbMonstre);
                                    spritesEnnemis(ennemis,nbMonstre,SrcRSmo,DestRSmo,smokeW,smokeH,fenetreW,fenetreH,nbCol,nbLig);
                                    DestRBoss.x=nbCol/ecr;
                                    DestR_perso.x = (fenetreW / nbCol)*monMonstre->positionX;
                                    DestR_perso.y = (fenetreH / nbLig)*monMonstre->positionY;
                                    DestR_perso.w = fenetreW / nbCol; // Largeur du sprite
                                    DestR_perso.h = fenetreH / nbLig ;
                                }
                        }
                    }
                }
                else if (ecr==3||ecr==4){
                    switch (evenements.type) {
                        case SDL_KEYUP:
                            if ((evenements.key.keysym.sym == SDLK_q) ||
                                (evenements.key.keysym.sym == SDLK_ESCAPE))
                                terminer = true;
                    }
                }
                else if (ecr==0){
                    switch (evenements.type) {
                        case SDL_KEYUP:
                            if ((evenements.key.keysym.sym == SDLK_q) ||
                                (evenements.key.keysym.sym == SDLK_ESCAPE))
                                terminer = true;
                            else if (evenements.key.keysym.sym == SDLK_l){
                                ennemis=load(&ecr,monMonstre,&nbMonstre);
                                spritesEnnemis(ennemis,nbMonstre,SrcRSmo,DestRSmo,smokeW,smokeH,fenetreW,fenetreH,nbCol,nbLig);
                                DestRBoss.x=(fenetreW / nbCol)*((nbCol-1)/ecr);
                                printf("%d\n",ennemis->e->positionX);
                                DestR_perso.x = (fenetreW / nbCol)*monMonstre->positionX;
                                DestR_perso.y = (fenetreH / nbLig)*monMonstre->positionY;
                                DestR_perso.w = fenetreW / nbCol; // Largeur du sprite
                                DestR_perso.h = fenetreH / nbLig ;
                            }
                            else if (evenements.key.keysym.sym == SDLK_d){
                                ecr=1;
                            }
                    }
                }
            }

            SDL_RenderPresent(ecran);
        }

    // Fermer la police et quitter SDL_ttf
    TTF_CloseFont( font );
    TTF_Quit();
// Libérer de la mémoire
        SDL_DestroyTexture(fond);
        SDL_DestroyRenderer(ecran);
// Quitter SDL
        SDL_DestroyWindow(fenetre);
        SDL_Quit();

        return 0;

    }