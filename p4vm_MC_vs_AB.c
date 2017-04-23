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

Grille mygrille={Vide};

/* match --  MC premier contre alpha-beta ; renvoie le score de MC */
int match(int nplay){
  Grille save = mygrille;
  Coup c;
  int t;
  int ki;

  for(ki = 1; (t = cfini(&mygrille)) == PasFini; ki ^= 1){
    if (ki == 0)
      c = ab_alphabeta(&mygrille);
    else
      c = MC(&mygrille, nplay);
    jouer(&mygrille, &c);
  }

  mygrille = save;
  return t;
}

enum {
  Nmatch = 200,
};


int main(int ac, char * av[]){
  int nplayouts;
  int i;
  int score;

  srand(getpid());

  //fichierdamier(&mygrille, "damier.vide");
  if (ac != 2){
    fprintf(stderr, "usage: %s nbre-de-playouts\n", av[0]);
    exit(1);
  }
  nplayouts = strtol(av[1], NULL, 0);
  mygrille.kikijoue = J;
  printf("%s", strgrille(&mygrille));

  for(i = score = 0; i < Nmatch; i++)
    score += match(nplayouts);

  printf("%d playouts: score %d\n", nplayouts, score);
  return 0;
}