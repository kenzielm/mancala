/* Sezny Watkins, Sydney Garnett, Jack Bens, McKenzie Maurer
 * Primary author: Sezny
 * Fall 2017
 * the levels for the mancala ai - returns its' move
 */

#include "ai.h"


//the easiest level - just returns a random number for a bin that's not empty
int easy(){
    int r=random();
   //CHANGE!!!!!!!!!!!!!!
    //get a new random bucket if the first one selected is empty
    while (Payer1Pits[r]==0){
	r=random();
    }
    return r;
}



