#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"MST.h"

/**
 * On utilise cette structure à fin de garder en mémoire des informations propres à chaque sommet du graphe
*/
typedef struct procheVoisin_t{
    double distance; //N'a de sens que lorsque que le champ 'pere' >=0, contient la distance minimale du sommet à la composante.
    int pere; /**3 type de valeur:  - -1 sommet déja traité; 
                                    - >=0 contient l'id du sommet dans la composante qui réalise la distance minimale; 
                                    - -2 permet de désigner les sommets non traités n'appartenant pas à la composante connexe en cours de calcul.
                                    n'est utile que dans le cas de l'option 'l'.
                                    */
}procheVoisin_t;

/**
 * initalise la liste des arrêtes et le buffer 'memDistance' nécessaire à l'algorithme de MST.
 */
list_t *init_tree(arbreP_t *tabOfArbre, procheVoisin_t *memDistance, int size, options_t ops){
    for(int i=0; i<size; i++){
        memDistance[i].pere = -2;

        if(ops.hflag && tabOfArbre[i].hauteur<ops.hight) memDistance[i].pere =-1;  //Dans le cas de l'option hauteur, min permet d'écarter les arbres ne vérifiant pas la condition.
    }

    return list_create();
}

/** 
 * Permet d'initialiser la prochaine composante connexe à traiter.
 * Sans l'option 'l' il n'y a qu'un seul appel à la fonction. 
 */
int initNextComp(arbreP_t *tabOfArbre, procheVoisin_t *memDistance, int size, options_t ops){
    //on recherche un sommet qui n'est pas dans une composante déja traitée pour initialiser la prochaine.
    int nouvelleRacine = 0;
    while(memDistance[nouvelleRacine].pere == -1){
        nouvelleRacine++;
        if(nouvelleRacine == size) return 0; //Dans ce cas, tous les sommets sont traités, on arrête le calcul.  
    }

    memDistance[nouvelleRacine].pere = -1;

    for(int i=nouvelleRacine+1; i<size; i++){
        if(ops.lflag == 0 && memDistance[i].pere != -1){
            memDistance[i].pere = nouvelleRacine;
            memDistance[i].distance = distance(tabOfArbre[nouvelleRacine].coordonne, tabOfArbre[i].coordonne);
        }

        if(ops.lflag == 1 && memDistance[i].pere != -1 && distance(tabOfArbre[nouvelleRacine].coordonne, tabOfArbre[i].coordonne) < ops.Dmax){
            memDistance[i].pere = nouvelleRacine;
            memDistance[i].distance = distance(tabOfArbre[nouvelleRacine].coordonne, tabOfArbre[i].coordonne);
        }
    }
            return 1;
}

int update(list_t *listOfArrete, arbreP_t *tabOfArbre, procheVoisin_t *memDistance, int size, options_t ops){
    //Affichage de l'avancement de l'algorithme.
    static int c = 0;
    c++;
    if(c%1000 == 0){
        printf("MST: %d/%d\r",c,size+1); 
        fflush(stdout);
    }

    //Recherche de la prochaine arrête et sommet à ajouter à la composante connexe.
    int nouveauSommet = 0;
    while(memDistance[nouveauSommet].pere < 0){ //Dans ce cas, il n'y a plus de sommet à traiter dans la composante connexe en cours. On initialise la prochaine composante connexe.
        nouveauSommet++;
        if(nouveauSommet == size) return initNextComp(tabOfArbre, memDistance, size, ops);
    }
    for(int i=nouveauSommet; i<size; i++){
        if(memDistance[i].pere >= 0 && memDistance[i].distance < memDistance[nouveauSommet].distance){
            nouveauSommet = i;
        }
    }

    arrete_t *nouvelleArrette = malloc(sizeof(arrete_t));
    nouvelleArrette->s1 = memDistance[nouveauSommet].pere;
    nouvelleArrette->s2 = nouveauSommet;
    list_append(listOfArrete, nouvelleArrette);
    
    memDistance[nouveauSommet].pere = -1;


    //Mise à jour des distances à la composante connexe.
    for(int i=1; i<size; i++){
        if(memDistance[i].pere >= 0 && memDistance[i].distance > distance(tabOfArbre[i].coordonne, tabOfArbre[nouveauSommet].coordonne)){
            memDistance[i].pere = nouveauSommet;
            memDistance[i].distance = distance(tabOfArbre[i].coordonne, tabOfArbre[nouveauSommet].coordonne);
        }

        //On considère au fur et à mesure que l'on ajoute des sommmets, les sommets de la composante.
        if(memDistance[i].pere == -2 && distance(tabOfArbre[i].coordonne, tabOfArbre[nouveauSommet].coordonne) < ops.Dmax){
            memDistance[i].pere = nouveauSommet;
            memDistance[i].distance = distance(tabOfArbre[i].coordonne, tabOfArbre[nouveauSommet].coordonne);
        }
    }
    
    return 1;
}

void* MST(arbreP_t *tabOfArbre, int size, options_t ops){
    clock_t start = clock();
    //Initialisation.
    procheVoisin_t memDistance[size];
    list_t *listOfArrete = init_tree(tabOfArbre, memDistance, size, ops);
    
    while(update(listOfArrete, tabOfArbre, memDistance, size, ops));
    printf("MST: %d/%d\nMST complété en %lf s\n",size+1, size+1, (double)((clock()-start))/CLOCKS_PER_SEC);
    
    return listOfArrete;   
}

void MSTFree(list_t *listArret){
    for(int i=0; i<list_size(listArret); i++) free((arrete_t *)list_get(listArret, i));
    list_free( listArret);

}