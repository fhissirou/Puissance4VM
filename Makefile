all: start

start :
	g++ -Wall -g p4vmLib.c p4vmAleatoire.c -o play_aleatoire
	g++ -Wall -g p4vmLib.c p4vmHvsM.c ab.c -o play_HvsM
	g++ -Wall -g p4vmLib.c p4vmAlphabeta.c -o play_alphabeta
	g++ -Wall -g p4vmLib.c p4vmMinmax.c -o play_minmax
	g++ -Wall -g p4vmLib.c mc.c p4vmMC.c -o play_mc
	g++ -Wall -g p4vmLib.c mc.c p4vm_MC_vs_AB.c ab.c -o play_mc_vs_ab







