//
// Created by juliedespre, dorapapai on 01/11/22.
//
#include "fonctions_fichiers.h"

char** allouer_tab_2D(int n, int m){
    char** tab_2D = (char**)malloc(n * sizeof(char*));
    if(tab_2D == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n ; i++){
        tab_2D[i] = (char*)malloc(m*sizeof(char));
    }

    return tab_2D;
}

char** initialiser_tab_2D(int n, int m){
    char** tab_2D=allouer_tab_2D(n,m);
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            tab_2D [i][j]='0'; // code pour la case herbe faire un truc mieux !!!
        }
    }
    return tab_2D;
}


void desallouer_tab_2D(char** tab, int n){
    for(int i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);
    tab = NULL;

}

void afficher_tab_2D(char** tab, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j<m; j++){
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
}
//compte nbre max lignes et de colonnes dans le nomFichier
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
    FILE* fichier = NULL ;
    fichier = fopen(nomFichier, "r") ;
    int c ;
    int nbLigne=0;
    int nbColonne=0;
    int maxCol=0;
    if (fichier != NULL) {
        do {
            c = fgetc(fichier);
            if ( c=='\n' || c=='\r' || c==EOF){

                if (c=='\r'){
                    c = fgetc(fichier);
                }
                if(c!=EOF){
                    nbLigne++;
                }
                if(nbColonne>maxCol){
                    maxCol=nbColonne;
                }
                nbColonne=0;
            }
            else{
                nbColonne++;
            }

        } while (c != EOF) ;
        fclose(fichier);
        *nbLig=nbLigne;
        *nbCol=maxCol;
    }

}



char** lire_fichier(const char* nomFichier){

    int nbLig =0;
    int nbCol=0;
    taille_fichier(nomFichier,&nbLig,&nbCol);
    char** tab=initialiser_tab_2D(nbLig,nbCol);

    FILE* fichier = NULL ;
    fichier = fopen(nomFichier, "r") ;
    int c ;
    int nbLigne=0;
    int nbColonne=0;
    if (fichier != NULL) {
        do {
            c = fgetc(fichier);
            if ( c=='\n' || c=='\r' || c==EOF){

                if (c=='\r'){ //car saut de ligne peut etre /r /n le fgetc permet de s'alligner avec /n
                    c = fgetc(fichier);
                }
                if(c!=EOF){//si le caract??re n'est pas EOF incr??mente le nbre de ligne
                    nbLigne++;
                }
                nbColonne=0;
            }
            else{
                //printf ("%d  %d  %c\n",nbLigne,nbColonne,c);
                tab[nbLigne][nbColonne]=c;
                nbColonne++;
            }

        } while (c != EOF) ; // deuxi??me partie du do while do : tout ce qu'il y avant jusqu'a arriver ?? la condition while
        fclose(fichier);

    }
    return tab;

}
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau) {
    char** tab2=initialiser_tab_2D(n, m);
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (tab[i][j]==ancien){
                tab2[i][j]=nouveau;
            } else {
            tab2[i][j]=tab[i][j];
            }
        }
    }
    return tab2;
}
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m) {
    // nbLig = n;
    // nbCol = m;

    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "a");//a pour ??crire dans un fichier d??j?? ??crit sinon w pour ??crire dans un fichier

    if (fichier != NULL) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j<m; j++){
                fputc(tab[i][j], fichier);
            }
            fputc('\n', fichier);
        }
        fclose(fichier);
    }
}

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer){
    SDL_CreateTextureFromSurface(renderer,SDL_LoadBMP(nomfichier));
}

SDL_Texture* charger_image_transparente(const char* nomfichier,SDL_Renderer* renderer,Uint8 r, Uint8 g, Uint8 b){
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    Uint32 key = SDL_MapRGB(surface->format,r,g,b);
    SDL_SetColorKey(surface, SDL_TRUE, key);
    SDL_CreateTextureFromSurface(renderer,surface);
}

SDL_Texture* charger_texte(const char* message, SDL_Renderer* renderer, TTF_Font *font, SDL_Color color){
    SDL_Surface* surface=TTF_RenderText_Solid(font, message,color);
    SDL_CreateTextureFromSurface(renderer,surface);
}

int deplacement(monstre m,SDL_Event *evenements,SDL_Rect *DestR_perso,SDL_Rect *SrcR_perso,char** tab,int fenetreW,int fenetreH,int nbCol,int nbLig,int objetH,int objetW){
    switch ((*evenements).key.keysym.sym) {
        case SDLK_RIGHT:
            (*SrcR_perso).x = 0;
            (*SrcR_perso).y = objetH/2;
            if ((*DestR_perso).x + fenetreW / nbCol < fenetreW &&
                    (tab[(*DestR_perso).y / (fenetreH / nbLig)][(*DestR_perso).x / (fenetreW / nbCol) + 1] == '0'||tab[(*DestR_perso).y / (fenetreH / nbLig)][(*DestR_perso).x / (fenetreW / nbCol) + 1] == '4')) {
                (*DestR_perso).x = ((*DestR_perso).x + fenetreW / nbCol);
                m->positionX++;
            }
            break;
        case SDLK_DOWN:
            (*SrcR_perso).x = 0;
            (*SrcR_perso).y = 0;
            if ((*DestR_perso).y + fenetreH / nbLig < fenetreH &&
                    (tab[(*DestR_perso).y / (fenetreH / nbLig) + 1][(*DestR_perso).x / (fenetreW / nbCol)] == '0'||tab[(*DestR_perso).y / (fenetreH / nbLig) + 1][(*DestR_perso).x / (fenetreW / nbCol)] == '4')) {
                (*DestR_perso).y = ((*DestR_perso).y + fenetreH / nbLig);
                m->positionY++;
            }
            break;
        case SDLK_LEFT:
            (*SrcR_perso).x = 0;
            (*SrcR_perso).y = objetH/4;
            if ((*DestR_perso).x - fenetreW / nbCol >= 0 &&
                    (tab[(*DestR_perso).y / (fenetreH / nbLig)][(*DestR_perso).x / (fenetreW / nbCol) - 1] == '0'||tab[(*DestR_perso).y / (fenetreH / nbLig)][(*DestR_perso).x / (fenetreW / nbCol) - 1] == '4')) {
                (*DestR_perso).x = ((*DestR_perso).x - fenetreW / nbCol);
                m->positionX--;
            }
            break;
        case SDLK_UP:
            (*SrcR_perso).x = 0;
            (*SrcR_perso).y = objetH/2+objetH/4;
            if ((*DestR_perso).y - fenetreH / nbLig >= 0 &&
                    (tab[(*DestR_perso).y / (fenetreH / nbLig) - 1][(*DestR_perso).x / (fenetreW / nbCol)] == '0' || tab[(*DestR_perso).y / (fenetreH / nbLig) - 1][(*DestR_perso).x / (fenetreW / nbCol)] == '4')){
                (*DestR_perso).y = ((*DestR_perso).y - fenetreH / nbLig);
                m->positionY--;
            }
            break;

        default:
            break;
    }
    return 0;
}


