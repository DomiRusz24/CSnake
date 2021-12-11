#include "Snake.h"
#include <curses.h>


void appendSnake(Snake *snake, Point location, bool extend) {
  if (!extend) {
    Body* newTail = snake->tail->next;
    free(snake->tail);
    snake->tail = newTail;
  } else {
    snake->size = snake->size + 1;
  }
  Body* oldHead = snake->head;
  Body* newHead = malloc(sizeof(Body));
  newHead->vector = location;
  snake->head = newHead;
  oldHead->next = newHead;
}

void doTick(Snake *snake, bool extend) {
  Point location;
  location.x = snake->head->vector.x + directionToVector(snake->direction).x;
  location.y = snake->head->vector.y + directionToVector(snake->direction).y;

  appendSnake(snake, location, extend);
}

void deconstructSnake(Snake *snake) {
  Body* current = snake->tail;
  Body* next;

  while(current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }

  free(snake);
}

void setDirection(Snake *snake, Direction dir) {
  if (snake->direction == UP && dir == DOWN) return;
  if (snake->direction == DOWN && dir == UP) return;
  if (snake->direction == LEFT && dir == RIGHT) return;
  if (snake->direction == RIGHT && dir == LEFT) return;
  snake->direction = dir;
}
