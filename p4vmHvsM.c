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
/*
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
*/

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

