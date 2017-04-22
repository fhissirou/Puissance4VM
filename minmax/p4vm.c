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

Return min() ; 



Return max() {
  int i, n;
  Return r, tmp ;
  Coup liste[MaxCoup];

  n = mkcoup(&mygrille, liste, mygrille.kikijoue);

  r.val = Xwin ;
  r.coup = nocoup ; 
  if (n == 0) return r ;
  for (i = 0; i < n ;  i++) {
     jouer(&mygrille, &liste[i]);
     tmp = min() ; 
     dejouer(&mygrille, &liste[i]) ;
     if (tmp.val > r.val) {
	r.val = tmp.val ;
        r.coup = liste[i] ; 
     }
   }
  return r;
}


Return min() {
  int i, n;
  Return r, tmp ;
  Coup liste[MaxCoup];

  n = mkcoup(&mygrille, liste, autre(mygrille.kikijoue));

  r.val = Xloose ;
  r.coup = nocoup ; 
  if (n == 0) return r ;
  for (i = 0; i < n ;  i++) {
     jouer(&mygrille, &liste[i]);
     tmp = max() ; 
     dejouer(&mygrille, &liste[i]) ;
     if (tmp.val < r.val) {
	r.val = tmp.val ;
        r.coup = liste[i] ; 
     }
   }
  return r;
}


int main(int k, char ** argv) {      
  char * line;
  Coup c;
  Coup liste[MaxCoup];
  int nel;
  int etat;

  Return r ; 
  
  srand(getpid());

  mygrille.kikijoue = J;

  for(;;){
    printf("%s", strgrille(&mygrille));
    re:
      /* faire jouer l'humain */
      printf("entrer un coup ");
      line = xgetline(stdin);

  
      c = lirecoup(line+1);

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

    printf("la machine va jouer\n");

    r = max() ;  // explorer 

    if (r.val == Xwin) // imprimer
	printf("La position est gagnante, en jouant %s\n", strcoup(&r.coup)); 
    else if (r.val == Xloose) 
	printf("La position est perdante\n") ;
    else 
	assert(0) ; 
	
    //nel = mkcoup(&mygrille, liste);

    // la liste des coups trouvés a été affichée : posiions sur la grille entre 0 et 41

    //c = liste[rand() % nel];

    // ici on peut accéder à la valeur avec cout << c.ou << endl ; 
 
    printf("la machine joue %s\n", strcoup(&r.coup));
    jouer(&mygrille, &r.coup);

    if((etat = cfini(&mygrille)) != 0){
      strcfini(etat);
      break;
    }
  } 

  return 0;
}


char * strgrille(Grille * g){
  int l, c;
  static char str[MaxStrGrille];
  int istr = 0;
  char m;

  for(l = 0; l < M; l++){
    for(c = 0; c < N; c++){
      if (g->place[lc2p(l, c)] == Vide)
	m = '.';
      else if (g->place[lc2p(l, c)] == R)
        m = 'r';
      else if (g->place[lc2p(l, c)] == J)
        m = 'j';
      else
	assert(0);
      istr += snprintf(&str[istr], sizeof str - istr,
		      " %c", m);
    }
    istr += snprintf(&str[istr], sizeof str - istr, "\n");
  }

  if (g->kikijoue == R)
    m = 'r';
  else if (g->kikijoue == J)
    m = 'j';
  else
    assert(0);
  istr += snprintf(&str[istr], sizeof str - istr,
		  "%c joue\n", m);
  return str;
}

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


void liregrille(Grille * g, FILE * fd){
  int l, c;
  char * line;
  char * mot;

  for(l = 0; l < M; l++){
    line = xgetline(fd);

    mot = strtok(line, " \n");
    g->place[lc2p(l, 0)] = mot2val(mot);

    for(c = 1; c < N; c++){
      mot = strtok(NULL, " \n");
      g->place[lc2p(l, c)] = mot2val(mot);
    }
  }

  line = xgetline(fd);
  if (strcmp(line + 1, " joue\n") != 0){
    fprintf(stderr, "Je ne comprend pas qui joue\n");
    exit(1);
  }
  g->kikijoue = mot2val(line);
}



/************* TT3   ************/

char * strcoup(Coup * coup){
  static char str[MaxStrCoup];
  char m;
  int l, c;

  if (coup->ki == R)
    m = 'r';
  else if (coup->ki == J)
    m = 'j';
  else
    assert(0);
  c = coup->ou / N;
  l = coup->ou % N ;
  snprintf(str, sizeof str, "%c en %d,%d", m, l, c);
  return str;
}


Coup lirecoup(char * line){
  char * mot;
  Coup coup;
  int l, c;

  mot = strtok(line, " ,\n");
  coup.ki = mot2val(mot); 

  mot = strtok(NULL, " ,\n");
  mot = strtok(NULL, " ,\n");
  if (sscanf(mot, "%d", &c) != 1){
    fprintf(stderr, "pas de numero de colonne dans %s\n", mot);
    exit(1);
  }

  if (c >= N) { coup.ou = Rate ; return coup ;}

  // calcul de la ligne où va etre placer le jeton
  for (l = M-1 ; l >= 0 ; l--) {
	if (mygrille.place[l * N + c] == Vide) break ;  // on commence par le bas dès que c'est vide on stop
	} 

  assert(l >= 0 )  ; // suffisant ? un coup dans une colonne déjà pleine n'est pas permis	
  
  coup.ou = lc2p(l, c) ;  // position du coup

  return coup;
}  


static inline int autre(int ki){
  if (ki == J)
    return R;
  else if (ki == R)
    return J;
  assert(0);
}


void jouer(Grille * g, Coup * c){
  assert(g->place[c->ou] == Vide);
  assert(g->kikijoue == c->ki);
  g->place[c->ou] = c->ki;
  g->kikijoue = c;
}

