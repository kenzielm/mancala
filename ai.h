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

//see if you can steal any of theirs
//if not return -1
//if so, return which pit you need to move
//return the one that can steal the most if there are multiples
int theivery(int *theirs, int *mine){
    //what to move
    int move=-1;
    //how many we're stealing (for determining the best one)
    int taking=0;
    //check each of your pits
    for (int i=0; i<6; i++){
	if (mine[i]>0){
	    //where it ends
	    int land=(i+mine[i])%13;
	    //check if it will be empty
	    if (land<6 && (land==i || mine[land]==0)){
		 //can we take more than the old one?
		if(theirs[5-land]>taking){
		    //if so, that's our new move - update our variables
		    taking=theirs[5-land];
		    move=i;
		}
	    }
	}
    }
    return move;
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


//determines if you're about to run out of marbles & lose
//returns 1 if we're about to lose, 0 otherwise
int losing(int score, int *pits){
    //if we've got more than half in our home, we're fine
    if (score>24){
	return 0;
    }
    //otherwise, check how many pits we still occupy
    int empty=0;
    for (int i=0; i<6; i++){
	//if we're in more than 3 we're fine 
	if (empty>3){
	    return 0;
	}
	if (pits[i]>0){
	    empty++;
	}
    }
    if (empty>3){
	return 0;
    }
    else{
	return 1;
    }
}

//finds the best one to move to be able to land there next time
int thinkAhead(int *theirs, int *mine){
    //the move
    int move=-1;
    //how many marbles we might be able to steal next turn from the current move
    int steal=0;
    //loop through your pits to find the best one to move
    for (int i=0; i<6; i++){
	//can we move & could it be better than our current move
	if(mine[i]>0 && theirs[5-i]>steal){
	    //loop through to see if moving any others next turn could end in this bucket
	    //account for the fact that there might be an additional marbel in the pits next turn
	    for(int j=0; j<6; j++){
		if((j+mine[j])%13==i || (j+1+mine[j])%13==i){
		    move=i;
		    steal=theirs[5-j];
		    break;
		}
	    }
	}
    }
    return move;
}


#endif
