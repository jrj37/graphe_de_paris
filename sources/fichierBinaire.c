#include"../headers/fichierBinaire.h"

#define BUFFER_SIZE 1000
#define CODEBIN "!c'est le code!"
#define SIZE_CODEBIN 16

//On utilise la projection cylindrique équidistante centrée arbitrairement sur Paris. Des erreurs dues à cette approximation qui apparaissent en cas de coordonnées très éloignées de Paris.
#define LAT 48.85995584849931
#define LON 2.3396034875320955
#define COS_LAT 0.6579097313 


///Remplace les quatres derniers caractères de 'name' par ".bin". 
void renamebin(char *name){
    if(strlen(name)<5){
        name[0] = 'f';
        name[1] = 0;
        return;
    }
    name[strlen(name)-1] = 'n';
    name[strlen(name)-2] = 'i';
    name[strlen(name)-3] = 'b';
    name[strlen(name)-4] = '.';
    return;
}

int parseCSV(options_t ops){
    FILE *in = fopen(ops.ifileName, "r");
    if(in == NULL) return 1;

    if(ops.oflag == 0) renamebin(ops.ifileName); 
    FILE *out = fopen(ops.ofilename, "w+b");
    if(out == NULL){
        fclose(in);
        return 2;
    }

    char code[SIZE_CODEBIN] = CODEBIN; //Pour identifier le fichier binaire.
    if(fwrite(code, SIZE_CODEBIN, 1, out) == 0) return 3;
    
    int size = 0; 
    if(fwrite(&size, sizeof(size), 1, out) == 0) return 3; //On écrira ici le nombre d'arbre parsé.


    char txtCourant[BUFFER_SIZE]; 
    int curseur = 0; //Curseur correspondant au prochain caractère de txtCourant.
    char charCourant;
    int countSeparateur = 0;

    arbreP_t arbreCourant;

    //Pour enlever la ligne d'entête.
    if(fgetc(in)=='I'){
        if(fgets(txtCourant, BUFFER_SIZE, in) == 0) exit(1);
    }  
    else fseek(in,0,SEEK_SET);

    while(!feof(in)){
        charCourant =fgetc(in); 

        switch(charCourant){
            case ';':
                if(countSeparateur == 13){   //13e ';' correspond à la fin de la colonne 'hauteur'.
                    txtCourant[curseur] = 0;
                    arbreCourant.hauteur = atoi(txtCourant);                    
                }
                txtCourant[0] = 0; //on réinitialise le 1er char à 0 pour fixer le champ à 0 en cas de colonne vide.
                curseur = 0;
                countSeparateur ++; //on compte les ';' afin de pouvoir identifier la colonne.
                break;

            case '\n':
            case EOF:
                txtCourant[strcspn(txtCourant, ",")]= 0;
                txtCourant[curseur] = 0;
                arbreCourant.coordonne.x = atof(txtCourant);
                arbreCourant.coordonne.y = atof(strchr(txtCourant, 0)+1);
                
                //Réinitialisation.
                txtCourant[0] = 0;
                curseur = 0;
                countSeparateur = 0;

                if(arbreCourant.coordonne.x != 0){ //Test pour écarter les lignes vides.
                    arbreCourant.coordonne.x = arbreCourant.coordonne.x-LAT;
                    arbreCourant.coordonne.y = (arbreCourant.coordonne.y-LON)*COS_LAT;
                    if(fwrite(&arbreCourant, sizeof(arbreCourant), 1, out) ==0) return 3;
                    size ++;
                }
                break;

            default :
                txtCourant[curseur] = charCourant;  //On écrit dans txtCourant les caractères contenus entre deux ';'.
                curseur ++;
        }
    }

    fseek(out, SIZE_CODEBIN, SEEK_SET);
    if(fwrite(&size, sizeof(size), 1, out) == 0) return 3;
    fclose(out);
    fclose(in);
    return 0;
}

int isBin(char *nameOfFile){
    FILE *f=fopen(nameOfFile, "rb");
    if(f == NULL) exit(1);

    char buffer[SIZE_CODEBIN];
    if(fread(buffer, SIZE_CODEBIN, 1, f) != 1) exit(1); //Problème sur le contenu du fichier.
    fclose(f);

    if(strncmp(buffer, CODEBIN, SIZE_CODEBIN) == 0) return 1; //return 1 si le fichier à la bonne forme binaire.
    return 0; //return 0 sinon, le fichier doit avoir la forme attendue de CSV pour le bon fonctionnement de la suite du programme.
}

void *loadFile(char *nameOfFile, int *size){
    FILE *file = fopen(nameOfFile, "rb");
    if( file == NULL) return NULL;

    fseek(file, SIZE_CODEBIN, SEEK_CUR); //On ignore le début du fichier qui corespond au code d'identification.

    if(fread(size, sizeof(int), 1, file) == 0){ //On recupère d'abord le nombre d'arbres du fichier.
        fclose(file);
        return NULL;
    }

    void * p = malloc(*size * sizeof(arbreP_t));

    if(fread(p, sizeof(arbreP_t), *size, file) == 0){
        free(p);
        fclose(file);
        return NULL;
    }
    
    fclose(file);
    
    return p;
}


void loadFree(void *p){
    free(p);
}