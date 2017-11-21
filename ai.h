/*Sezny Watkins, Sydney Garnett, MckKenzie Maurer, Jack Bens
 * Primary author: Sezny
 * Fall 2017
 * The general functions all levels of the ai might use
 */

#ifndef AI_H_
#define AI_H_
#include <stdlib.h>


//randomly selects a bucket
int random(){
    return rand()%6;
}

//returns -1 if it can't end in the home (& go again)
//returns the number of the pit that can get home first
//returns the first one it finds, going from closest to the home to farthest
int home(int *pits){
    //go through all the pits 
    //from closest to the home to farthest left
    for (int i=5; i>=0; i--){
	//check if there's just enough cubes to get home
	if (pits[i]==6-i){
	    return i;
	}
    }
    //if none of them can reach home, return -1
    return -1;
}

//checks if the opponent can land in an empty pit & steal the AI's marbles
int defense (int *theirs, int *mine){
}

#endif
