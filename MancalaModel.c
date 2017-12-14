#include <MancalaModel.h>
#include <stdio.h>
#include <stdlib.h>

//calls update function
void notify(MancalaModel * this) {
    if (this->update != NULL) {
	this->update(this);
    }
}

//creates a new MancalaModel and sets up the board, player turn, and game state
MancalaModel * ModelCreate(void (*update_ptr)(MancalaModel *)) {
    MancalaModel * newModel = malloc(sizeof(MancalaModel));
    newModel->update = update_ptr;
    newModel->Player1Bank = 0;
    newModel->Player2Bank = 0;
    for (int i = 0; i < PITCOUNT; i++) {
	newModel->Player1Pits[i] = 4;
	newModel->Player2Pits[i] = 4;
    }
    newModel->turn = PLAYER1;
    newModel->GameState = READY;
    notify(newModel);
    return newModel;
}

//frees the memory allocated to the MancalaModel
void ModelFree(MancalaModel * this) {
    if (this != NULL) {
	free(this);
    }
}

//checks how many stones there are in the given array (current player's side)
int checkPits(int * pits, int size) {
    int allpits = 0;
    for (int i = 0; i < size; i++) {
	allpits += pits[i];
    }
    return allpits;
}

//checks all possible game state conditions before making the player's move
//returns the state of the game
//arguments are the MancalaModel and int which pit of stones the player wants to move
int Player1Move(MancalaModel * this, int pit) {

    if (this->turn != PLAYER1) {
	this->GameState = NOTYOURTURN;
	notify(this);
	return NOTYOURTURN;
    } else if (pit < 0 || pit > 5) {
	this->GameState = OUTOFBOUNDS;
	notify(this);
	return OUTOFBOUNDS;
    } else if (this->Player1Pits[pit] == 0) {
	this->GameState = PITEMPTY;
	notify(this);
	return PITEMPTY;
    } else {
	//takes the stones out of the chosen pit and stores them outside the board for the moment
	int stones = this->Player1Pits[pit];
	this->Player1Pits[pit] = 0;
	int bank = PLAYER1;

	//drops one stone in each consecutive pit or bank in a counter clockwise direction
	//(except the opposite player's bank) until stones run out
	for (int i = 0; i < stones; i++) {
	    //if the current pit is 0-4
	    if (pit <= 4) {
		//if the current pit is on the player's side
		if (bank == PLAYER1) {
		    //increment the pit and drop the stone into the new pit
		    this->Player1Pits[++pit] += 1;
		} else {
		    //if the current pit is on the other player's side
		    this->Player2Pits[++pit] += 1;
		}
	    } else if (pit == 5) {
		//if the current pit is 5, aka the last pit before the bank
		//drops the stone in player 1's bank but not player 2's
		if (bank == PLAYER1) {
		    this->Player1Bank++;
		    //changes the bank to indicate that we are  now on the other player's side
		    bank = PLAYER2;
		    //makes the current pit -1 so that on the next loop it will iterate
		    //to 0 (the first pit on the other side)
		    pit = -1;
		} else {
		    this->Player1Pits[0] += 1;
		    pit = 0;
		    bank = PLAYER1;
		} 
	    }
	}

	//checks to see if the game is over (i.e. either array of pits is empty)
	//or if the current player can take another move
	if ((checkPits(this->Player1Pits, PITCOUNT) == 0) || (checkPits(this->Player2Pits, PITCOUNT) == 0)) {
	    this->GameState = GAMEOVER;
	    notify(this);
	    return GAMEOVER;
	} else if (pit == -1) {
	    this->GameState = MOVEAGAIN;
	    notify(this);
	    return MOVEAGAIN;
	}
	
	//if the last stone was dropped in an empty pit on the player's side,
	//take that stone and all the stones in the opposite pit (on the other player's side)
	//and put them in the player's bank
	if ((bank == PLAYER1) && (this->Player1Pits[pit] == 1) && (this->Player2Pits[5-pit] >= 1)) {
	    this->Player1Pits[pit] = 0;
	    this->Player1Bank++;
	    int steal = 5 - pit;
	    this->Player1Bank += this->Player2Pits[steal];
	    this->Player2Pits[steal] = 0;
	}
	
	//set the turn to the other player and return that the move has been completed
	this->turn = (this->turn + 1) % 2;
	this->GameState = MOVECOMPLETE;
	notify(this);
	return MOVECOMPLETE; 
	    

    }


}

