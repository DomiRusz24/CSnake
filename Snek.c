#include "Snek.h"

SnakeGame *snake;

int main() {

  srand(time(NULL));

  snake = malloc(sizeof(SnakeGame));

  snake->sound = false;

  snake->snake = malloc(sizeof(Snake));
  snake->stopped = false;
  snake->board.xSize = 20;
  snake->board.ySize = 20;

  snake->tickDelay = 50;

  snake->snake->direction = UP;
  snake->snake->head = malloc(sizeof(Body));
  snake->snake->tail = malloc(sizeof(Body));
  snake->snake->tail->next = snake->snake->head;

  snake->snake->size = 2;

  snake->snake->tail->vector.x = (snake->board.xSize / 2);
  snake->snake->head->vector.x = (snake->board.xSize / 2);
  snake->snake->tail->vector.y = (snake->board.ySize / 2);
  snake->snake->head->vector.y = ((snake->board.ySize / 2) - 1);

  randomizeApple(&snake->board);

  init(snake);

  while(!snake->stopped) {
    registerKeyPresses(snake);

    snake->tick = snake->tick + 1;

    if (snake->tick == snake->tickDelay) {
      snake->tick = 0;
      tick(snake);
      display(snake);
      snake->sound = false;
    }

    sleep(10);
  }

  end(snake);

}
