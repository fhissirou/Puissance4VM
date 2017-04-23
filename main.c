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

int strmenu(){
  int val;
  while(1){
    printf("-- puissance 4 version Misère --\n\n");
    printf("Menu\n");
    printf(" 1- H vs M(parfait)\n");
    printf(" 2- H vs M (random)\n");
    printf(" 3- Compare Minmax et Alphabeta\n");
    scanf("%d", &val);
    if(val>= 1 && val <= 3)
      return val;
  }
}

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

      // la fonction cfini() ne fonctionne par correctement mais pour l'instant ca ne dérange pas trop la génération de coups
      if (c.ou == Rate){  
        printf("mauvais coup, recommencer\n");
        goto re;
      }

    // les coups sont bien lu et jouer
    printf("coup lu %s\n", strcoup(&c));  
    jouer(&mygrille, &c);

    if((etat = cfini(&mygrille)) != 0){
      strcfini(etat);
      break;
    }

    /* faire jouer le hasard */
    Gtmp = mygrille;
    nel = mkcoup(&Gtmp, liste);

    // la liste des coups trouvés a été affichée : posiions sur la grille entre 0 et 41

    c = liste[rand() % nel];

    // ici on peut accéder à la valeur avec cout << c.ou << endl ; 
 
    printf("la machine joue %s\n", strcoup(&c));
    jouer(&mygrille, &c);

    if((etat = cfini(&mygrille)) != 0){
        printf("val === %d\n", etat);
      strcfini(etat);
      break;
    }
  } 

  return 0;
}


