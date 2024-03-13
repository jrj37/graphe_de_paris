#pragma once

#include<stdio.h>
#include<stdlib.h>

#include"typeArbre.h"
#include"utilitaires.h"
#include"ParseOption.h"


/**
 * @defgroup MST Minimum Spanning Tree
 * 
 * @{
 * @details On utilise l'algoritme de Prim pour calculer un MST.
 * 
 * On initialise un sous graphe vide (Dans le cas de l'option -l cette initialisation se fait au début du traitement de chaque composante).
 * Le principe est d'agrandir ce sous graphe avec le sommet le plus proche du sous graphe par l'arrête la réalisant. Pour réduire le nombre 
 * de calcul, on garde en mémoire pour chaque sommet l'arrête de distance minimum au sous graphe , ainsi lors de l'ajout du sommet s au sous 
 * graphe, il suffit pour chaque sommet de comparer la distance en mémoire avec la distance au sommet s.
 * 
 * Avec l'option -l on traite toutes les composantes connexes dans un ordre indéterminé. Le calcul pour chaque composante reprend le principe
 * précédent en considérant au fur et à mesure les sommets de la composante.
*/

/**
 * structure représentant une arrête.
*/
typedef struct arrete_t{
    int s1, s2;
}arrete_t;

/**
 * @brief effectue le calcul d'un arbre recouvrant de poids minimal.
 * 
 * @param tabOfArbre liste des arbres, sommets du graphe.
 * @param size nombre de sommets du graphe.
 * @param ops contient les options données en ligne de commande.
 * 
 * @return liste des arrêtes de l'arbre recouvrant de poids minimal.
*/
void* MST(arbreP_t *tabOfArbre, int size, options_t ops);

/**
 * libère l'espace memoire allouée pour le MST. Ce qui entraine la perte du résultat.
*/
void MSTFree(list_t *listArret);


/**}@*/