PUISSANCE4 VERSION MISÈRE 

------------------------------
|   Roxane Desrousseaux      |
|          &                 |
|   Fodé Hissirou            |
------------------------------


Règle du Jeu Puissance4 version Misère:

Dans la version misère de puissance4, le joueur perdant est celui qui réalise en premier un alignement (vertical,horizontal,diagonal) d'au moins quatre pions de sa couleur. 
Si toutes les cases de la grille de jeu sont remplies et qu'aucun des deux joueurs n'a réalisé un tel alignement, la partie est déclarée nulle. 
Chaque joueur dispose de 21 pions d'une couleur (par convention, en général jaune ou rouge). Tour à tour les deux joueurs placent un pion dans la colonne de leur choix (0 1 2 3 4 5 ou 6).
Le pion coulisse jusqu'à la position la plus basse possible dans la dite colonne et c'est alors à l'adversaire de jouer.



Compilation:
make

Les six exécutables suivant sont générés.

g++ -Wall -g p4vmLib.c p4vmAleatoire.c -o play_aleatoire
g++ -Wall -g p4vmLib.c p4vmHvsM.c ab.c -o play_HvsM
g++ -Wall -g p4vmLib.c p4vmAlphabeta.c -o play_alphabeta
g++ -Wall -g p4vmLib.c p4vmMinmax.c -o play_minmax
g++ -Wall -g p4vmLib.c mc.c p4vmMC.c -o play_mc
g++ -Wall -g p4vmLib.c mc.c p4vm_MC_vs_AB.c ab.c -o play_mc_vs_ab

Les exécutables ./play_aleatoire,  ./play_HvsM et  permettent de jouer tout à tour contre l'ordinateur.
Dans le premier cas l'ordinateur calcule la liste des coups possibles et en joue un aléatoirement.
Dans le deuxième cas, l'ordinateur joue comme un "joueur parfait", alphabeta avec profondeur limitée est appliquée pour chercher le meilleur coup possible.

Les exécutables ./play_minmax , ./play_alphabeta prennent en entrée un damier et renvoie le joueur qui possède la position gagnante.
Exemples d'éxécution :

 ./play_minmax < damiers/damier1
 r . . j r . .
 r . . j r j j
 j . r j r j r
 j . j r j r r
 r . r r r j j
 r j j j r j r
r joue

Le joueur Jaune gagne !
Résultat de l'exploration totale : 927 noeuds

./play_minmax < damiers/damier2
 . . . j r . .
 r . . j r j j
 j . r j r j r
 j . j r j r r
 r . r r r j j
 r j j j r j r
j joue

Le joueur Rouge gagne!
Résultat de l'exploration totale : 10658 noeuds



./play_alphabeta < damier2
./play_minmax < damier2
./play_HvsM
./play_Aleatoire