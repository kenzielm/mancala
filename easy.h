/* Sezny Watkins, Sydney Garnett, Jack Bens, McKenzie Maurer
 * Primary author: Sezny
 * Fall 2017
 * the easiest level of the ai for mancala
 * just chooses a random bucket to move
 */

#include "ai.h"

int move(){
    int r=random();
   //CHANGE!!!!!!!!!!!!!!
    //get a new random bucket if the first one selected is empty
    while (Payer1Pits[r]==0){
	r=random();
    }
    return r;
}



