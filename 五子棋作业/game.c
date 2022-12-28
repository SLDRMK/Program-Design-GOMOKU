/* Functioons related to the game process. */
#include "game.h"
#include "endGame.h"
#include "board.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "ai.h"
#include "meta.h"

void cleanStdin()
{
	//	To clean the std stream.
	char c = 'a';
	while ((c = getchar()) != EOF && c != '\n');
}

void game()
{
	int choice = menu();
	if (choice == 1)
		modePVP();
	else if (choice == 2)
		modePVC();
	else if (choice == 'q')
		exitGame();
	else
	{
		system("cls");
		cleanStdin();
		printf("Wrong choice, Please enter again!\n");
		game();
	}		
}

void exitGame()
{
	exit(0);
}

void endGame()
{
	cleanStdin();
	char choice= 'y';
	printf("Do you want to play again (\"y\" means yes and \"q\" to quit):");
	int err = scanf_s("%c", &choice, 2);
	if (choice == 'y')
	{
		printf("Welcome to play the GOMOKU GAME!\n");
		system("cls");
		game();
	}
	else if (choice == 'q')
		exitGame();
	else
	{
		system("cls");
		printf("Wrong choice! Please enter again!");
		endGame();
	}
}

void modePVP()
{
	//	player vs player
	while (!judgeGameEnding())
	{
		drawBoard(0);
		printf("Player ¡ñ putting chess (For example: A1):");
		playerPutChess(3);
		copyBoard();
		if (judgeGameEnding())
		{
			system("cls");
			printf("Player ¡ñ wins!\n");
			endGame();
		}
		else if (judgeBoardGoingFull()) // The board can only be full when the player ¡ñ puts chess.
		{
			system("cls");
			printf("Nowhere to put chess. Game ends.");
			endGame();
		}
		else
		{
			drawBoard(0);
			printf("Player ¡ð putting chess (For example: A1):");
			playerPutChess(4);
			if (judgeGameEnding())
			{
				system("cls");
				printf("Player ¡ð wins!\n");
				endGame();
			}
		}
	}
}

void modePVC()
{
	// player vs computer
	cleanStdin();
	int choice;
	while ((choice = chooseMode()) == -1)
		cleanStdin();
	if (choice == 1)
	{
		while (!judgeGameEnding())
		{
			drawBoard(0);
			printf("Player ¡ñ putting chess (For example: A1):");
			playerPutChess(3);
			copyBoard();
			if (judgeGameEnding())
			{
				system("cls");
				printf("Player ¡ñ wins!\n");
				endGame();
			}
			else if (judgeBoardGoingFull()) // The board can only be full when the player ¡ñ puts chess.
			{
				system("cls");
				printf("Nowhere to put chess. Game ends.");
				endGame();
			}
			else
			{
				drawBoard(1);
				// printf("Player ¡ð putting chess (For example: A1):");
				aiPutW();
				if (judgeGameEnding())
				{
					system("cls");
					printf("Player ¡ð wins!\n");
					endGame();
				}
			}
		}
	}
	else
	{
		while (!judgeGameEnding())
		{
			drawBoard(1);
			// printf("Player ¡ñ putting chess (For example: A1):");
			aiPutB();
			copyBoard();
			if (judgeGameEnding())
			{
				system("cls");
				printf("Player ¡ñ wins!\n");
				endGame();
			}
			else if (judgeBoardGoingFull()) // The board can only be full when the player ¡ñ puts chess.
			{
				system("cls");
				printf("Nowhere to put chess. Game ends.");
				endGame();
			}
			else
			{
				drawBoard(0);
				printf("Player ¡ð putting chess (For example: A1):");
				playerPutChess(4);
				if (judgeGameEnding())
				{
					system("cls");
					printf("Player ¡ð wins!\n");
					endGame();
				}
			}
		}
	}

}