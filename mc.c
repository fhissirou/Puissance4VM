/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Fonctions pour la recherche de coups avec MC
 * Utilisé par p4vmMC.c et p4vm_MC_vs_AB.c
*/

#include "p4vm.h"

int playout(Grille * g){
  int t;
  Coup liste[MaxCoup];
  int nel;
  Grille copie;

  copie = * g;
  while((t = cfini(&copie)) == PasFini){
    nel = mkcoup(&copie, liste);
    jouer(&copie, &liste[rand() % nel]);
  }
  return t;
}



Coup MC(Grille * g, int nplayout){
  Coup liste[MaxCoup];
  int nel;
  int score[MaxCoup];
  int i, imax;

  nel = mkcoup(g, liste);

  for(i = 0; i < nel; i++)
    score[i] = 0;

  // jouer des playouts et noter le résultat pour le premier coup
  for(i = 0; i < nplayout; i++){
    jouer(g, &liste[i % nel]);
    score[i % nel] += playout(g);
    dejouer(g, &liste[i % nel]);
  }

  // choisir celui avec le meilleur score
  for(imax = 0, i = 1; i < nel; i++)
    if ((g->kikijoue == R && score[i] > score[imax]) ||
    (g->kikijoue == J && score[i] < score[imax]))
      imax = i;

  return liste[imax];
}
