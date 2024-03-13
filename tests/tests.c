#include<stdio.h>
#include<stdlib.h>
#include <tps.h>

#include"typeArbre.h"
#include"ParseOption.h"
#include"fichierBinaire.h"
#include"utilitaires.h"
#include"MST.h"


void testsErreur(){
    options_t ops = optionsInit();
    ops.ifileName = "thisisnotafile";
    if(parseCSV(ops) !=1 ) exit(1);

    if(loadFile("thisisnotafile", NULL) != NULL) exit(1);
    int size;
    if(loadFile("tests/_empty__file__", &size) != NULL) exit(1);

    printf("TEST_ERREUR fichierBinaire.c OK\n");
}

void tests_fichierBinaire(){
    options_t ops = optionsInit();
    char name[] = "tests/arbre2test";
    ops.ifileName = name;
    parseCSV(ops);
    int size = 0;
    arbreP_t *tabOfArbre = loadFile(ops.ifileName, &size);

    //test du parse
    if(size != 5) exit(1);
    if(tabOfArbre[1].coordonne.x != 48.86453528415868-48.85995584849931 || tabOfArbre[3].coordonne.y != 0.6579097313*(2.306804208770215-2.3396034875320955)) exit(1);
    if(tabOfArbre[0].hauteur != 10) exit(1);

    loadFree(tabOfArbre);

    //test isBin
    if(isBin("tests/arbre2test") != 0) exit(1);
    if(isBin("tests/arbre2.bin") != 1) exit(1);

    printf("TEST fichierBinaire.c OK\n");
}

void testparseOption(){
    options_t ops = optionsInit();
    if(ops.ifileName != NULL || ops.iflag != 0) exit(1);
    
    printf("TEST ParseOption.c OK\n");
}

void testDistance(){
    coordonnee_t s1={.x=10,.y=5};
    coordonnee_t s2={.x=2,.y=5};
    int d=distance(s1,s2);
    if (d!=8){
         exit(1);
    }
    printf("TEST distance OK\n");
}

void tests_MST(){
    FILE *tmp = fopen("_temp_stdout__", "w+");
    FILE *save = stdout;
    stdout = tmp;


    options_t ops = optionsInit();
    char name[] = "tests/arbre2test";
    ops.ifileName = name;
    parseCSV(ops);
    int size = 0;
    arbreP_t *tabOfArbre = loadFile(ops.ifileName, &size);
    list_t *listArret;

    listArret = MST(tabOfArbre, size, ops);
    if(list_size(listArret) != 4) exit(1);
    if( ((arrete_t *)list_get(listArret,1))->s1 != 3) exit(1);
    if( ((arrete_t *)list_get(listArret,3))->s2 != 1) exit(1);
    MSTFree(listArret);

    ops.hflag = 1, ops.hight = 11;
    listArret = MST(tabOfArbre, size, ops);
    if(list_size(listArret) != 1) exit(2);
    if(    (((arrete_t*)list_get(listArret,0))->s1 != 3 || ((arrete_t*)list_get(listArret,0))->s2 != 4)
        && (((arrete_t*)list_get(listArret,0))->s1 != 4 || ((arrete_t*)list_get(listArret,0))->s2 != 3)){
            exit(1);
        }
    MSTFree(listArret);
    ops.hflag = 0; 

    ops.lflag = 1, ops.Dmax = (180/PI)*3/R_TERRE;
    listArret = MST(tabOfArbre, size, ops);
    printf("%d\n",list_size(listArret));
    if(list_size(listArret) != 2) exit(3);
    if(    (((arrete_t*)list_get(listArret,0))->s1 != 1 || ((arrete_t*)list_get(listArret,0))->s2 != 4)
        && (((arrete_t*)list_get(listArret,0))->s1 != 4 || ((arrete_t*)list_get(listArret,0))->s2 != 1)
        && (((arrete_t*)list_get(listArret,1))->s1 != 1 || ((arrete_t*)list_get(listArret,1))->s2 != 4)
        && (((arrete_t*)list_get(listArret,1))->s1 != 4 || ((arrete_t*)list_get(listArret,1))->s2 != 1)){
            exit(3);
        }
    MSTFree(listArret);

    stdout = save;
    fclose(tmp);
    remove("_temp_stdout__");
    loadFree(tabOfArbre);   

    printf("TEST MST.c OK\n");
}


/*--------------------------------main---------------------------------------*/

int main(){
    testsErreur();
    tests_fichierBinaire();
    testparseOption();
    testDistance();
    tests_MST();
    return 0;
}

