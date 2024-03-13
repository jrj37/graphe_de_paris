#include <stdio.h>
#include <tps.h>
#include <typeArbre.h>
#include <MST.h>
#include <math.h>
#define wLong 1000
#define wLarg 800
#define ajusterFenetre 0.0003

double maximumX(arbreP_t *tab,int size){
    double maxX=0;
    for (int i=0;i<size;i++){
        if (tab[i].coordonne.x>maxX){
            maxX=tab[i].coordonne.x;
        }
    }
    return maxX;
}

double maximumY(arbreP_t *tab,int size){
    double maxY=0;
    for(int j=0;j<size;j++){
        if (tab[j].coordonne.y>maxY){
            maxY=tab[j].coordonne.y;
        }
    }
    return maxY;
}

double minimumX(arbreP_t *tab, int size){
    double minX=tab[0].coordonne.x;
    for (int i=0;i<size;i++){
        if (tab[i].coordonne.x<minX){
            minX=tab[i].coordonne.x;
        }
    }
    return minX;
}

double minimumY(arbreP_t *tab, int size){
    double minY=tab[0].coordonne.y;
    for (int i=0;i<size;i++){
        if (tab[i].coordonne.y<minY){
            minY=tab[i].coordonne.y;
        }
    }
    return minY;
}

void render( list_t *listeAretes,arbreP_t *tab,int size){
    double maxX,maxY,minX,minY,aLong,aLarg;
    minX=minimumX(tab, size)-ajusterFenetre;
    minY=minimumY(tab, size)-ajusterFenetre;
    maxX=maximumX(tab, size)+ajusterFenetre;
    maxY=maximumY(tab, size)+ajusterFenetre;
    aLong = (wLong)/(maxY-minY);
    aLarg = (wLarg)/(maxX-minX);
    tps_createWindow("Graphe de Paris",wLong,wLarg);
    while (tps_isRunning()){
        tps_background(255,255,255);
        tps_setColor(255,0,0);
        if(size < 1000){
            for(int i=0; i<size; i++){
                tps_fillEllipse(aLong*(tab[i].coordonne.y)-aLong*minY, (aLarg*(tab[i].coordonne.x)-aLarg*minX)+2*((wLarg/2)-(aLarg*(tab[i].coordonne.x)-aLarg*minX)), 2, 2);
            }
        }
        tps_setColor(0,0,0);
        int taille=list_size(listeAretes);
        arrete_t *arrete;
        for (int i=0;i<taille;i++){
            arrete=list_get(listeAretes,i);
            tps_drawLine(aLong*(tab[arrete->s1].coordonne.y)-aLong*minY,
                        (aLarg*(tab[arrete->s1].coordonne.x)-aLarg*minX)+2*((wLarg/2)-(aLarg*(tab[arrete->s1].coordonne.x)-aLarg*minX)),
                         aLong*(tab[arrete->s2].coordonne.y)-aLong*minY, 
                        ((aLarg*(tab[arrete->s2].coordonne.x)-aLarg*minX)+2*(wLarg/2 -(aLarg*(tab[arrete->s2].coordonne.x)-aLarg*(minX)))));
        }
        tps_render();
    }
    tps_closeWindow();
}

// On a une symétrie par rapport à l'axe des abscisses.
// On proportionne la fenêtre à la taille du graphe sur l'axe des Y et l'axe des X.
