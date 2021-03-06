/* 
 * Roxane Desrousseaux
 * Fodé Hissirou
 * 24 Avril 2017
 * Simulation de jeu puissance 4 version misère avec l'ordinateur
 * Permet d'envoyer un damier en entrée et retourne le joueur qui a la position gagnante avec minmax
 * On lance programme avec 
 * make
 * ./play_minmax < nom_damier
*/

#include "p4vm.h"



int nexplore;
Grille mygrille;

int max(){
  Coup liste[MaxCoup];
  int nel;
  int i, tmp;
  int val= Xloose;

  nexplore += 1;

  tmp = cfini(&mygrille);
  if (tmp != PasFini)
    return tmp;

  nel = mkcoup(&mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(&mygrille, &liste[i]);
    tmp = min();
    assert(tmp != PasFini);
    dejouer(&mygrille, &liste[i]);

    if(tmp > val){
      val= tmp;
    }
  }

  return val;
}

int min(){
  Coup liste[MaxCoup];
  int nel;
  int i, tmp;
  int val= Xwin;

  nexplore += 1;

  tmp = cfini(&mygrille);
  if (tmp != PasFini){
    return tmp;
  }

  nel = mkcoup(&mygrille, liste);
  for(i = 0; i < nel; i++){
    jouer(&mygrille, &liste[i]);
    tmp = max();
    assert(tmp != PasFini);
    dejouer(&mygrille, &liste[i]);

    if (tmp < val){
      val = tmp;
    }

  }

  return val;
}


int main(int ac, char * av[]){
  int val = PasFini;
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
    val = max();
  }
  strcfini(val);
  printf("Résultat de l'exploration totale : %d noeuds\n",nexplore);

  return 0;
}