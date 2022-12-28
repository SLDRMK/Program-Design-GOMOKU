/* Fuctions related to the chess board. */

#ifndef BOARD_H_
#define BOARD_H_

void loadBoard();
void reloadBoard();
void copyBoard();
void drawBoard(int computer);
void printBoardElement(int r, int l, int e);
void putChess(int r, int l, int color);
void inputPosition();
void wrongInput();

#endif