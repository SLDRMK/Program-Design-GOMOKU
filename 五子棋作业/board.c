/* Fuctions related to the chess board. */
//	r refers to horizon row and l refers to vertical line
#include "game.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include "meta.h"

void loadBoard()
{
	// define the boundary
	for (int r = 0; r < BOARDWIDTH; r++)
	{
		for (int l = 0; l < BOARDWIDTH; l++)
		{
			board[l][r] = -1;
		}
	}
	// init the board
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			board[l][r] = 0;
		}
	}
	{
		directions[0][0] = 0;
		directions[0][1] = 1;
		directions[1][0] = 1;
		directions[1][1] = 0;
		directions[2][0] = 1;
		directions[2][1] = 1;
		directions[3][0] = 1;
		directions[3][1] = -1;
		directions[4][0] = 0;
		directions[4][1] = -1;
		directions[5][0] = -1;
		directions[5][1] = 0;
		directions[6][0] = -1;
		directions[6][1] = -1;
		directions[7][0] = 1;
		directions[7][1] = -1;
	}
	int r = 0;
	{
		scoreTypes1[r][0] = 50;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 0;
		scoreTypes1[r][5] = 0;
	}
	r = 1;
	{
		scoreTypes1[r][0] = 50;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 0;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 0;
	}
	r = 2;
	{
		scoreTypes1[r][0] = 200;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 0;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 0;
	}
	r = 3;
	{
		scoreTypes1[r][0] = 200;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 0;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 4;
	{
		scoreTypes1[r][0] = 500;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 0;
		scoreTypes1[r][5] = 0;
	}
	r = 5;
	{
		scoreTypes1[r][0] = 500;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 0;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 6;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 0;
	}
	r = 7;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 0;
		scoreTypes1[r][5] = 1;
	}
	r = 8;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 0;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 9;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 0;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 10;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 0;
	}
	r = 11;
	{
		scoreTypes1[r][0] = 5000;
		scoreTypes1[r][1] = 0;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 12;
	{
		scoreTypes1[r][0] = 100000000;
		scoreTypes1[r][1] = 1;
		scoreTypes1[r][2] = 1;
		scoreTypes1[r][3] = 1;
		scoreTypes1[r][4] = 1;
		scoreTypes1[r][5] = 1;
	}
	r = 0;
	{
		scoreTypes2[r][0] = 5000;
		scoreTypes2[r][1] = 0;
		scoreTypes2[r][2] = 1;
		scoreTypes2[r][3] = 0;
		scoreTypes2[r][4] = 1;
		scoreTypes2[r][5] = 1;
		scoreTypes2[r][6] = 0;
	}
	r = 1;
	{
		scoreTypes2[r][0] = 5000;
		scoreTypes2[r][1] = 0;
		scoreTypes2[r][2] = 1;
		scoreTypes2[r][3] = 1;
		scoreTypes2[r][4] = 0;
		scoreTypes2[r][5] = 1;
		scoreTypes2[r][6] = 0;
	}
	r = 2;
	{
		scoreTypes2[r][0] = 50000;
		scoreTypes2[r][1] = 0;
		scoreTypes2[r][2] = 1;
		scoreTypes2[r][3] = 1;
		scoreTypes2[r][4] = 1;
		scoreTypes2[r][5] = 1;
		scoreTypes2[r][6] = 0;
	}
	lastPos[0] = lastPos[1] = 0;
}

void reloadBoard()
{
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			if (board[r][l] == 3)
				board[r][l] = 1;
			else if (board[r][l] == 4)
				board[r][l] = 2;
		}
	}
}

void copyBoard()
{
	for (int r = 0; r < BOARDWIDTH; r++)
		for (int l = 0; l < BOARDWIDTH; l++)
			boardForCalculating[r][l] = board[r][l];
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			if (boardForCalculating[r][l] == 3)
				boardForCalculating[r][l] = 1;
			else if (boardForCalculating[r][l] == 4)
				boardForCalculating[r][l] = 2;
		}
	}
}

void drawBoard(int computer)
{
	system("cls");
	printf("&&&  GOMOKU GAME  &&&\nProduced by SLDRMK\n\n");
	int lastRow = 0;
	int lastLine = 0;
	for (int r = 1; r <= BOARDSIZE; r++)
	{
		printf("%2d  ", BOARDSIZE + 1 - r);
		for (int l = 1; l <= BOARDSIZE; l++)
		{
			printBoardElement(r, l, board[l][r]);
		}
		printf("\n");
	}
	printf("    A B C D E F G H I J K L M N O\n\n");
	if (lastPos[0] != 0)
		printf("Last Position: %c%d\n", lastPos[0], lastPos[1]);
	if (computer == 0)
		printf("Please choose the position to put your chess (row:letter+space+line:number) !\n");
	else
		printf("Points calcululated: %d / 225\nTrim times: %d", calProcess, trim);
	reloadBoard();
}

