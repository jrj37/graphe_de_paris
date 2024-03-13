#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <signal.h>
#include"fichierBinaire.h"
#include"../headers/typeArbre.h"
#include"../headers/ParseOption.h"
#include"MST.h"
#include"ui.h"

/** @mainpage Document d'information
 *   
 * @section Résumé_général Résumé général
 * 
 * Utilisation : L'execution de 'graphe' doit se faire avec l'option -i suivi du chemin vers un fichier au format CSV ou binaire résultant du parsage. En cas de fichier autre le comportement est indéfini.
 * En cas de fichier CSV en entrée, un fichier binaire résultant du parsage est créé, son nom peut être choisi avec l'option -o <fichier>. L'execution sans option -i ou -u ne fait rien.
 * Par défaut la totalité des arrêtes sont considérées, le graphe est complet. L'option -h <hauteur> permet de ne considèrer que les arbres plus grands que <hauteur>. L'option -l <distance> permet de considérer que les arrêtes entre les arbres écartés de plus de <distance>.
 * 
 * L'option -w perrmet de désactiver l'affichage graphique.
 * 
 * En cas d'erreur sur l'ouverture ou le contenu du fichier passé en entrée le programme quitte avec le code d'erreur 1.
 */

static void sigint()
{
    ssize_t unused __attribute__((unused));
    unused = write(STDERR_FILENO, "\nArrêt du programme !\n", 24);
    exit(1);
}

int main(int argc, char **argv){
    if (signal(SIGINT, sigint) == SIG_ERR){    //Signal sigint pour quitter le programme.
        perror("signal SIGINT");
        exit(1);
    }
    
    options_t options = optionsInit();
    parseOption(argc, argv, &options);

    if(options.iflag == 0) return 0;


    if(isBin(options.ifileName) == 0){
        if(parseCSV(options)!=0) return 1;
    }


    int size = 0;
    arbreP_t *tabOfArbre = loadFile(options.ofilename, &size);
    if(tabOfArbre == NULL) exit(1);

    
    

    list_t *listArret = MST(tabOfArbre, size, options);
     
    

    if(options.wflag) render(listArret, tabOfArbre, size);

    loadFree(tabOfArbre);
    MSTFree(listArret);

    return 0;
}