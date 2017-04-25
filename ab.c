/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Fonctions pour la recherche de bons coups avec alphabeta (profondeur limitée)
 * Utilisé par p4vmHvsM.c et p4vm_MC_vs_AB.c
*/

#include "p4vm.h"

static Coup boncoup;
int nexplore;
static Grille *mygrille;
int pMax= 4;


int maxAB_profondeur(int alpha, int beta, int flag, int prof){
  Coup liste[MaxCoup];
  int nel;
  int i, t;

  nexplore += 1;
  t = cfini(mygrille);
  if (t != PasFini)
    return t;
  if(prof >= pMax)
    return t;
  
  nel = mkcoup(mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(mygrille, &liste[i]);
    prof++;
    t = minAB_profondeur(alpha, beta, 0, prof);
    dejouer(mygrille, &liste[i]);
    prof--;

    if (t > alpha){
      alpha = t;
      if(flag){
        boncoup= liste[i];
      }
    }
    if (alpha >= beta){
      break;
    }
  }

  return alpha;
}

int minAB_profondeur(int alpha, int beta, int flag, int prof){
  Coup liste[MaxCoup];
  int nel;
  int i, t;

  nexplore += 1;

  t = cfini(mygrille);
  if (t != PasFini)
    return t;
  if(prof >= pMax){
    return t;
  }
  nel = mkcoup(mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(mygrille, &liste[i]);
    prof++;
    t = maxAB_profondeur(alpha, beta, 0, prof);
    dejouer(mygrille, &liste[i]);
    prof--;

    if (t < beta){
      beta = t;
      if(flag){
        boncoup= liste[i];
      }
    }
    if (alpha >= beta){
      break;
    }
  }
  return beta;
}


Coup ab_alphabeta(Grille * g){
mygrille= g;
  if (g->kikijoue == R)
    maxAB_profondeur(Xloose, Xwin, 1,1);
  else if (g->kikijoue == J)
    minAB_profondeur(Xloose, Xwin, 1, 1);
  return boncoup;
}
