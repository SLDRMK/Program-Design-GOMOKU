/* To judge if the game endsand other conditions. */
#include <stdio.h>
#include <stdlib.h>
#include "endGame.h"
#include "board.h"
#include "game.h"
#include "meta.h"

int readColor(int row, int line, int directionx, int directiony, int color)
{
	//	row, line to decide position, directionx, y to decide direction,
	//	color 1, 3 to represent black, 2, 4 to represent white
	int temp = 0;
	for (int m = 0; m < 5 && row + directionx * m >= 1 && row + directionx * m <= BOARDSIZE
		&& line + directiony * m >= 1 && line + directiony * m <= BOARDSIZE 
		&& (board[row + directionx * m][BOARDSIZE + 1 - (line + directiony * m)] == color 
			|| board[row + directionx * m][BOARDSIZE + 1 - (line + directiony * m)] == color + 2); m++)
	{
		temp++;
	}
	return temp;
}

void readAllColor()
{
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			int isBlack = 0;
			int isWhite = 0;
			if (board[r][BOARDSIZE + 1 - l] == 1 || board[r][BOARDSIZE + 1 - l] == 3)
				isBlack = 1;
			if (board[r][BOARDSIZE + 1 - l] == 2 || board[r][BOARDSIZE + 1 - l] == 4)
				isWhite = 1;
			boardHorizonBlack[r][l] = (readColor(r, l, 1, 0, 1) + readColor(r, l, -1, 0, 1) - isBlack) * isBlack;
			boardVerticalBlack[r][l] = (readColor(r, l, 0, 1, 1) + readColor(r, l, 0, -1, 1) - isBlack) * isBlack;
			boardLeftUpBlack[r][l] = (readColor(r, l, 1, -1, 1) + readColor(r, l, -1, 1, 1) - isBlack) * isBlack;
			boardLeftDownBlack[r][l] = (readColor(r, l, 1, 1, 1) + readColor(r, l, -1, -1, 1) - isBlack) * isBlack;
			boardHorizonWhite[r][l] = (readColor(r, l, 1, 0, 2) + readColor(r, l, -1, 0, 2) - isWhite) * isWhite;
			boardVerticalWhite[r][l] = (readColor(r, l, 0, 1, 2) + readColor(r, l, 0, -1, 2) - isWhite) * isWhite;
			boardLeftUpWhite[r][l] = (readColor(r, l, 1, -1, 2) + readColor(r, l, -1, 1, 2) - isWhite) * isWhite;
			boardLeftDownWhite[r][l] = (readColor(r, l, 1, 1, 2) + readColor(r, l, -1, -1, 2) - isWhite) * isWhite;
		}
	}
}

int judgeGameEnding()
{
	readAllColor();
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			if (boardHorizonBlack[r][l] >= 5 || boardVerticalBlack[r][l] >= 5
				|| boardLeftUpBlack[r][l] >= 5 || boardLeftDownBlack[r][l] >= 5
				|| boardHorizonWhite[r][l] >= 5 || boardVerticalWhite[r][l] >= 5
				|| boardLeftUpWhite[r][l] >= 5 || boardLeftDownWhite[r][l] >= 5)
				return 1;
		}
	}
	return 0;
}

int judgeBlack(int r, int l)
{ 
	return boardForCalculating[r][l] == 1 || boardForCalculating[r][l] == 3; 
}

int judgeWhite(int r, int l)
{
	return boardForCalculating[r][l] == 2 || boardForCalculating[r][l] == 4;
}

int judgeBlank(int r, int l)
{
	return boardForCalculating[r][l] == 0;
}

int judgeBoardGoingFull()
{
	int fullPoints = 0;
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			if (boardForCalculating[r][l] == 0)
			{
				fullPoints++;
			}
		}
	}
	return (fullPoints == 0);
}

