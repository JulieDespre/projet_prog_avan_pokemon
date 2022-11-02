//
// Created by juliedespre on 01/11/22.
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
            tab_2D [i][j]=' ';
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
                if(c!=EOF){//si le caractère n'est pas EOF incrémente le nbre de ligne
                    nbLigne++;
                }
                nbColonne=0;
            }
            else{
                //printf ("%d  %d  %c\n",nbLigne,nbColonne,c);
                tab[nbLigne][nbColonne]=c;
                nbColonne++;
            }

        } while (c != EOF) ; // deuxième partie du do while do : tout ce qu'il y avant jusqu'a arriver à la condition while
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
