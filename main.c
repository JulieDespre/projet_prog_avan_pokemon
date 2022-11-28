//
// Created by juliedespre, dorapapai on 14/11/22.
//

#include "fonctions_fichiers.h"
#include "monstre.h"

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
    int fenetreW=1400,fenetreH=750;
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
    SDL_Texture* fond = charger_image( "pavage_perso.bmp", ecran );
    //Récupérer largeur et largeur de la texture avec SDL_QueryTexture
    int objetW;
    int objetH;
    //recupère taille objet
    SDL_QueryTexture(fond,NULL,NULL,&objetW,&objetH);
    SDL_Rect DestR_sprite[nbLig][nbCol], SrcR_sprite[nbLig][nbCol];

    for(int i=0; i<nbLig; i++){
        for(int j=0; j<nbCol; j++) {
            SrcR_sprite[i][j].x = objetW / 9 * (((int)tab[i][j]-48)%9); // car char en int codé en ascii 0 = 48
            SrcR_sprite[i][j].y = objetH / 5 * (((int)tab[i][j]-48)/5);
            SrcR_sprite[i][j].w = objetW / 9; // Largeur de l’objet en pixels de la texture
            SrcR_sprite[i][j].h = objetH / 5; // Hauteur de l’objet en pixels de la texture
            DestR_sprite[i][j].x = fenetreW / nbCol * j;
            DestR_sprite[i][j].y = fenetreH / nbLig * i;
            DestR_sprite[i][j].w = fenetreW / nbCol; // Largeur du sprite
            DestR_sprite[i][j].h = fenetreH / nbLig; // Hauteur du sprite
        }
    }

    SDL_Texture* fond2 = charger_image( "combat_ombre.bmp", ecran );
    int objet2W;
    int objet2H;
    //recupère taille objet
    SDL_QueryTexture(fond,NULL,NULL,&objet2W,&objet2H);
    SDL_Rect DestR_fond2, SrcR_fond2;

    SrcR_fond2.x=0;
    SrcR_fond2.y=0;
    SrcR_fond2.w=objet2W*10;
    SrcR_fond2.h=objet2H*12;
    DestR_fond2.x=0;
    DestR_fond2.y=0;
    DestR_fond2.w=fenetreW;
    DestR_fond2.h=fenetreH;

// Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    SDL_Texture* sprites = charger_image_transparente("perso.bmp", ecran,r,g,b);
//Récupérer largeur et hauteur de la texture avec SDL_QueryTexture
    SDL_Surface* surface = SDL_LoadBMP("perso.bmp");
    Uint32 key = SDL_MapRGB(surface->format,r,g,b);
    SDL_QueryTexture(sprites,&key,NULL,&objetW,&objetH);
    SDL_Rect DestR_chat, SrcR_chat;

    SrcR_chat.x = 0;
    SrcR_chat.y = 0;
    SrcR_chat.w = objetW/3; // Largeur de l’objet en pixels de la texture, changer nom
    SrcR_chat.h = objetH/4; // Hauteur de l’objet en pixels de la texture, changer nom
    DestR_chat.x = 0;
    DestR_chat.y = 0;
    DestR_chat.w = objetW/nbCol*2; // Largeur du sprite
    DestR_chat.h = objetH/nbLig/1.5; // Hauteur du sprite

// Charger l’image avec la transparence
    r = 255, g = 255, b = 255;
    SDL_Texture* citrouille = charger_image_transparente("citrouilles.bmp", ecran,r,g,b);
//récupérer objet (citrouille)
    int citrouilleW;
    int citrouilleH;
    SDL_Surface* surfaceCit = SDL_LoadBMP("citrouilles.bmp");
    Uint32 keyCit = SDL_MapRGB(surfaceCit->format,r,g,b);
    SDL_QueryTexture(citrouille,&keyCit,NULL,&citrouilleW,&citrouilleH);
    SDL_Rect SrcRCit, DestRCit;
    SrcRCit.x = 0;
    SrcRCit.y = 0;
    SrcRCit.w = citrouilleW/12; // Largeur de l’objet en pixels de la texture
    SrcRCit.h = citrouilleH/4; // Hauteur de l’objet en pixels de la texture
    DestRCit.x = fenetreW/nbCol*2;
    DestRCit.y = fenetreH/nbLig*3;
    DestRCit.w = citrouilleW/nbCol;//largeur de la citrouille
    DestRCit.h = citrouilleH/nbLig*1.5;//hauteur de la citrouille


    //Variable du jeu
    int etat=0;
    monstre monMonstre = creerMonstre(150,2,5);
    monstre ennemi1 = creerEnnemi(20,1,6, 600, 350);
    monstre ennemi2 = creerMonstre(20,2,7);
    monstre ennemi3 = creerMonstre(20,3,8);
    monstre ennemi4 = creerMonstre(20,1,6);
    monstre ennemi5 = creerMonstre(20,2,7);
    listeEnnemi ennemis= creerListeEnnemi(ennemi1);
    ajouterEnnemi(ennemis,ennemi2);
    ajouterEnnemi(ennemis,ennemi3);
    ajouterEnnemi(ennemis,ennemi4);
    ajouterEnnemi(ennemis,ennemi5);
    // Boucle principale
    while(!terminer) {

        if ((DestR_chat).x / (fenetreW / nbCol)==2 && (DestR_chat).y / (fenetreH / nbLig)==3) etat+=1;
        SDL_RenderClear(ecran);

        for(int i=0; i<nbLig; i++) {
            for (int j = 0; j < nbCol; j++) {
                if (etat==0 || etat==2) SDL_RenderCopy(ecran, fond, &SrcR_sprite[i][j], &DestR_sprite[i][j]);
                else SDL_RenderCopy(ecran, fond2, &SrcR_fond2, &DestR_fond2);
            }
        }
        if (etat==1){
            int resultat=combat(monMonstre,ennemis->e); //liste entière au lieu de ennemis

            if (resultat==0) {
                printf("Vous êtes mort !\n");
                terminer=true;
            }
            else {
                printf("Il te reste %d pv.%p\n",monMonstre->pv,ennemis); //coredumped si amy gagne
                if (ennemis->next==NULL) printf("Vous avez gagnez!");
            }
            ennemis=ennemis->next;
        }
        SDL_RenderCopy(ecran, citrouille, &SrcRCit, &DestRCit);
        SDL_RenderCopy(ecran, sprites, &SrcR_chat, &DestR_chat);
        while (SDL_PollEvent(&evenements)) {

            switch (evenements.type) {
                case SDL_QUIT:
                    terminer = true;
                    break;
                case SDL_KEYUP:
                //case SDL_KEYDOWN:
                    etat=deplacement (&evenements,&DestR_chat,&SrcR_chat,tab,fenetreW,fenetreH,nbCol,nbLig,objetH,objetW);
                    if (evenements.key.keysym.sym==SDLK_q) terminer=true;
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

