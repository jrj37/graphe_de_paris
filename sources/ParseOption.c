#include "string.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include"ParseOption.h"

void afficherOption(void){
    printf("Options:\n");
    printf("-i <fichier> : fichier d'entrée\n");
    printf("-o <fichier>: fichier de sortie \n");
    printf("-h <hauteur> : prend pas en compte les arbres plus petit que <hauteur>\n");
    printf("-l <distance>: prends pas en comptes les arrête de poids supprieur à <distance>\n");
}

options_t optionsInit(void){
    options_t ops;
    ops.ifileName = NULL;
    ops.iflag = 0;
    ops.oflag = 0;
    ops.ofilename = NULL;
    ops.hflag = 0;
    ops.lflag = 0;
    ops.wflag = 1;

    return ops;
}


int parseOption(int argc, char **argv, options_t *ops){
    if (argc==1){
        afficherOption();
        exit(0);
    }
    int c;
    opterr = 0;
  
    while ((c = getopt (argc, argv, "i:o:l:h:uw")) != -1){
        switch (c){
            case 'i':
                ops->iflag = 1;
                ops->ifileName = optarg;
                break;
            case 'o':
                ops->oflag = 1;
                ops->ofilename = optarg;
                break;
            case 'l':
                ops->lflag = 1;
                ops->Dmax = (180/PI)*atof(optarg)/R_TERRE;
                break;
            case 'h':
                ops->hflag = 1;
                ops->hight = atoi(optarg);
                break;
            case 'u': //Afficher les options. 
                afficherOption();
                exit(1);
            case 'w':
                ops->wflag = 0;
                break;
            case '?':
                if (optopt == 'i') fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt)) fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
                return 1;
            default:
                abort ();
      }
    }
  
    if(ops->oflag == 0) ops->ofilename = ops->ifileName; //Si pas d'output indiquer on récupère le chemin en input.
    return 0;
}

