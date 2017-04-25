PUISSANCE4 VERSION MISÈRE 
---------------------------------------------------------

------------------------------
|   Roxane Desrousseaux      |
---------------------------------------------------------
|   Fodé Hissirou            |
------------------------------


Règle du Jeu Puissance4 version Misère:
---------------------------------------------------------

Dans la version misère de puissance4, le joueur perdant est celui qui réalise en premier un alignement (vertical,horizontal,diagonal) d'au moins quatre pions de sa couleur. 
Si toutes les cases de la grille de jeu sont remplies et qu'aucun des deux joueurs n'a réalisé un tel alignement, la partie est déclarée nulle. 
Chaque joueur dispose de 21 pions d'une couleur (par convention, en général jaune ou rouge). Tour à tour les deux joueurs placent un pion dans la colonne de leur choix (0 1 2 3 4 5 ou 6).
Le pion coulisse jusqu'à la position la plus basse possible dans la dite colonne et c'est alors à l'adversaire de jouer.


Compilation:
---------------------------------------------------------
make

La commande renvoie le message suivant (six exécutables suivant sont générés):  <br>

g++ -Wall -g p4vmLib.c p4vmAleatoire.c -o play_aleatoire <br>
g++ -Wall -g p4vmLib.c p4vmHvsM.c ab.c -o play_HvsM  <br>
g++ -Wall -g p4vmLib.c p4vmAlphabeta.c -o play_alphabeta  <br>
g++ -Wall -g p4vmLib.c p4vmMinmax.c -o play_minmax  <br>
g++ -Wall -g p4vmLib.c mc.c p4vmMC.c -o play_mc  <br>
g++ -Wall -g p4vmLib.c mc.c p4vm_MC_vs_AB.c ab.c -o play_mc_vs_ab  <br>

