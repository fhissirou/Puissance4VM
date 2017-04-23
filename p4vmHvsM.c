/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Permet de jouer contre un joueur parfait
 * On lance programme avec 
 * make
 * ./playHvsM
 * Exemples de coups : 
 * j j en 0
 * j j en 6
*/

#include "p4vm.h"


int main(int k, char ** argv) {      
  char * line;
  Grille grille= {Vide} ;
  Coup c;
  int etat;

  grille.kikijoue = J;

  for(;;){
    printf("%s", strgrille(&grille));
    re:
      /* faire jouer l'humain */
      printf("entrer un coup ");
      line = xgetline(stdin);

  
      c = lirecoup(&grille, line+1);

      // la fonction cfini() ne fonctionne par correctement mais pour l'instant ca ne dérange pas trop la génération de coups
      if (c.ou == Rate){  
        printf("mauvais coup, recommencer\n");
        goto re;
      }

    // les coups sont bien lu et jouer
    printf("coup lu %s\n", strcoup(&c));  
    jouer(&grille, &c);
    printf("%s", strgrille(&grille));

    if((etat = cfini(&grille)) != PasFini){
      strcfini(etat);
      break;
    }

    // joueur parfait
    c= ab_alphabeta(&grille);
    printf("la machine joue %s\n", strcoup(&c));
    jouer(&grille, &c);

    if((etat = cfini(&grille)) != PasFini){
        printf("val === %d\n", etat);
      strcfini(etat);
      break;
    }
  } 

  return 0;
}

