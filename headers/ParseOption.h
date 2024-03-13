#pragma once
#define R_TERRE 6371.0
#define PI 3.1415926535

/**
 * @defgroup Args  Parseur d'arguments
 * @{
 *
*/

/**
 * @brief structure pour stocker les options données en ligne de commande.
 * 
 */

typedef struct options_t{
    int iflag;///<1 si un fichier est en input, 0 sinon.
    char *ifileName;///<chemin vers le fichier en input.
    int oflag;///<flag de l'option 'o'.
    char *ofilename;///<chemin vers le fichier en output.
    int hflag;///<flag de l'option 'h'.
    int hight;///<hauteur minimal des arbres considérées.
    int lflag;///<flag de l'option 'l'.
    double Dmax;///<distance maximal des arrêtes considérées.
    int wflag;///1(par défaut) pour afficher le rendu graphique, 0 sinon.
}options_t;

/**
 * @brief initialise les options par défauts.
 * 
 * @return un champ contenant les options configurées par défaut.
*/
options_t optionsInit(void);

/**
 * @brief parse les arguments données en ligne de commande. Et met à jour le champ ops avec les options données.
 * 
 * @return 0 si tout se passe correctement, 1 sinon.
*/
int parseOption(int argc, char **argv, options_t *ops);

/**@}*/