all: start

start :
	g++ -Wall -g p4vmLib.c p4vmAleatoire.c -o play_aleatoire
	g++ -Wall -g p4vmLib.c p4vmHvsM.c -o play_HvsM
	g++ -Wall -g p4vmLib.c p4vmAlphabeta.c -o play_alphabeta
	g++ -Wall -g p4vmLib.c p4vmMinmax.c -o play_minmax







