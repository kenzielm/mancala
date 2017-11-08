typedef struct MancalaModel MancalaModel;
//return void update(*MancalaModel)
//void (*update)(*MancalaModel) = &fun;
MancalaModel * ModelCreate(void (*update)(MancalaModel *));
void ModelFree(MancalaModel * this);

#define PLAYER1 0
#define PLAYER2 1

#define GAMEOVER 999
#define MOVECOMPLETE 100
#define MOVEAGAIN 200
#define READY 0
#define NOTYOURTURN 300
#define PITEMPTY 400
#define OUTOFBOUNDS 500

int Player1Move(MancalaModel * this, int pit); //player 1 moves from pit 0-5, returns int indicating outcome
int Player2Move(MancalaModel * this, int pit); //player 2 moves from pit 0-5, returns int indicating outcome
int Player1Score(MancalaModel * this); //returns player 1's score
int Player2Score(MancalaModel * this); //returns player 2's score

#define PITCOUNT 6

int* Player1Pits(MancalaModel * this); //returns array of how many marbles are in each pit on player 1's side
int* Player2Pits(MancalaModel * this); //returns array of how many marbles are in each pit on player 2's side

struct MancalaModel {
    void (*update)(MancalaModel *);
    int Player1Bank;
    int Player2Bank;
    int Player1Pits [6];
    int Player2Pits [6];
    int turn;
    int GameState;
};

