#include <MancalaModel.h>
#include <stdio.h>
#include <stdlib.h>
#include <levels.h>

void printModel(MancalaModel * this) {
    printf("Player 2: %2d, %2d, %2d, %2d, %2d, %2d\n", this->Player2Pits[5], this->Player2Pits[4], this->Player2Pits[3], this->Player2Pits[2], this->Player2Pits[1], this->Player2Pits[0]);
    printf("%2d                              %2d\n", this->Player2Bank, this->Player1Bank);
    printf("Player 1: %2d, %2d, %2d, %2d, %2d, %2d\n", this->Player1Pits[0], this->Player1Pits[1], this->Player1Pits[2], this->Player1Pits[3], this->Player1Pits[4], this->Player1Pits[5]);
    char * state;
    if (this->GameState == GAMEOVER) {
	state = "GAMEOVER";
    } else if (this->GameState == MOVECOMPLETE) {
	state = "MOVECOMPLETE";
    } else if (this->GameState == MOVEAGAIN) {
	state = "MOVEAGAIN";
    } else if (this->GameState == NOTYOURTURN) {
	state = "NOTYOURTURN";
    } else if (this->GameState == READY) {
	state = "READY";
    } else if (this->GameState == PITEMPTY) {
	state = "PITEMPTY";
    } else if (this->GameState == OUTOFBOUNDS) {
	state = "OUTOFBOUNDS";
    } else {
	state = "UNKNOWN";
    }
    printf("Game state: %s     Next turn: %s\n\n", state, this->turn==0?"Player1":"Player2");
}

int main(/*int argc, char *argv[]*/) {
    char * buf = malloc(BUFSIZ);
    char * temp;
    size_t size = BUFSIZ;
    MancalaModel * model = ModelCreate(printModel);
    while (model->GameState != GAMEOVER) {
	if (model->turn == PLAYER1) {
	    printf("Player %d turn (pits 1-6): ", model->turn + 1);
	    getline(&buf, &size, stdin);
	    long move = strtol(buf, &temp, 10);
	    if (move < 1 || move > 6) {
		printf("error: invalid move, expecting number between 1 and 6\n");
	    } else {
		Player1Move(model, move - 1);
	    }
	} else {
	    Player2Move(model, easy(model->Player1Pits));
	}
    }


}
