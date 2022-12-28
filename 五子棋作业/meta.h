/* All the main data. */
#ifndef META_H_
#define META_H_

#define BOARDWIDTH 20
#define BOARDSIZE 15
#define DIRECTIONS 4
#define SCORETYPES1 13
#define SCORETYPES2 3
#define MINSCORE0 100000000
#define MAXSCORE0 -100000000
#define SCORELAYERS 4
#define V 10
#define E 10

int layers;		// banned layers judging layers
int num;		// compete times
int calProcess;
int trim;

struct point {
	int state;				// player: -1; computer: 1; empty: 0
	int x;
	int y;
	long double value;      // score of point
	long double p_value;	// score of point for fastsort
	long double n_value;    // all score
};

int board[BOARDWIDTH][BOARDWIDTH];
int boardForCalculating[BOARDWIDTH][BOARDWIDTH];
int directions[8][2];
int input[4];
int scoreTypes1[SCORETYPES1][6];
int scoreTypes2[SCORETYPES2][7];
long double score[BOARDWIDTH][BOARDWIDTH];
long double allScores[BOARDWIDTH][BOARDWIDTH];
int maxPos[2];
int minPos[2];
int lastPos[2];
int sort[BOARDSIZE * BOARDSIZE];

#endif
