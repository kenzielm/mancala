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


int medium(int* AIpits, int *PlayerPits, int AIscore, int PlayerScore){
}

int hard(int* AIpits, int *PlayerPits, int AIscore, int PlayerScore){
}
