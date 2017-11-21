all:	ModelTest mancala
MancalaModel.o:	MancalaModel.c
	gccx -c MancalaModel.c -I.
ModelTest:	ModelTest.c MancalaModel.o
	gccx -o ModelTest ModelTest.c MancalaModel.o -I.
mancala:	mancala.c MancalaModel.o
	gccx -o mancala mancala.c MancalaModel.o -I .
clean:	
	rm MancalaModel.o ModelTest mancala
