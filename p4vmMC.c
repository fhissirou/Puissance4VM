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

/*
 Test : combien de playouts par secondes ?
*/
int main(int ac, char * av[]){
  Grille mygrille = {Vide} ;;
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