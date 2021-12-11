#include "Board.h"
#include "Point.h"

void randomizeApple(Board *board) {
  board->amount = 1;

  if (board->amount == 1) {
    board->apples = malloc(sizeof(Point));
  }

  Point p;

  int x = rand() % board->xSize;
  int y = rand() % board->ySize;

  p.x = x;
  p.y = y;

  board->apples[0] = p;
}
