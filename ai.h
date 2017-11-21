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
//returns the number of the biggest pit they could steal from
//or -1 if they can't steal anything
int defense (int *theirs, int *mine){
    int concern=-1;
    //loop through their pits to find any that are empty
    //&& across from any of yours that aren't
    for (int i=0; i<6;i++){
	//if so, see if they can end in it
	if (theirs[i]==0 && mine[5-i]>0 && mine[5-i]>mine[concern]){
	    //boolean for if they can end there or not
	    int worry=0;
	    for(int j=i+1; j<6; j++){
		if (theirs[j]==(5-j)+7+(i+1)){
		    worry=1;
		    break;
		}
	    }
	    for (int j=0; j<i; j++){
		if (worry==1){
		    break;
		}
		if (theirs[j]==i-j || theirs[j]==(i-j)+13){
		    worry=1;
		    break;
		}
	    }
	    //if so, that's our new concern
	    if (worry==1){
		concern=5-i; 
	    }
	}
    }
    return concern;
}

#endif
