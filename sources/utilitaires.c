#include <stdio.h>
#include"typeArbre.h"
#include "math.h"
#include "utilitaires.h"

double distance(coordonnee_t s1,coordonnee_t s2){
    double d;
    d=sqrt(pow((s1.x)-(s2.x),2) + pow((s1.y)-(s2.y),2));
    return d;
}

//liste
typedef struct list_t{
    void ** elements;
    int allocated;
    int size;
    } list_t;

list_t* list_create(){
   
    list_t* l= malloc(sizeof(list_t));
    if (l==NULL){
        return NULL;
        }
    l->allocated =10000;
    l->size=0;  
    void ** machin= malloc(l->allocated*sizeof(void *));
   if(machin== NULL){
    free(l);
    return NULL;
   }
   l->elements=machin;
   return l;
}

int list_append(list_t* l,void * i){
    void ** elements1;
    
    if (l->size==l->allocated){
     elements1= realloc (l->elements, sizeof(void*)* l->allocated*2);
     if (!elements1){
        return 0;
     }
     l-> allocated *=2;
     l->elements =elements1;
     l->elements[l->size] = i;
     l->size =l->size+1;
     return 1;

    }
    else {
        l->elements[l->size] = i;
        l->size =l->size+1;
   
        return 1;

    }
}

int list_size(list_t *l){
    return l->size;

}
void list_free(list_t *l){
    free(l->elements);
    free(l);
    
}



void *list_get(list_t *l,int i){
    return l->elements[i];
}