//functionally the same as Player2Move, just with all Player1's and Player2's switched
//checks all possible game state conditions before making the player's move
//returns the state of the game
//MancalaModel and int which pit of stones the player wants to move
int Player2Move(MancalaModel * this, int pit) {

    if (this->turn != PLAYER2) {
	this->GameState = NOTYOURTURN;
	notify(this);
	return NOTYOURTURN;
    } else if (pit < 0 || pit > 5) {
	this->GameState = OUTOFBOUNDS;
	notify(this);
	return OUTOFBOUNDS;
    } else if (this->Player2Pits[pit] == 0) {
	this->GameState = PITEMPTY;
	notify(this);
	return PITEMPTY;
    } else {
	//takes the stones out of the chosen pit and stores them outside the board for the moment
	int stones = this->Player2Pits[pit];
	this->Player2Pits[pit] = 0;
	int bank = PLAYER2;

	//drops one stone in each consecutive pit or bank (except the opposite player's bank) until stones run out
	for (int i = 0; i < stones; i++) {
	    if (pit <= 4) {
		if (bank == PLAYER2) {
		    this->Player2Pits[++pit] += 1;
		} else {
		    this->Player1Pits[++pit] += 1;
		}
	    } else if (pit == 5) {
		//drops the stone in player 1's bank but not player 2's
		    if (bank == PLAYER2) {
		    this->Player2Bank++;
		    bank = PLAYER1;
		    pit = -1;
		} else {
		    this->Player2Pits[0] += 1;
		    pit = 0;
		    bank = PLAYER2;
		} 
	    }
	}

	//checks to see if the game is over or if the current player can take another move
	if ((checkPits(this->Player2Pits, PITCOUNT) == 0) || (checkPits(this->Player1Pits, PITCOUNT) == 0)) {
	    this->GameState = GAMEOVER;
	    notify(this);
	    return GAMEOVER;
	} else if (pit == -1) {
	    this->GameState = MOVEAGAIN;
	    notify(this);
	    return MOVEAGAIN;
	}
	
	//if the last stone was dropped in an empty pit on the player's side,
	//take that stone and all the stones in the opposite pit (on the other player's side)
	//and put them in the player's bank
	if ((bank == PLAYER2) && (this->Player2Pits[pit] == 1) && (this->Player1Pits[5-pit] >= 1)) {
	    this->Player2Pits[pit] = 0;
	    this->Player2Bank++;
	    int steal = 5 - pit;
	    this->Player2Bank += this->Player1Pits[steal];
	    this->Player1Pits[steal] = 0;
	}

	//set the turn to the other player and return that the move has been completed
	this->turn = (this->turn + 1) % 2;
	this->GameState = MOVECOMPLETE;
	notify(this);
	return MOVECOMPLETE; 
	    

    }

}

//returns how many stones are in player 1's bank
int Player1Score(MancalaModel * this) {
    return this->Player1Bank;
}

//returns how many stones are in player 2's bank
int Player2Score(MancalaModel * this) {
    return this->Player2Bank;
}

//returns array of how many marbles are in each pit on player 1's side
int * Player1Pits(MancalaModel * this) {
    return this->Player1Pits;
}

//returns array of how many marbles are in each pit on player 2's side
int * Player2Pits(MancalaModel * this) {
    return this->Player2Pits;
}
