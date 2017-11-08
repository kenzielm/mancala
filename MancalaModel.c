#include <MancalaModel.h>
#include <stdio.h>
#include <stdlib.h>

void notify(MancalaModel * this) {
    if (this->update != NULL) {
	this->update(this);
    }
}

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

void ModelFree(MancalaModel * this) {
    if (this != NULL) {
	free(this);
    }
}

int checkPits(int * pits, int size) {
    int allpits = 0;
    for (int i = 0; i < size; i++) {
	allpits += pits[i];
    }
    return allpits;
}

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
	int stones = this->Player1Pits[pit];
	this->Player1Pits[pit] = 0;
	int bank = PLAYER1;

	for (int i = 0; i < stones; i++) {
	    if (pit <= 4) {
		if (bank == PLAYER1) {
		    this->Player1Pits[++pit] += 1;
		} else {
		    this->Player2Pits[++pit] += 1;
		}
	    } else if (pit == 5) {
		    if (bank == PLAYER1) {
		    this->Player1Bank++;
		    bank = PLAYER2;
		    pit = -1;
		} else {
		    this->Player2Pits[0] += 1;
		    pit = 0;
		    bank = PLAYER1;
		} 
	    }
	}

	if (checkPits(this->Player1Pits, PITCOUNT) == 0) {
	    this->GameState = GAMEOVER;
	    notify(this);
	    return GAMEOVER;
	} else if (pit == -1) {
	    this->GameState = MOVEAGAIN;
	    notify(this);
	    return MOVEAGAIN;
	}
	
	if (bank == PLAYER1 && this->Player1Pits[pit] == 1) {
	    this->Player1Pits[pit] = 0;
	    this->Player1Bank++;
	    int steal = 5 - pit;
	    this->Player1Bank += this->Player2Pits[steal];
	    this->Player2Pits[steal] = 0;
	}
	
	this->turn = (this->turn + 1) % 2;
	this->GameState = MOVECOMPLETE;
	notify(this);
	return MOVECOMPLETE; 
	    

    }


}


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
	int stones = this->Player2Pits[pit];
	this->Player2Pits[pit] = 0;
	int bank = PLAYER2;

	for (int i = 0; i < stones; i++) {
	    if (pit <= 4) {
		if (bank == PLAYER2) {
		    this->Player2Pits[++pit] += 1;
		} else {
		    this->Player1Pits[++pit] += 1;
		}
	    } else if (pit == 5) {
		    if (bank == PLAYER2) {
		    this->Player2Bank++;
		    bank = PLAYER1;
		    pit = -1;
		} else {
		    this->Player1Pits[0] += 1;
		    pit = 0;
		    bank = PLAYER2;
		} 
	    }
	}

	if (checkPits(this->Player2Pits, PITCOUNT) == 0) {
	    this->GameState = GAMEOVER;
	    notify(this);
	    return GAMEOVER;
	} else if (pit == -1) {
	    this->GameState = MOVEAGAIN;
	    notify(this);
	    return MOVEAGAIN;
	}
	
	if (bank == PLAYER2 && this->Player2Pits[pit] == 1) {
	    this->Player2Pits[pit] = 0;
	    this->Player2Bank++;
	    int steal = 5 - pit;
	    this->Player2Bank += this->Player1Pits[steal];
	    this->Player1Pits[steal] = 0;
	}

	this->turn = (this->turn + 1) % 2;
	this->GameState = MOVECOMPLETE;
	notify(this);
	return MOVECOMPLETE; 
	    

    }

}


