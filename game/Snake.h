#include <stdbool.h>
#include <stdlib.h>
#include "Body.h"



typedef enum {
  UP,
  LEFT,
  RIGHT,
  DOWN
} Direction;

typedef struct Snake Snake;

struct Snake {
  int size;
  Direction direction;
  Body *head;
  Body *tail;
};

static Point directionToVector(Direction dir) {
  Point p;
  p.x = 0;
  p.y = 0;
  switch(dir) {
  case UP: {
    p.y = -1;
    break;
  }
  case DOWN: {
    p.y = 1;
    break;
  }
  case LEFT: {
    p.x = -1;
    break;
  }
  case RIGHT: {
    p.x = 1;
    break;
  }
  }

  return p;
}

static char directionToChar(Direction dir) {
  switch (dir) {
  case UP: {
    return '^';
  }
  case DOWN: {
    return 'v';
  }
  case LEFT: {
    return '<';
  }
  case RIGHT: {
    return '>';
  }
  }
}

void setDirection(Snake *snake, Direction dir);

void appendSnake(Snake *snake, Point location, bool extend);

void doTick(Snake *snake, bool extend);

void deconstructSnake(Snake *snake);