int posR(int r, int direc, int position) { return r + position * directions[direc][0]; }
int posL(int l, int direc, int position) { return l + position * directions[direc][1]; }
int j0(int r, int l, int direc, int position) { return judgeBlank(posR(r, direc, position), posL(l, direc, position)); }
int j1(int r, int l, int direc, int position) { return judgeBlack(posR(r, direc, position), posL(l, direc, position)); }
int j2(int r, int l, int direc, int position) { return judgeWhite(posR(r, direc, position), posL(l, direc, position)); }
int positionR(int r, int direc, int position, int i) { return r + (-i + position) * directions[direc][0]; }
int positionL(int l, int direc, int position, int i) { return l + (-i + position) * directions[direc][1]; }
int posInBoard(int r, int l) { return r >= 1 && r <= 15 && l >= 1 && l <= 15; }

// to count the number of alive threes
int judge3(int r, int l)
{
	int threes = 0;
	int temp = 0;
	/*
	// check horizontal
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 3; l <= BOARDSIZE - 4; l++)
		{
			// _xooox_, at most one '_' is white, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r, l + 1) && judgeBlack(r, l + 2) && judgeBlank(r, l - 1)
				&& judgeBlank(r, l + 3) && (!judgeWhite(r, l - 2) || !judgeWhite(r, l + 4)))
			{
				boardForCalculating[r][l - 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r][l - 1] = 0;
					boardForCalculating[r][l + 3] = 1;
					if (!judgeBannedPlaces())
					{
						threes++;
						boardForCalculating[r][l + 3] = 0;
					}
				}
				boardForCalculating[r][l - 1] = 0;
				boardForCalculating[r][l + 3] = 0;
			}
		}
	}
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 2; l <= BOARDSIZE - 4; l++)
		{
			// xooxox or xoxoox, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r, l + 3) && judgeBlank(r, l - 1) && judgeBlank(r, l + 4) 
				&& (judgeBlack(r, l + 1) && judgeBlank(r, l + 2)) || (judgeBlank(r, l + 1) && judgeBlack(r, l + 2)))
			{
				boardForCalculating[r][l - 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r][l - 1] = 0;
					boardForCalculating[r][l + 2] = 1;
					if (!judgeBannedPlaces())
					{
						boardForCalculating[r][l + 2] = 0;
						boardForCalculating[r][l + 4] = 1;
						if (!judgeBannedPlaces())
						{
							threes++;
							boardForCalculating[r][l + 4] = 0;
						}
					}
				}
				boardForCalculating[r][l - 1] = 0;
				boardForCalculating[r][l + 2] = 0;
				boardForCalculating[r][l + 4] = 0;
			}
		}
	}
	// check vertical
	for (int r = 3; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			// _xooox_, at most one '_' is white, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 1, l) && judgeBlack(r + 2, l) && judgeBlank(r - 1, l)
				&& judgeBlank(r + 3, l) && (!judgeWhite(r - 2, l) || !judgeWhite(r + 4, l)))
			{
				boardForCalculating[r - 1][l] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l] = 0;
					boardForCalculating[r + 3][l] = 1;
					if (!judgeBannedPlaces())
					{
						threes++;
						boardForCalculating[r + 3][l] = 0;
					}
				}
				boardForCalculating[r - 1][l] = 0;
				boardForCalculating[r + 3][l] = 0;
			}
		}
	}
	for (int r = 2; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			// xooxox or xoxoox, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 3, l) && judgeBlank(r - 1, l) && judgeBlank(r + 4, l)
				&& (judgeBlack(r + 1, l) && judgeBlank(r + 2, l)) || (judgeBlank(r + 1, l) && judgeBlack(r + 2, l)))
			{
				boardForCalculating[r - 1][l] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l] = 0;
					boardForCalculating[r + 2][l] = 1;
					if (!judgeBannedPlaces())
					{
						boardForCalculating[r + 2][l] = 0;
						boardForCalculating[r + 4][l] = 1;
						if (!judgeBannedPlaces())
						{
							threes++;
							boardForCalculating[r + 4][l] = 0;
						}
					}
				}
				boardForCalculating[r - 1][l] = 0;
				boardForCalculating[r + 2][l] = 0;
				boardForCalculating[r + 4][l] = 0;
			}
		}
	}
	// check diag
	for (int r = 3; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 3; l <= BOARDSIZE - 4; l++)
		{
			// _xooox_, at most one '_' is white, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 1, l + 1) && judgeBlack(r + 2, l + 2) && judgeBlank(r - 1, l - 1)
				&& judgeBlank(r + 3, l + 3) && (!judgeWhite(r - 2, l - 2) || !judgeWhite(r + 4, l + 4)))
			{
				boardForCalculating[r - 1][l - 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l - 1] = 0;
					boardForCalculating[r + 3][l + 3] = 1;
					if (!judgeBannedPlaces())
					{
						threes++;
						boardForCalculating[r + 3][l + 3] = 0;
					}
				}
				boardForCalculating[r - 1][l - 1] = 0;
				boardForCalculating[r + 3][l + 3] = 0;
			}
		}
	}
	for (int r = 2; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 2; l <= BOARDSIZE - 4; l++)
		{
			// xooxox or xoxoox, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 3, l + 3) && judgeBlank(r - 1, l - 1) && judgeBlank(r + 4, l + 4)
				&& (judgeBlack(r + 1, l + 1) && judgeBlank(r + 2, l + 2)) || (judgeBlank(r + 1, l + 1) && judgeBlack(r + 2, l + 2)))
			{
				boardForCalculating[r - 1][l - 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l - 1] = 0;
					boardForCalculating[r + 2][l + 2] = 1;
					if (!judgeBannedPlaces())
					{
						boardForCalculating[r + 2][l + 2] = 0;
						boardForCalculating[r + 4][l + 4] = 1;
						if (!judgeBannedPlaces())
						{
							threes++;
							boardForCalculating[r + 4][l + 4] = 0;
						}
					}
					boardForCalculating[r - 1][l - 1] = 0;
					boardForCalculating[r + 2][l + 2] = 0;
					boardForCalculating[r + 4][l + 4] = 0;
				}
			}
		}
	}
	// check antidiag
	for (int r = 3; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 5; l <= BOARDSIZE - 2; l++)
		{
			// _xooox_, at most one '_' is white, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 1, l - 1) && judgeBlack(r + 2, l - 2) && judgeBlank(r - 1, l + 1)
				&& judgeBlank(r + 3, l - 3) && (!judgeWhite(r - 2, l + 2) || !judgeWhite(r + 4, l - 4)))
			{
				boardForCalculating[r - 1][l + 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l + 1] = 0;
					boardForCalculating[r + 3][l - 3] = 1;
					if (!judgeBannedPlaces())
					{
						threes++;
						boardForCalculating[r + 3][l - 3] = 0;
					}
				}
				boardForCalculating[r - 1][l + 1] = 0;
				boardForCalculating[r + 3][l - 3] = 0;
			}
		}
	}
	for (int r = 2; r <= BOARDSIZE - 4; r++)
	{
		for (int l = 4; l <= BOARDSIZE - 2; l++)
		{
			// xooxox or xoxoox, x means blank, o means black
			if (judgeBlack(r, l) && judgeBlack(r + 3, l - 3) && judgeBlank(r - 1, l + 1) && judgeBlank(r + 4, l - 4)
				&& (judgeBlack(r + 1, l - 1) && judgeBlank(r + 2, l - 2)) || (judgeBlank(r + 1, l - 1) && judgeBlack(r + 2, l - 2)))
			{
				boardForCalculating[r - 1][l + 1] = 1;
				if (!judgeBannedPlaces())
				{
					boardForCalculating[r - 1][l + 1] = 0;
					boardForCalculating[r + 2][l - 2] = 1;
					if (!judgeBannedPlaces())
					{
						boardForCalculating[r + 2][l - 2] = 0;
						boardForCalculating[r + 4][l - 4] = 1;
						if (!judgeBannedPlaces())
						{
							threes++;
							boardForCalculating[r + 4][l - 4] = 0;
						}
					}
					boardForCalculating[r - 1][l + 1] = 0;
					boardForCalculating[r + 2][l - 2] = 0;
					boardForCalculating[r + 4][l - 4] = 0;
				}
			}
		}
	}
	return (threes >= 2);
	*/
	// _xooox_, o : black; x : blank; _at least one is blank 
	for (int direc = 0; direc < DIRECTIONS; direc++)
		for (int i = 0; i < 3; i++)
			if ((posInBoard(positionR(r, direc, -2, i), positionL(l, direc, -2, i)) && posInBoard(positionR(r, direc, 3, i), positionL(l, direc, 3, i)))
				|| (posInBoard(positionR(r, direc, -1, i), positionL(l, direc, -1, i)) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
			{
				if (j0(r, l, direc, -1) && j0(r, l, direc, 3) && j1(r, l, direc, 1) && j1(r, l, direc, 2))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, -1), posL(l, direc, -1)) && j0(r, l, direc, 4))
						temp++;
					if (!judgeBannedPlaces(posR(r, direc, 3), posL(l, direc, 3)) && j0(r, l, direc, -2))
						temp++;
					copyBoard();
				}
				if (j0(r, l, direc, -2) && j0(r, l, direc, 2) && j1(r, l, direc, -1) && j1(r, l, direc, 1))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, -2), posL(l, direc, -2)) && j0(r, l, direc, 3))
						temp++;
					if (!judgeBannedPlaces(posR(r, direc, 2), posL(l, direc, 2)) && j0(r, l, direc, -3))
						temp++;
					copyBoard();
				}
				if (j0(r, l, direc, -3) && j0(r, l, direc, 1) && j1(r, l, direc, -2) && j1(r, l, direc, -1))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, -3), posL(l, direc, -3)) && j0(r, l, direc, 2))
						temp++;
					if (!judgeBannedPlaces(posR(r, direc, 1), posL(l, direc, 1)) && j0(r, l, direc, -4))
						temp++;
					copyBoard();
				}
			}
	threes = temp;
	temp = 0;
	// xooxox, x : blank; o : black
	for (int direc = 0; direc < DIRECTIONS * 2; direc++)
		for (int i = 0; i < 4 && i != 3; i++)
			if (posInBoard(positionR(r, direc, -1, i), positionL(l, direc, -1, i) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
			{
				if ((j0(r, l, direc, -1) && j1(r, l, direc, 1) && j0(r, l, direc, 2) && j1(r, l, direc, 3) && j0(r, l, direc, 4)))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, 2), posL(l, direc, 2)))
						temp++;
					copyBoard();
				}
				if ((j0(r, l, direc, -2) && j1(r, l, direc, -1) && j0(r, l, direc, 1) && j1(r, l, direc, 2) && j0(r, l, direc, 3)))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, 1), posL(l, direc, 1)))
						temp++;
					copyBoard();
				}
				if ((j0(r, l, direc, -4) && j1(r, l, direc, -3) && j0(r, l, direc, -2) && j1(r, l, direc, -1) && j0(r, l, direc, 0)))
				{
					boardForCalculating[r][l] = 1;
					if (!judgeBannedPlaces(posR(r, direc, -1), posL(l, direc, -1)))
						temp++;
					copyBoard();
				}
			}
	threes += temp / 2;
	return threes;
}

