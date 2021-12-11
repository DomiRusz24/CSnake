#include <stdbool.h>
#include <stdio.h>
#include "Snake.h"
#include "Board.h"

typedef struct SnakeGame SnakeGame;

struct SnakeGame {
  bool stopped;
  bool sound;
  unsigned long int tick;
  unsigned int tickDelay;
  Snake *snake;
  Board board;
};


void tick(SnakeGame *gamed);

