#include <stdio.h>
#include "ai.h"


int defenseLoop(){
    int mine[6];
    int theirs[6];
    theirs[5]=0;
    theirs[4]=14;
    for (int i=0; i<4; i++){
	theirs[i]=1;
	mine[i]=5;
    }
    mine[4]=5;
    mine[5]=5;
    return defense(theirs, mine);
}

int defensePrioritize(){
    int mine[6];
    int theirs[6];

    theirs[5]=0;
    theirs[4]=1;
    theirs[3]=0;
    theirs[2]=1;
    theirs[1]=0;
    theirs[0]=1;
    mine[0]=3;
    mine[2]=6;
    mine[4]=1;
    mine[1]=3;
    mine[3]=3;
    mine[5]=3;
    return defense(theirs, mine);
}




int testDefense(){
    int mine[6];
    int theirs[6];
    theirs[0]=0;
    theirs[3]=0;
    theirs[1]=2;
    theirs[5]=0;
    theirs[4]=1;
    theirs[2]=6;
    mine[2]=0;
    mine[0]=5;
    mine[1]=6;
    for (int i=3; i<6; i++){
	mine[i]=i;
    }
    return defense(theirs, mine);
}


    
void testHome(){    
    int mine[6];
    for (int i=0; i<6; i++){
	mine[i]=i;
    }
    mine[4]=2;
    mine[0]=6;
    printf("move: %i \n", home(mine));
}

void testLosing(){
    int pits[6];
    for (int i=0; i<6; i++){
	pits[i]=0;
    }
    for (int i=0; i<6; i++){
	pits[i]=i;
	printf("with %i non-empty pits & bad score: %i \n", i, losing(10, pits));
	printf("and good score: %i \n", losing(30, pits));
    }
}


void testTheivery(){
    int theirs[6];
    int mine[6];
    for (int i=0; i<6; i++){
	theirs[i]=i;
	mine[i]=i;
    }
    printf("4 is: %i \n", mine[4]);
    printf("Can't steal: %i \n", theivery(theirs, mine));
    mine[5]=8;
    printf("Can steal by moving from 5: %i \n", theivery(theirs, mine));
    mine[2]=0;
    printf("Moving from 5 steals the most, 1 also works: %i \n", theivery(theirs, mine));
    mine[5]=0;
    printf("Only moving from 1 works: %i \n", theivery(theirs, mine));
    mine[1]=13;
    printf("Moving from 1 to get all the way round the board: %i \n", theivery(theirs, mine));
    mine[1]=4;
    printf("1 can land in 5 but won't steal anything: %i \n", theivery(theirs, mine));
}

void testThinkingAhead(){
    int theirs[6];
    int mine[6];
    for (int i=0; i<6; i++){
	theirs[i]=i;
	mine[i]=i;
    }
    printf("Should move from 1: %i \n", thinkAhead(theirs, mine));
}


int main(){
 //   printf("test defense (should be 0): %i \n", testDefense());
 //   printf("test defense's looping(should be 0): %i \n", defenseLoop());
//    printf("test defense's prioritizing (should be 2): %i \n", defensePrioritize());
   // testLosing();
    //testTheivery();
    testThinkingAhead();
}


