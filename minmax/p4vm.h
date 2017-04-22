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

  Max = 0 , Min = 1,
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


struct Return {  //renvoyée par minimax
	int val ; //la valeur
	Coup coup ;  // le coup pour l'obtenir
};

typedef struct Grille Grille;
typedef struct Coup Coup ; 
typedef struct Return Return ; 

Grille mygrille ;

Coup nocoup = { -1 } ; 



/****** PROTOTYPES DES FONCTIONS ***********/


char * strgrille(Grille * g) ; 
static inline int lc2p(int l, int c) ; 


void liregrille(Grille * g, FILE * fd) ; 
static inline int mot2val(char * mot) ;
static inline char * xgetline(FILE * oulire) ; 


char * strcoup(Coup * coup) ; 
Coup lirecoup(char * line) ; 
static inline int autre(int ki) ; 
void jouer(Grille * g, Coup * c) ; 
void dejouer(Grille * g, Coup * c) ;


int mkcoup(Grille * g, Coup c[], int kikijoue) ; 

int mkcoup2(Grille * g, Coup c[]) ; 
void strcfini(int val) ; 
int cfini(Grille * g) ; 
