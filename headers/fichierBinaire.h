#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../headers/typeArbre.h"
#include"ParseOption.h"

/**
 * @defgroup Bin Bin
 * @{
*/

/**
 * @brief parse les données aux formats CSV et produit un fichier binaire dans un format exploitable par les autres fonctions.
 * Si l'option 'o' n'est pas renseignée, le nom du fichier binaire est repris du nom de fichier en input en modifiant les quatres derniers caractères par ".bin".
 * Le champ 'fileName' en option est modifié par le chemin vers le fichier binaire.
 * 
 * @param ops le champ 'fileName' doit contenir un chemin vers un fichier CSV au format de la base de donnée des arbres de Paris. 
 * 
 * @return 0 si tout se passe correctement, 1 en cas d'erreur sur l'input, 2 en cas d'erreur sur l'output, 3 sinon.
*/
int parseCSV(options_t ops);

/**
 * @brief teste si le fichier en input est au format exploitable.
 * 
 * @return 1 si le fichier est au bon format, 2 en cas d'erreur sur la lecture du fichier, 0 sinon.
*/
int isBin(char *nameOfFile);

/**
 * @brief charge les données du fichier binaire à l'adresse retournée et initialise le champ size avec le nombre d'arbre donné.
 * 
 * @param nameOfFile doit contenir le chemin vers un fichier binaire au format résultant de la fonction 'parseCSV'.
*/
void *loadFile(char *nameOfFile, int *size);

/**
 * libère la mémoire allouée pour contenir les données du fichier.
*/
void loadFree(void *p);

/**}@*/