Exemples de commandes : 
---------------------------------------------------------
* ./play_alphabeta < damiers/damier2  <
* ./play_minmax < damiers/damier2
* ./play_HvsM
* ./play_Aleatoire
* ./play_mc 10     (l'argument indique le nombre de playout)
* ./play_ms_vs_ab

Les exécutables ./play_aleatoire,  ./play_HvsM et ./play_mc permettent de jouer tout à tour contre l'ordinateur.  <br>
Dans le premier cas l'ordinateur calcule la liste des coups possibles et en joue un aléatoirement. <br>
Dans le deuxième cas, l'ordinateur joue comme un "joueur parfait", alphabeta avec profondeur limitée est appliquée pour chercher le meilleur coup possible. <br>
Dans le troisième cas, l'ordinateur joue en jouant un coup trouvé par la méthode de Monte Carlo.  <br>

Les exécutables ./play_minmax , ./play_alphabeta prennent en entrée un damier et renvoie le joueur qui possède la position gagnante. <br>
L'exécutable ./play_mc_vs_ab [nbplayout] simule 200 parties de jeu entre un joueur parfait et un joueur monte carlo. <br>
Un score de -190 indique que le joueur monte carlo a gagné (200 - 190) = 10 parties. <br>





Exemples de résultats attendus :
-----------------------------------------------------

 * ./play_minmax < damiers/damier1 <br>
 r . . j r . .  <br>
 r . . j r j j   <br>
 j . r j r j r  <br>
 j . j r j r r  <br>
 r . r r r j j <br>
 r j j j r j r <br>
r joue <br>

Le joueur Jaune gagne !
Résultat de l'exploration totale : 927 noeuds
Ici le damier envoyé indiquait que rouge devait jouer mais minmax a trouvé que jaune avait une solution gagnante.

Pour le même damier : 
* ./play_alphabeta < damiers/damier1  <br>
 r . . j r . . <br>
 r . . j r j j <br>
 j . r j r j r <br>
 j . j r j r r <br>
 r . r r r j j <br> 
 r j j j r j r <br>
r joue <br>

Le joueur Jaune gagne !
Résultat de l'exploration totale : 23 noeuds
Ici le damier envoyé indiquait que rouge devait jouer mais alphabeta a trouvé que jaune avait une solution gagnante. <br>


* ./play_minmax < damiers/damier2 <br>
 . . . j r . . <br>
 r . . j r j j <br> 
 j . r j r j r <br>
 j . j r j r r <br>
 r . r r r j j <br>
 r j j j r j r <br>
j joue <br>

Le joueur Rouge gagne!
Résultat de l'exploration totale : 10658 noeuds
Ici le damier envoyé indiquait que jaune devait jouer mais alphabeta a trouvé que rouge avait une solution gagnante. <br>



Une exploration énorme que minmax ne sait pas résoudre
* ./play_alphabeta < damiers/damier7 <br>
 . . . . . . j <br>
 . . . . . . r <br>
 . . . r . j r <br> 
 . . . r j r r <br>
 r j . j j r j <br>
 j r r j j j r <br>
j joue <br>


Le joueur Rouge gagne!
Résultat de l'exploration totale : 11586708 noeuds


Un exemple sur un match nul : 

./play_alphabeta < damiers/damier9<br>
* r r . j . . .
* j j r r . . .
* r r j j . . .
* j j r r . . .
* r r j j r j .
* j j r j r j r
j joue<br>

Match nul
Résultat de l'exploration totale : 3373 noeuds



Une simulation entre joueur parfait et mc
./play_mc_vs_ab 200<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
j joue<br>
200 playouts: score -108<br>



Un exemple de déroulement de jeu contre mc ( le principe est le même avec ./play_aleatoire et ./play_HvsM, il n'y a que la stratégie de jeu de l'ordinateur qui change)<br>

* ./play_mc 100
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
j joue<br>
entrer un coup j j en 0<br>
coup lu j en 0,5<br>
la machine joue r en 2,5<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* j . r . . . .
j joue<br>
entrer un coup j j en 6<br>
coup lu j en 6,5<br>
la machine joue r en 1,5<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* j r r . . . j
j joue<br>
entrer un coup j j en 5<br>
coup lu j en 5,5<br>
la machine joue r en 0,4<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* . . . . . . .
* r . . . . . .
* j r r . . j j
j joue<br>
entrer un coup j j en 4<br>
coup lu j en 4,5<br>
la machine joue r en 0,3<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* r . . . . . .
* r . . . . . .
* j r r . j j j
j joue<br>
entrer un coup j j en 6<br>
coup lu j en 6,4<br>
la machine joue r en 5,4<br>
* . . . . . . .
* . . . . . . .
* . . . . . . .
* r . . . . . .
* r . . . . r j
* j r r . j j j
j joue<br>
entrer un coup j j en 5<br>
coup lu j en 5,3<br>
la machine joue r en 5,2<br>
* . . . . . . .
* . . . . . . .
* . . . . . r .
* r . . . . j .
* r . . . . r j
* j r r . j j j
j joue<br>
entrer un coup j j en 5<br>
coup lu j en 5,1<br>
la machine joue r en 5,0<br>
* . . . . . r .
* . . . . . j .
* . . . . . r .
* r . . . . j .
* r . . . . r j
* j r r . j j j
j joue<br>
entrer un coup j j en 0<br>
coup lu j en 0,2<br>
la machine joue r en 0,1<br>
* . . . . . r .
* r . . . . j .
* j . . . . r .
* r . . . . j .
* r . . . . r j
* j r r . j j j
j joue<br>
entrer un coup j j en 0<br>
coup lu j en 0,0<br>
la machine joue r en 6,3<br>
* j . . . . r .
* r . . . . j .
* j . . . . r .
* r . . . . j r
* r . . . . r j
* j r r . j j j
j joue<br>
entrer un coup j j en 6<br>
coup lu j en 6,2<br>
la machine joue r en 4,4<br>
* j . . . . r .
* r . . . . j .
* j . . . . r j
* r . . . . j r
* r . . . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 6<br>
coup lu j en 6,1<br>
la machine joue r en 1,4<br>
* j . . . . r .
* r . . . . j j
* j . . . . r j
* r . . . . j r
* r r . . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 6<br>
coup lu j en 6,0<br>
la machine joue r en 2,4<br>
* j . . . . r j
* r . . . . j j
* j . . . . r j
* r . . . . j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 4<br>
coup lu j en 4,3<br>
la machine joue r en 4,2<br>
* j . . . . r j
* r . . . . j j
* j . . . r r j
* r . . . j j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 4<br>
coup lu j en 4,1<br>
la machine joue r en 4,0<br>
* j . . . r r j
* r . . . j j j
* j . . . r r j
* r . . . j j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 1<br>
coup lu j en 1,3<br>
la machine joue r en 1,2<br>
* j . . . r r j
* r . . . j j j
* j r . . r r j
* r j . . j j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 1<br>
coup lu j en 1,1<br>
la machine joue r en 1,0<br>
* j r . . r r j
* r j . . j j j
* j r . . r r j
* r j . . j j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 2<br>
coup lu j en 2,3<br>
la machine joue r en 2,2<br>
* j r . . r r j
* r j . . j j j
* j r r . r r j
* r j j . j j r
* r r r . r r j
* j r r . j j j
j joue<br>
entrer un coup j j en 2<br>
coup lu j en 2,1<br>
la machine joue r en 2,0<br>
* j r r . r r j
* r j j . j j j
* j r r . r r j
* r j j . j j r
* r r r . r r j
* j r r . j j j
j joue <br>
entrer un coup j j en 3 <br>
coup lu j en 3,5 <br>

Le joueur Rouge gagne !  <br>