void dejouer(Grille * g, Coup * c){
  assert(g->place[c->ou+N] == c->ki);   
  assert(g->kikijoue == autre(c->ki));
  g->place[c->ou+N] = Vide;  
  g->kikijoue = autre(g->kikijoue);
}



/************************************* TT4   *******************************************************/


int cfini(Grille * g){
  int cc, c, l, ll;
  int type;
  int nbCaseLigne= 0;
  for(l = 0; l < M; l++){
    for(c = 0; c < N; c++){
      type = g->place[lc2p(l, c)];
      if (type != Vide){
        nbCaseLigne= 1;
        // on verifie l'alignement sur du vertical haut vers le bas à partir de la position occurente 
        for(ll = l; ll < M; ll++){
          if (g->place[lc2p(ll, c)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // on verifie l'alignement du vertical bas vers le haut à partir de la position occurente
        for(ll = l; ll >= 0; ll--){
          if (g->place[lc2p(ll, c)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // on verifie l'alignement du horizontal de la gauche vers la droite à partir de la position occurente
        for(cc = c; cc < N; cc++){
          if (g->place[lc2p(l, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // on verifie l'alignement du horizontal de la droite vers la gauche à partir de la position occurente
        for(cc = c; cc >= 0; cc--){
          if (g->place[lc2p(l, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // On verifie l'alignement sur la diagonale haut-gauche
        for(cc = c, ll= l; cc >= 0 && ll >= 0; cc--, ll--){
          if (g->place[lc2p(ll, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else nbCaseLigne++;
        }

        nbCaseLigne= 1;
        // On verifie l'alignement sur la diagonale haut-droite
        for(cc = c, ll= l; cc < N && ll >= 0; cc++, ll--){
          if (g->place[lc2p(ll, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // On verifi l'alignement sur la diagonale bas-droite
        for(cc = c, ll= l; cc < N && ll < M; cc++, ll++){
          if (g->place[lc2p(ll, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }

        nbCaseLigne= 1;
        // On verifi l'alignement sur la diagonale bas-gauche
        for(cc = c, ll= l; cc >= 0 && ll < M; cc--, ll++){
          if (g->place[lc2p(ll, cc)] != type) break;
          else if(nbCaseLigne >= 4) return type; // la partie est finie et il retourne le joueur gagnant
          else ++nbCaseLigne;
        }       
      }
    }
  }

  // pas de gagnant ; reste-t-il un coup à jouer ?
  for(int cc = 0; cc < N; cc++)
    if (g->place[lc2p(l, cc)] == Vide) return 0; // ce n'est pas fini car il ya une case vide

  return Fini; // partie est terminer pas de gagnant
}


void strcfini(int etat){
  if(etat == Fini) printf("Match nul");
  else if(etat == J) printf("Le joueur Rouge a gagné !");
  else if(etat == R) printf("Le joueur Jaune a gagné !");
}



/* mkcoup  --  la liste des coups légaux, tout simplement les colonnes où il y a encore de la place  */
int mkcoup2(Grille * g, Coup c[]){
  int i;
  int icoup = 0;
  int ligne, col  ;
  for(ligne = 0; ligne < M; ligne++){
    for(col = 0; col < N; col++){
      // une place vide avec une case non vide en dessous, ou bien une case vide qui n'a pas de case en dessous
      if (g->place[lc2p(ligne, col)] == Vide && (g->place[lc2p(ligne+1, col)] != Vide || ligne == M-1) ){
      i = lc2p(ligne, col) ; 
      c[icoup].ou = i;
      c[icoup].ki = g->kikijoue;
      icoup += 1; 
      }
    }
  }

  printf("Il y a %d coup possibles : ", icoup);
  for (i = 0 ; i < icoup ; i++) printf("%d ", c[i].ou);
  printf("\n") ; 
  return icoup;
}


/* mkcoup  --  la liste des coups légaux, tout simplement les colonnes où il y a encore de la place  */
int mkcoup(Grille * g, Coup c[], int kikijoue){
  int i;
  int icoup = 0;
  int ligne, col  ;
  for(ligne = 0; ligne < M; ligne++){
    for(col = 0; col < N; col++){
      // une place vide avec une case non vide en dessous, ou bien une case vide qui n'a pas de case en dessous
      if (g->place[lc2p(ligne, col)] == Vide && (g->place[lc2p(ligne+1, col)] != Vide || ligne == M-1) ){
      i = lc2p(ligne, col) ; 
      c[icoup].ou = i;
      c[icoup].ki = kikijoue;
      icoup += 1; 
      }
    }
  }

  printf("Il y a %d coup possibles : ", icoup);
  for (i = 0 ; i < icoup ; i++) printf("%d ", c[i].ou);
  printf("\n") ; 
  return icoup;
}


/* La fonction utilisée pour tester cfini() ./play < damier3 par exemple */
int test(int k, char ** argv) {
  int etat;
  liregrille(&mygrille, stdin);
  printf("%s", strgrille(&mygrille));
  if((etat = cfini(&mygrille)) != 0){
      strcfini(etat);
    }
  return 0 ;
}






int main2(int k, char ** argv) {      
  char * line;
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

  
      c = lirecoup(line+1);

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
    nel = mkcoup2(&mygrille, liste);

    // la liste des coups trouvés a été affichée : posiions sur la grille entre 0 et 41

    c = liste[rand() % nel];

    // ici on peut accéder à la valeur avec cout << c.ou << endl ; 
 
    printf("la machine joue %s\n", strcoup(&c));
    jouer(&mygrille, &c);

    if((etat = cfini(&mygrille)) != 0){
      strcfini(etat);
      break;
    }
  } 

  return 0;
}

