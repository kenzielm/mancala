/* Sezny Watkins, Sydney Garnett, Jack Bens, McKenzie Maurer
 * Primary author: Sezny
 * Fall 2017
 * the levels for the mancala ai - returns its' move
 */

#include "ai.h"


//the easiest level - just returns a random number for a bin that's not empty
int easy(int*pits){
    int r=random();
    //get a new random bucket if the first one selected is empty
    while (pits[r]==0){
	r=random();
    }
    return r;
}


int medium(int* AIpits, int *PlayerPits){
    //if we can end in the home bucket and get another turn, do it
    int tryHome=home(AIpits);
    if (tryHome!=-1){
	return tryHome;
    }

    //otherwise, try to land in an empty pit & steal some of theirs
    int tryTheivery=theivery(PlayerPits, AIpits);
    if (tryTheivery!=-1){
	return tryTheivery;
    }

    //otherwise check if they can steal some of yours
    int tryDefense=defense(PlayerPits, AIpits);
    if (tryDefense!=-1){
	return tryDefense;
    }

    //if none of those work this AI thinks there's nothing strategic to do
    //and just makes a random move
    int move=random();
    while(AIpits[move]==0){
	move=random();
    }
    return move;
}

int hard(int* AIpits, int *PlayerPits, int AIscore, int PlayerScore){
}
