#ifndef P4VM_H
#define P4VM_H
# include <stdio.h>
# include <assert.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>


enum {
  R = 1, J = 2,			// joueurs (Rouge et Jaune) et marques
  Vide = 0,			// pas marque

  N = 7,			// taille du damier : N nombre de colonne, M nombre de rangées
  M = 6,
  Xwin = 1, Xloose = -1, Nul = 0, // résultats
  Fini = -1,

  Rate = -1,			// case invalide


  MaxCoup = 42,   // il y a 21 pions par joueur
 
  MaxStrGrille = 1024,
  MaxStrCoup = 100,
};

struct Grille
{
	int kikijoue ;
	int place[N*M] ; 
};

struct Coup {
  int ou;
  int ki;
};

typedef struct Grille Grille;
typedef struct Coup Coup ; 


static inline int lc2p(int l, int c){ return l * N + c; }

/**** TT2 ***********/

/* xgetline  --  comme getline mais ligne neuve et EOF = erreur */
static inline char * xgetline(FILE * oulire){
  char * str;
  size_t ncar;
  int t;

  str = NULL;
  t = getline(&str, &ncar, oulire);
  if (t == -1){
    if (feof(oulire))
      fprintf(stderr, "Fin de fichier inattendue\n");
    perror("xgetline");
    exit(1);
  }
  return str;
}


static inline int autre(int ki){
  if (ki == J)
    return R;
  else if (ki == R)
    return J;
  assert(0);
}


static inline int
mot2val(char * mot){
  if (mot == NULL){
    fprintf(stderr, "mot manquant\n");
    exit(1);
  }

  if (mot[0] == '.')
    return Vide;
  else if (mot[0] == 'j' || mot[0] == 'J')
    return J;
  else if (mot[0] == 'r' || mot[0] == 'R')
    return R;

  fprintf(stderr, "caractere %c pas compris\n", mot[0]);
  exit(1);
}



/****** PROTOTYPES DES FONCTIONS ***********/


char * strgrille(Grille * g) ; 
//static inline int lc2p(int l, int c) ; 


void liregrille(Grille * g, FILE * fd) ; 
//static inline int mot2val(char * mot) ;
//static inline char * xgetline(FILE * oulire) ; 


char * strcoup(Coup * coup) ; 
Coup lirecoup(Grille *mygrille, char * line) ; 
//static inline int autre(int ki) ; 
void jouer(Grille * g, Coup * c) ; 
void dejouer(Grille * g, Coup * c) ;

int test(int k, char ** argv);
int mkcoup(Grille * g, Coup c[]) ; 
void strcfini(int val) ; 
int cfini(Grille * g) ; 


int maxAB(int alpha, int beta);
int minAB(int alpha, int beta);

#endif