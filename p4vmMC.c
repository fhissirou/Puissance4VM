/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Permet de jouer contre un joueur MC
 * On lance programme avec 
 * make
 * ./play_mc
 * Exemples de coups : 
 * j j en 0
 * j j en 6
*/

#include "p4vm.h"


int main(int ac, char * av[]){
  Grille mygrille = {Vide};
  char * line;
  Coup c;
  int nplayout;
  mygrille.kikijoue = J;

  if (ac != 2){
    fprintf(stderr, "usage: %s nombre-de-playouts\n", av[0]);
    return 1;
  }
  nplayout = strtol(av[1], NULL, 0);

  for(;;){
    printf("%s", strgrille(&mygrille));

    /* faire jouer l'humain */
    printf("entrer un coup ");
    line = xgetline(stdin);


  re:
    c = lirecoup(&mygrille,line+1);
    if (c.ou == Rate){
      printf("mauvais coup, recommencer\n");
      goto re;
    }

    printf("coup lu %s\n", strcoup(&c));
    jouer(&mygrille, &c);

    if (cfini(&mygrille) != PasFini)
      break;

    /* explorer au hasard */
    c = MC(&mygrille, nplayout);
    printf("la machine joue %s\n", strcoup(&c));
    jouer(&mygrille, &c);

    if (cfini(&mygrille) != PasFini)
      break;
  }

  strcfini(cfini(&mygrille));

  return 0;
}