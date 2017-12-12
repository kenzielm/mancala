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

//hardest (for now) level
int hard(int* AIpits, int *PlayerPits, int AIscore){
    //get info - are we losing, can we steal any of theirs, can they take any of ours, can we land in home
    int out=losing(AIscore, AIpits);
    int offense=theivery(PlayerPits, AIpits);
    int defensive=defense(PlayerPits, AIpits);
    int steal;

    //if we can steal from them, find out how much
    if (offense!=-1){
	steal =PlayerPits[5-((offense+AIpits[offense])%13)];
    }

    //if we're almost out & about to lose then strategy revolves around stallinguntil we have more marbels
    if (out==1){
	printf("thinks it's running out");
	//we can't afford to lose a whole pit, so play defense if needed
	if (defensive!=-1){
	    return defensive;
	}
	//otherwise, we can play offense if we don't lose too many marbels or if we would steal enough for it to be worth it
	else if (offense!=-1){
	    if (AIpits[offense]>2 || steal+AIscore+1>24){
		return offense;
	    }
	}
	//otherwise, we move whatever is farthest back to stall
	else {
	    for (int i=0; i<6; i++){
		if (AIpits[i]>0){
		    return i;
		}
	    }
	}
    }
    int again=home(AIpits);
    
    //tells us if we can steal more than we can lose or not
    //0 if they can steal more from us than from them
    //1 if we can steal more from them than they can from us (or if it's equal, cause then we'll just hope they don't notice they can steal from us)
    //-1 if neither are possible
    printf("is comparing");
    int compare;
    if (defensive!=-1 && offense!=-1){
	if (AIpits[defensive]>steal){
	    compare=0;
	}
	else {
	    compare=1;
	}
    }
    else if (defensive!=-1){
	compare=0;
    }
    else if(offense!=-1){
	compare=1;
    }
    else{
	compare=-1;
    }

    //if they can steal more from you than you can from them, play defensively and move what they would otherwise steal
    if (compare==0){
	printf("thinks we should be defending");
	//landing in home & going again can't interfere with this, so go ahead and do it if you can
	if (again!=-1){
	    return again;
	}
	else {
	    return defensive;
	}
    }

    //if we can steal more from them than they can from us, then play offensively, and steal their stuff
    if (compare==1){
	printf("Thinks we should be stealing");
	//if we can land in our home, make sure it won't interfere with our thievery before doing it
	//or if it would make us even more successful thieves
	if (again!=-1){
	    if (again>offense){
		return again;
	    }
	    else if (PlayerPits[5-again]>steal){
		int possiblePits[6];
		for (int i=0; i<6; i++){
		    possiblePits[i]=AIpits[i];
		}
		possiblePits[again]=0;
		int possibleOffense=theivery(PlayerPits, possiblePits);
		if (possibleOffense!=-1 && PlayerPits[5-((AIpits[possibleOffense]+possibleOffense)%13)]){
		   return again;
		}
	    }
	}
    }
    //if neither of those are an option, go ahead and land in home to go again, if you can
    if (again!=-1){
	printf("is trying to land at home");
	return again;
    }

    //otherwise, try to move something that will be useful next time around
    int future=thinkAhead(PlayerPits, AIpits);
    if (future!=-1){
	printf("is thinking ahead");
	return future;
    }

    printf("has no strategy");

    //otherwise, just make a random move
    return easy(AIpits);
}
