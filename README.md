# ProjetProgramation_FERREIRA-RIVIER_JULIEN

## Usage
L'execution de 'graphe' doit se faire avec l'option -i suivi du chemin vers un fichier au format CSV ou binaire résultant du parsage. En cas de fichier autre le comportement est indéfini.
 En cas de fichier CSV en entrée, un fichier binaire résultant du parsage est créé, son nom peut être choisi avec l'option -o <fichier>. L'execution sans option -i ou -u ne fait rien.
 Par défaut la totalité des arrêtes sont considérées, le graphe est complet. L'option -h <hauteur> permet de ne considérer que les arbres plus grands que <hauteur>. L'option -l <distance> permet de considérer que les arrêtes entre les arbres écartés de plus de <distance>.
 
 L'option -w permet de désactiver l'affichage graphique.
Le code est réalisé en C.

