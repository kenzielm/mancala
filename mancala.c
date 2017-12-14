#include <MancalaModel.h>
#include <stdio.h>
#include <stdlib.h>
#include <levels.h>
#include <ctype.h>
#include <string.h>

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

int aiMove(MancalaModel * this, int lvl) {
    if (lvl == 1) {
	return easy(this->Player2Pits);
    } else if (lvl == 2) {
	return medium(this->Player2Pits, this->Player1Pits);
    } else if (lvl == 3) {
	return hard(this->Player2Pits, this->Player1Pits, this->Player2Bank);
    }	
    return '\0';
}

int main(int argc, char *argv[]) {
    char * buf = malloc(BUFSIZ);
    char * temp;
    size_t size = BUFSIZ;
    int l;
    if (argc > 1) {
	l = atoi(argv[1]);
	printf("AI LEVEL: %d\n", l);
    } else {
	l = 1;
	printf("AI LEVEL: 1\n");
    }
    MancalaModel * model = ModelCreate(printModel);
    while (model->GameState != GAMEOVER) {
	    printf("Player %d turn (pits 1-6): ", model->turn + 1);
	if (model->turn == PLAYER1) {
	    getline(&buf, &size, stdin);
	    long move = strtol(buf, &temp, 10);
	    if (move < 1 || move > 6) {
		printf("error: invalid move, expecting number between 1 and 6\n");
	    } else {
		Player1Move(model, move - 1);
	    }
	} else {
	    int level;
	    if (argc > 1) {
		level = aiMove(model, l);
	    } else {
		level = easy(model->Player2Pits);
	    }
	    printf("%d\n", level+1);
	    Player2Move(model, level);

	}
    }

    if (model->GameState == GAMEOVER) {
	printf("GAMEOVER\n");
	int winner;
	if (model->Player1Bank > model->Player2Bank) {
	    winner = PLAYER1;
	} else if (model->Player2Bank > model->Player1Bank) {
	    winner = PLAYER2;
	}
	printf("Winner: Player %d\n", winner + 1);
    }

}
