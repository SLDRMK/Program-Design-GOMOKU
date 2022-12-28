/* The main procedures. */
#include "board.h"
#include "endGame.h"
#include "menu.h"
#include "game.h"
#include <stdio.h>
#include "meta.h"
#include "ai.h"

main()
{
	// judge3Test();
	// judge4Test();
	// test();
	loadBoard();
	printf("Welcome to play the GOMOKU GAME!\n");
	game();
}