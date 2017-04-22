/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 26 Mars 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * On lance programme avec 
 * make
 * ./play
 * Exemples de coups : 
 * j j en 0
 * j j en 6
*/

#include "p4vm.h"

int nexplore;
Grille mygrille;

int maxAB(int alpha, int beta){
  Coup liste[MaxCoup];
  int nel;
  int i, t;

  nexplore += 1;

  t = cfini(&mygrille);
  if (t != 0)
    return t;

  nel = mkcoup(&mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(&mygrille, &liste[i]);
    t = minAB(alpha, beta);
    assert(t != 0);
    dejouer(&mygrille, &liste[i]);

    if (t > alpha)
      alpha = t;
    if (alpha >= beta)
      break;
  }

  return alpha;
}

int minAB(int alpha, int beta){
  Coup liste[MaxCoup];
  int nel;
  int i, t;

  nexplore += 1;

  t = cfini(&mygrille);
  if (t != 0)
    return t;

  nel = mkcoup(&mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(&mygrille, &liste[i]);
    t = maxAB(alpha, beta);
    assert(t != 0);
    dejouer(&mygrille, &liste[i]);

    if (t < beta)
      beta = t;
    if (alpha >= beta)
      break;
  }
  return beta;
}


int main(int ac, char * av[]){
  int val = Fini;
  int i;
  int nfois = 1; // une exploration par défaut

  if (ac > 1)
    nfois = strtol(av[1], NULL, 0);
  //mygrille.kikijoue = J;

  //Grille mygrille;
  liregrille(&mygrille, stdin);
  printf("%s", strgrille(&mygrille));

    //printf("%s", strgrille(&mygrille));
  for(i = 0; i < nfois; i++){
    val = maxAB(Xloose, Xwin);
  }
  printf("val = %d\n", val);
  strcfini(val);
  printf("Résultat de l'exploration totale : %d noeuds\n",nexplore);

  return 0;
}