// to count the number of fours
int judge4(int r, int l)
{
	int fours = 0;
	/*
	int temp1 = 0;		// To temperarily store the color
	int temp2 = 0;		// The same
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			if (judgeBlack(r, l))
			{
				// check horizotal
				{
					// _oooo_, at least one '_' is blank
					if (judgeBlack(r, l + 1) && judgeBlack(r, l + 2) && judgeBlack(r, l + 3)
						&& (judgeBlank(r, l - 1) || judgeBlank(r, l + 4)))
					{
						temp1 = boardForCalculating[r][l - 1];
						boardForCalculating[r][l - 1] = 1;
						if (!judgeBannedPlaces())
						{
							boardForCalculating[r][l - 1] = temp1;
							temp2 = boardForCalculating[r][l + 4];
							boardForCalculating[r][l + 4] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r][l + 4] = temp2;
						}
						boardForCalculating[r][l - 1] = temp1;
					}
					// ooo_o or oo_oo or o_ooo, 'o' is black and '_' is blank
					if (judgeBlack(r, l + 4) && judgeBlack(r, l + 1) && judgeBlack(r, l + 2) && judgeBlank(r, l + 3))
					{
						boardForCalculating[r][l + 3] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r][l + 3] = 0;
					}
					if (judgeBlack(r, l + 4) && judgeBlack(r, l + 1) && judgeBlank(r, l + 2) && judgeBlack(r, l + 3))
					{
						boardForCalculating[r][l + 2] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r][l + 2] = 0;
					}
					if (judgeBlack(r, l + 4) && judgeBlank(r, l + 1) && judgeBlack(r, l + 2) && judgeBlack(r, l + 3))
					{
						boardForCalculating[r][l + 1] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r][l + 1] = 0;
					}
				}
				// check vertical
				{
					// _oooo_, at least one '_' is blank
					if (judgeBlack(r + 1, l) && judgeBlack(r + 2, l) && judgeBlack(r + 3, l)
						&& (judgeBlank(r - 1, l) || judgeBlank(r + 4, l)))
					{
						temp1 = boardForCalculating[r - 1][l];
						boardForCalculating[r - 1][l] = 1;
						if (!judgeBannedPlaces())
						{
							boardForCalculating[r - 1][l] = temp1;
							temp2 = boardForCalculating[r + 4][l];
							boardForCalculating[r + 4][l] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r + 4][l] = temp2;
						}
						boardForCalculating[r - 1][l] = temp1;
					}
					// ooo_o or oo_oo or o_ooo, 'o' is black and '_' is blank
					if (judgeBlack(r + 4, l) && judgeBlack(r + 1, l) && judgeBlack(r + 2, l) && judgeBlank(r + 3, l))
					{
						boardForCalculating[r + 3][l] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 3][l] = 0;
					}
					if (judgeBlack(r + 4, l) && judgeBlack(r + 1, l) && judgeBlank(r + 2, l) && judgeBlack(r + 3, l))
					{
						boardForCalculating[r + 2][l] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 2][l] = 0;
					}
					if (judgeBlack(r + 4, l) && judgeBlank(r + 1, l) && judgeBlack(r + 2, l) && judgeBlack(r + 3, l))
					{
						boardForCalculating[r + 1][l] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 1][l] = 0;
					}
				}
				// check diag
				{
					// _oooo_, at least one '_' is blank
					if (judgeBlack(r + 1, l + 1) && judgeBlack(r + 2, l + 2) && judgeBlack(r + 3, l + 3)
						&& (judgeBlank(r - 1, l - 1) || judgeBlank(r + 4, l + 4)))
					{
						temp1 = boardForCalculating[r - 1][l - 1];
						boardForCalculating[r - 1][l - 1] = 1;
						if (!judgeBannedPlaces())
						{
							boardForCalculating[r - 1][l - 1] = temp1;
							temp2 = boardForCalculating[r + 4][l + 4];
							boardForCalculating[r + 4][l + 4] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r + 4][l + 4] = temp2;
						}
						boardForCalculating[r - 1][l - 1] = temp1;
					}
					// ooo_o or oo_oo or o_ooo, 'o' is black and '_' is blank
					if (judgeBlack(r + 4, l + 4) && judgeBlack(r + 1, l + 1) && judgeBlack(r + 2, l + 2) && judgeBlank(r + 3, l + 3))
					{
						boardForCalculating[r + 3][l + 3] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 3][l + 3] = 0;
					}
					if (judgeBlack(r + 4, l + 4) && judgeBlack(r + 1, l + 1) && judgeBlank(r + 2, l + 2) && judgeBlack(r + 3, l + 3))
					{
						boardForCalculating[r + 2][l + 2] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 2][l + 2] = 0;
					}
					if (judgeBlack(r + 4, l + 4) && judgeBlank(r + 1, l + 1) && judgeBlack(r + 2, l + 2) && judgeBlack(r + 3, l + 3))
					{
						boardForCalculating[r + 1][l + 1] = 1;
						if (!judgeBannedPlaces())
						{
							fours++;
						}
						boardForCalculating[r + 1][l + 1] = 0;
					}
				}
				// check antidiag
				// more check in case of going beyond boundry
				{
					if (l >= 4)
					{
						// _oooo_, at least one '_' is blank
						if (judgeBlack(r + 1, l - 1) && judgeBlack(r + 2, l - 2) && judgeBlack(r + 3, l - 3)
							&& (judgeBlank(r - 1, l + 1) || judgeBlank(r + 4, l - 4)))
						{
							temp1 = boardForCalculating[r - 1][l + 1];
							boardForCalculating[r - 1][l + 1] = 1;
							if (!judgeBannedPlaces())
							{
								boardForCalculating[r - 1][l + 1] = temp1;
								temp2 = boardForCalculating[r + 4][l - 4];
								boardForCalculating[r + 4][l - 4] = 1;
								if (!judgeBannedPlaces())
								{
									fours++;
								}
								boardForCalculating[r + 4][l - 4] = temp2;
							}
							boardForCalculating[r - 1][l + 1] = temp1;
						}
						// ooo_o or oo_oo or o_ooo, 'o' is black and '_' is blank
						if (judgeBlack(r + 4, l - 4) && judgeBlack(r + 1, l - 1) && judgeBlack(r + 2, l - 2) && judgeBlank(r + 3, l - 3))
						{
							boardForCalculating[r + 3][l - 3] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r + 3][l - 3] = 0;
						}
						if (judgeBlack(r + 4, l - 4) && judgeBlack(r + 1, l - 1) && judgeBlank(r + 2, l - 2) && judgeBlack(r + 3, l - 3))
						{
							boardForCalculating[r + 2][l - 2] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r + 2][l - 2] = 0;
						}
						if (judgeBlack(r + 4, l - 4) && judgeBlank(r + 1, l - 1) && judgeBlack(r + 2, l - 2) && judgeBlack(r + 3, l - 3))
						{
							boardForCalculating[r + 1][l - 1] = 1;
							if (!judgeBannedPlaces())
							{
								fours++;
							}
							boardForCalculating[r + 1][l - 1] = 0;
						}
					}
				}
			}
		}
	}
	*/
	// _oooo_; o : black; at least one _ is blank
	for (int direc = 0; direc < DIRECTIONS; direc++)
		for (int i = 0; i < 4; i++)
			if ((posInBoard(positionR(r, direc, -1, i), positionL(l, direc, -1, i)) && posInBoard(positionR(r, direc, 3, i), positionL(l, direc, 3, i)))
				|| (posInBoard(positionR(r, direc, 0, i), positionL(l, direc, 0, i)) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
				if ((!(!j0(r, l, direc, -1) && !j0(r, l, direc, 4)) && j1(r, l, direc, 1) && j1(r, l, direc, 2) && j1(r, l, direc, 3))
					|| (!(!j0(r, l, direc, -2) && !j0(r, l, direc, 3)) && j1(r, l, direc, -1) && j1(r, l, direc, 1) && j1(r, l, direc, 2))
					|| (!(!j0(r, l, direc, -3) && !j0(r, l, direc, 2)) && j1(r, l, direc, -2) && j1(r, l, direc, -1) && j1(r, l, direc, 1))
					|| (!(!j0(r, l, direc, -4) && !j0(r, l, direc, 1)) && j1(r, l, direc, -3) && j1(r, l, direc, -2) && j1(r, l, direc, -1)))
					fours++;
	// ooo_o, o : black; _ : blank
	for (int direc = 0; direc < DIRECTIONS * 2; direc++)
		for (int i = 0; i < 5 && i != 3; i++)
			if ((posInBoard(positionR(r, direc, 0, i), positionL(l, direc, 0, i)) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
				if ((j1(r, l, direc, 1) && j1(r, l, direc, 2) && j0(r, l, direc, 3) && j1(r, l, direc, 4))
					|| (j1(r, l, direc, -1) && j1(r, l, direc, 1) && j0(r, l, direc, 2) && j1(r, l, direc, 3))
					|| (j1(r, l, direc, -2) && j1(r, l, direc, -1) && j0(r, l, direc, 1) && j1(r, l, direc, 2))
					|| (j1(r, l, direc, -4) && j1(r, l, direc, -3) && j1(r, l, direc, -2) && j0(r, l, direc, -1)))
					fours++;
	// oo_oo, o : black; _ : blank
	for (int direc = 0; direc < DIRECTIONS; direc++)
		for (int i = 0; i < 5 && i != 2; i++)
			if ((posInBoard(positionR(r, direc, 0, i), positionL(l, direc, 0, i)) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
				if ((j1(r, l, direc, 1) && j0(r, l, direc, 2) && j1(r, l, direc, 3) && j1(r, l, direc, 4))
					|| (j1(r, l, direc, -1) && j1(r, l, direc, 1) && j0(r, l, direc, 2) && j1(r, l, direc, 3))
					|| (j1(r, l, direc, -3) && j1(r, l, direc, -2) && j0(r, l, direc, -1) && j1(r, l, direc, 1))
					|| (j1(r, l, direc, -4) && j1(r, l, direc, -3) && j0(r, l, direc, -2) && j1(r, l, direc, -1)))
					fours++;
	return fours;
}

// to check if there is more than 6 black in a line
int judgeLong(int r, int l)
{
	/*
	int judge = 0;	// no such circumstances in default -> judge == 1 -> return result = !judge == 0
	int num = 0;
	// check honrizontal
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE - 5; l++)
		{
			for (int i = 0; i < 6; i++)
			{
				num += judgeBlack(r, l + i);
			}
			judge += (num == 6);
			num = 0;
		}
	}
	// check vertical
	for (int r = 1; r <= BOARDSIZE - 5; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			for (int i = 0; i < 6; i++)
			{
				num += judgeBlack(r + i, l);
			}
			judge += (num == 6);
			num = 0;
		}
	}
	// check diag
	for (int r = 1; r <= BOARDSIZE - 5; r++)
	{
		for (int l = 1; l <= BOARDSIZE - 5; l++)
		{
			for (int i = 0; i < 6; i++)
			{
				num += judgeBlack(r + i, l + i);
			}
			judge += (num == 6);
			num = 0;
		}
	}
	// check antidiag
	for (int r = 1; r <= BOARDSIZE - 5; r++)
	{
		for (int l = 6; l <= BOARDSIZE; l++)
		{
			for (int i = 0; i < 6; i++)
			{
				num += judgeBlack(r + i, l - i);
			}
			judge += (num == 6);
			num = 0;
		}
	}
	return judge != 0;
	*/
	int longs = 0;
	for (int direc = 0; direc < DIRECTIONS; direc++)
		for (int i = 0; i < 5; i++)
			if ((posInBoard(positionR(r, direc, 0, i), positionL(l, direc, 0, i)) && posInBoard(positionR(r, direc, 4, i), positionL(l, direc, 4, i))))
				if ((j1(r, l, direc, 1) && j1(r, l, direc, 2) && j1(r, l, direc, 3) && j1(r, l, direc, 4))
					|| (j1(r, l, direc, -1) && j1(r, l, direc, 1) && j1(r, l, direc, 2) && j1(r, l, direc, 3))
					|| (j1(r, l, direc, -2) && j1(r, l, direc, -1) && j1(r, l, direc, 1) && j1(r, l, direc, 2))
					|| (j1(r, l, direc, -3) && j1(r, l, direc, -2) && j1(r, l, direc, -1) && j1(r, l, direc, 1))
					|| (j1(r, l, direc, -4) && j1(r, l, direc, -3) && j1(r, l, direc, -2) && j1(r, l, direc, -1)))
					longs++;
}

int judgeBannedPlaces(int r, int l)
{
	layers++;
	if (layers >= 10)
		return 0;
	if (judge3(r, l) >= 2 || judge4(r, l) >= 2 || judgeLong(r, l) >= 1)
		return 1;
	return 0;
}

void playerPutChess(int color)
{
	int row, line = 0;
	inputPosition();
	row = 10 * input[0] + input[1];
	line = 10 * input[2] + input[3];
	while (board[row][BOARDSIZE - line + 1] != 0 || row < 1 || row > BOARDSIZE || line < 1 || line > BOARDSIZE)
	{
		printf("%d %d", row, line);
		wrongInput();
		row = 10 * input[0] + input[1];
		line = 10 * input[2] + input[3];
	}
	layers = 0;
	{
		copyBoard();
		if (color == 3 && judgeBannedPlaces(row, BOARDSIZE + 1 - line))
		{
			system("cls");
			printf("Player ¡ñ loses due to banned positions!\nPlease enter to go on.\n");
			printf("%d %d %d\n", row, line, judgeBannedPlaces(row, BOARDSIZE + 1 - line));
			endGame();
		}
	}	
	putChess(row, line, color);
	lastPos[0] = row + 'A' - 1;
	lastPos[1] = line;
}