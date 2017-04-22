all: start

start :
	g++ -Wall -g p4vm.c p4vmlib.c -o play_simple
	g++ -Wall -g p4vmlib.c AlphaBeta.c -o play_AlphaBeta