void printBoardElement(int r, int l, int e)
{
	switch (e)
	{
	case 1:
		printf("¡ñ");
		break;
	case 2:
		printf("¡ð");
		break;
	case 3:
		printf("¡ø");
		break;
	case 4:
		printf("¡÷");
		break;
	case 0:
		if (r == 1)
		{
			if (l == 1)
			{
				printf("©³");
			}
			else if (l == BOARDSIZE)
			{
				printf("©·");
			}
			else
			{
				printf("©Ó");
			}
		}
		else if (r == BOARDSIZE)
		{
			if (l == 1)
			{
				printf("©»");
			}
			else if (l == BOARDSIZE)
			{
				printf("©¿");
			}
			else
			{
				printf("©Û");
			}
		}
		else
		{
			if (l == 1)
			{
				printf("©Ä");
			}
			else if (l == BOARDSIZE)
			{
				printf("©Ì");
			}
			else
			{
				printf("©à");

			}
		}
		break;
	}
}

void putChess(int r, int l, int color)
{
	board[r][BOARDSIZE + 1 - l] = color;
}

void inputPosition()
{
	int temp = getchar();
	temp = getchar();
	int times = 0;
	if (temp >= 'A' && temp <= 'O')
	{
		temp = temp - 'A' + 1;
		input[1] = temp % 10;
		input[0] = temp / 10;
		temp = getchar();
		while (temp == ' ' || temp == '\t')
			temp = getchar();
		if (temp == '0')
		{
			input[2] = 0;
			temp = getchar();
			if (temp >= '1' && temp <= '9')
				input[3] = temp - '0';
			wrongInput();
		}
		else if (temp == '1')
		{
			temp = getchar();
			if (temp == '\n')
			{
				input[2] = 0;
				input[3] = 1;
			}
			else if (temp >= '0' && temp <= '5')
			{
				input[2] = 1;
				input[3] = temp - '0';
			}
			else
				wrongInput();
		}
		else if (temp >= '1' && temp <= '9')
		{
			input[2] = 0;
			input[3] = temp - '0';
		}
		else
			wrongInput();
	}
	else if (temp >= 'a' && temp <= 'o')
	{
		temp = temp - 'a' + 1;
		input[1] = temp % 10;
		input[0] = temp / 10;
		temp = getchar();
		while (temp == ' ' || temp == '\t')
			temp = getchar();
		if (temp == '0')
		{
			input[2] = 0;
			temp = getchar();
			if (temp >= '1' && temp <= '9')
				input[3] = temp - '0';
			else
				wrongInput();
		}
		else if (temp == '1')
		{
			temp = getchar();
			if (temp == '\n')
			{
				input[2] = 0;
				input[3] = 1;
			}
			else if (temp >= '0' && temp <= '5')
			{
				input[2] = 1;
				input[3] = temp - '0';
			}
			else
				wrongInput();
		}
		else if (temp >= '1' && temp <= '9')
		{
			input[2] = 0;
			input[3] = temp - '0';
		}
		else
			wrongInput();
	}
	else
	{
		if (temp == '0')
		{
			input[2] = 0;
			temp = getchar();
			if (temp >= '1' && temp <= '9')
				input[3] = temp - '0';
			else
				wrongInput();
		}
		else if (temp == '1')
		{
			temp = getchar();
			if (temp == '\n')
			{
				input[2] = 0;
				input[3] = 1;
			}
			else if (temp >= '0' && temp <= '5')
			{
				input[2] = 1;
				input[3] = temp - '0';
			}
			else
				wrongInput();
		}
		else if (temp >= '1' && temp <= '9')
		{
			input[2] = 0;
			input[3] = temp - '0';
		}
		else
			wrongInput();
		temp = getchar();
		while (temp == ' ' || temp == '\t')
			temp = getchar();
		if (temp >= 'A' && temp <= 'O')
		{
			temp = temp - 'A' + 1;
			input[1] = temp % 10;
			input[0] = temp / 10;
		}
		else
			wrongInput();
	}
	/* {
		while ((temp = getchar()) != '\n' && times <= 2)
		{
			times++;
			if (temp == ' ' || temp == '\t')
			{
				times--;
				continue;
			}
			else if (temp == '0' || temp == "1")
			{
				input[2] = temp - '0';
				temp = getchar();
				if (temp == '\n' || temp == ' ' || temp == '\t' && temp)

					if (input[2] == 0 && temp >= '1' && temp <= '9' || (input[2] == 1 && temp >= '0' && temp <= '5'))
						input[3] = temp - '0';
					else if (input[2] == 1 && temp >= 'A' && temp <= 'O')
					{
						times += 2;
						input[2] = 0;
						input[3] = 1;
						temp = temp - 'A' + 1;
						input[1] = temp % 10;
						input[0] = temp / 10;
					}
					else if (input[2] == 1 && temp >= 'a' && temp <= 'o')
					{
						times += 2;
						temp = temp - 'a' + 1;
						input[1] = temp % 10;
						input[0] = temp / 10;
					}
					else
						wrongInput();
			}
			else if (temp >= '2' && temp <= '9')
			{
				input[2] = 0;
				input[3] = temp - '2' + 2;
			}
			else if (temp >= 'A' && temp <= 'O')
			{
				temp = temp - 'A' + 1;
				input[1] = temp % 10;
				input[0] = temp / 10;

			}
			else if (temp >= 'a' && temp <= 'o')
			{
				temp = temp - 'a' + 1;
				input[1] = temp % 10;
				input[0] = temp / 10;
			}
		}
	}*/
}

void wrongInput()
{
	printf("You cannot put a chess here.\nPlease choose a position again (For example: A1):");
	// cleanStdin();
	inputPosition();
}