/* To judge if the game endsand other conditions. */

#ifndef ENDGAME_H_
#define ENDGAME_H_
#define BOARDWIDTH 20
#define BOARDSIZE 15
#define DIRECTIONS 4

// simpler version in the judgement functions
int posR(int r, int direc, int position);
int posL(int l, int direc, int position);
int j0(int r, int l, int direc, int position);
int j1(int r, int l, int direc, int position);
int j2(int r, int l, int direc, int position);
int positionR(int r, int direc, int position, int i);
int positionL(int l, int direc, int position, int i);

int boardHorizonBlack[BOARDWIDTH][BOARDWIDTH];
int boardVerticalBlack[BOARDWIDTH][BOARDWIDTH];
int boardLeftUpBlack[BOARDWIDTH][BOARDWIDTH];
int boardLeftDownBlack[BOARDWIDTH][BOARDWIDTH];
int boardHorizonWhite[BOARDWIDTH][BOARDWIDTH];
int boardVerticalWhite[BOARDWIDTH][BOARDWIDTH];
int boardLeftUpWhite[BOARDWIDTH][BOARDWIDTH];
int boardLeftDownWhite[BOARDWIDTH][BOARDWIDTH];

int readColor(int row, int line, int directionx, int directiony, int color);
void readAllColor();
int judgeGameEnding();
int judgeBoardGoingFull();

int posInBoard(int r, int l);	// judge if (r, l) is in board
int judgeBlack(int r, int l);
int judgeWhite(int r, int l);
int judgeBlank(int r, int l);
int judge3(int row, int line);
int judge4(int row, int line);
int judgeLong(int row, int line);
int judgeBannedPlaces(int r, int l);

void playerPutChess(int color);

// Test functions
int judge3Test();
int judge4Test();

#endif