#pragma once

#include <stdio.h>
#include"typeArbre.h"
#include "math.h"
#include "stdlib.h"

/**
 * calcul la distance euclidienne entre deux arbres.
*/
double distance(coordonnee_t s1, coordonnee_t s2);


typedef struct list_t list_t; 

list_t* list_create();///< initialise une liste avec aucun élément.
int list_append(list_t* l,void *i);///< ajoute un élément à la fin de la liste l.
int list_size(list_t *l);///< retourne le nombre d'éléments de la liste l.
void *list_get(list_t *l,int i);///< retourne le (idx+1)-ieme élément. En cas de dépassement, le comportement est indéfini.
void list_free(list_t *l);///< libère la mémoire allouée pour la liste l.