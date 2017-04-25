/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Jeu contre l'ordinateur qui joue de manière aléatoire
 * On lance programme avec 
 * make
 * ./play_aleatoire
 * Exemples de coups : 
 * j j en 0
 * j j en 6
*/

#include "p4vm.h"


int main(int k, char ** argv) {      
  char * line;
  Grille mygrille= {Vide} ;
  Grille Gtmp;
  Coup c;
  Coup liste[MaxCoup];
  int nel;
  int etat;

  srand(getpid());

  mygrille.kikijoue = J;

  for(;;){
    printf("%s", strgrille(&mygrille));
    re:
      /* faire jouer l'humain */
      printf("entrer un coup ");
      line = xgetline(stdin);

      c = lirecoup(&mygrille, line+1);

      if (c.ou == Rate){  
        printf("mauvais coup, recommencer\n");
        goto re;
      }

    // les coups sont bien lu et jouer
    printf("coup lu %s\n", strcoup(&c));  
    jouer(&mygrille, &c);

    if((etat = cfini(&mygrille)) != PasFini){
      strcfini(etat);
      break;
    }

    /* faire jouer le hasard */
    Gtmp = mygrille;
    nel = mkcoup(&Gtmp, liste);

    c = liste[rand() % nel];
    printf("la machine joue %s\n", strcoup(&c));
    jouer(&mygrille, &c);

    if((etat = cfini(&mygrille)) != PasFini){
        printf("val === %d\n", etat);
      strcfini(etat);
      break;
    }
  } 

  return 0;
}


