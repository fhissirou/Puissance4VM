/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation entre un joueur parfait et un joueur montecarlo
 * ./play_mc_vs_ab
*/

#include "p4vm.h"

Grille mygrille={Vide};


/* match --  MC premier contre alpha-beta ; renvoie le score de MC */
int match(int nplay){
  Grille save = mygrille;
  Coup c;
  int t;
  int ki ;

  for (ki = 0 ; cfini(&mygrille) == PasFini;  ki ^= 1 ) {
    if (ki == 1) {
      //printf("alphabeta joue\n") ;
      c = ab_alphabeta(&mygrille); 
      if (mygrille.place[c.ou] != Vide) { 
	//printf("alphabeta a perdu \n") ; 
        //printf("%s", strgrille(&mygrille));
        mygrille = save; return 1; 
       } 
    }
    else {
	//printf("mc joue\n") ; 
      	c = MC(&mygrille, nplay);
	}
  
    jouer(&mygrille, &c); 
  }
  mygrille = save;
  t = cfini(&mygrille) ; 
  if ( t == 2) return -1;  //mc a perdu
  return 0; //match nul
}



enum {
  Nmatch = 200,
};


int main(int ac, char * av[]){
  int nplayouts;
  int i;
  int score;

  srand(getpid());

  fichiergrille(&mygrille, (char*)"damiers/damier.vide");
  if (ac != 2){
    fprintf(stderr, "usage: %s nbre-de-playouts\n", av[0]);
    exit(1);
  }
  nplayouts = strtol(av[1], NULL, 0);
  //mygrille.kikijoue = J;
  printf("%s", strgrille(&mygrille));

  for(i = score = 0; i < Nmatch; i++) {
    //printf("Match numéro %d-----------\n", i) ; 
    int s = match(nplayouts);
    //printf("Score is %d\n", s) ; 
    score += s ; 
  }

  printf("%d playouts: score %d\n", nplayouts, score);
  return 0;
}
