all:	ModelTest mancala ASCIImancala
MancalaModel.o:	MancalaModel.c
	gccx -c MancalaModel.c -I.
ModelTest:	ModelTest.c MancalaModel.o
	gccx -o ModelTest ModelTest.c MancalaModel.o -I .
mancala:	mancala.c MancalaModel.o
	gccx -o mancala mancala.c MancalaModel.o -I .
ASCIImancala:	ASCIImancala.c MancalaModel.o
	gccx -o ASCIImancala ASCIImancala.c MancalaModel.o -I .
graphics: graphics.c #this should compile, it compiled on my mac, Not Clyde
	gccx graphics.c -o graphics -framework OpenGL -framework GLUT
clean:	
	rm MancalaModel.o ModelTest mancala ASCIImancala
