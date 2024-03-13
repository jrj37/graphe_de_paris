#pragma once 
#include <stdio.h>
#include <tps.h>
#include <typeArbre.h>
#include <MST.h>

/**
 * @defgroup UI UI
 * @{
 *
*/


/**
 * @brief Lance la fenêtre qui affiche le graphe. Elle se termine lorsque la fenêtre est fermée.
 * 
 * @param res liste des arrêtes du graphes.
 * @param tab liste des arbres(sommet du graphe), contient les coordonées de chaque arbre.
 */
void render( list_t *res,arbreP_t *tab,int size);


/**@}*/