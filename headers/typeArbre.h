#pragma once

#include<stdio.h>
#include<stdlib.h>
 
/**
 * @defgroup typeArbre Types Arbre
 * @{
 * 
*/

typedef struct coordonnee_t{
    double x;
    double y;
}coordonnee_t;


/**
 * @brief structure pour stocker les informations qui correspondent à un arbre.
*/
typedef struct arbreP_t{
    coordonnee_t coordonne;///<coordonnées de l'arbre.
    int hauteur;///<hauteur de l'arbre.
}arbreP_t;

/**}@*/