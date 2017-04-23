all: start

start :
	gcc -Wall -g p4vmLib.c p4vmAleatoire.c -o play_aleatoire
	gcc -Wall -g p4vmLib.c p4vmHvsM.c -o play_HvsM
	gcc -Wall -g p4vmLib.c p4vmAlphabeta.c -o play_alphabeta
	gcc -Wall -g p4vmLib.c p4vmMinmax.c -o play_minmax
	gcc -Wall -g p4vmLib.c p4vmMC.c -o play_mc







