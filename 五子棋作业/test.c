/* Some test functions.*/
#include "endGame.h"
#include "board.h"
#include "meta.h"
#include "game.h"
#include <stdio.h>

int judge3Test()
{
	loadBoard();
	board[3][3] = 1;
	board[4][4] = 1;
	board[6][4] = 1;
	board[7][3] = 1;
	int row, line = 0;
	row = line = 5;
	copyBoard(); 
	printf("%d %d %d\n", row, line, judge3(row, line));
}

int judge4Test()
{
	loadBoard();
	board[3][3] = 1;
	board[4][4] = 1;
	board[7][7] = 1;
	copyBoard();
	printf("%d\n", judgeBannedPlaces(6, 6));
}