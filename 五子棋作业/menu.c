/* Functions related to drawing the menu. */
#include "board.h"
#include "endGame.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "meta.h"

int menu()
{
	int choice = 0;
	printMenu();
	printf("Please enter the number to choose the game mode that you want to play (\"q\" to quit):");
	int err = scanf_s("%d", &choice, 2);
	return choice;
}

void printMenu()
{
	printf("1. Player vs Player.\n");
	printf("2. Player vs Computer.\n");
}

int chooseMode()
{
	system("cls");
	char choice = 0;
	printf("Please enter the color that you want to play \n(\"b\" for black to play first, or \"w\" for white to play secondly):");
	int err = scanf_s("%c", &choice, 1);
	if (choice == 'b' || choice == 'B')
		return 1;
	if (choice == 'w' || choice == 'W')
		return 2;
	return -1;
}