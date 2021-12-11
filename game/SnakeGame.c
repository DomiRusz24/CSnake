#include "SnakeGame.h"

void tick(SnakeGame *game) {

  if (game->snake->head->vector.x > game->board.xSize - 1 ||
      game->snake->head->vector.y > game->board.ySize - 1 ||
      game->snake->head->vector.y < 0 ||
      game->snake->head->vector.x < 0) {
    game->stopped = true;
  } else {
    if (game->snake->head->vector.x == game->board.apples[0].x && game->snake->head->vector.y == game->board.apples[0].y) {
      game->sound = true;
      doTick(game->snake, true);
      randomizeApple(&game->board);
    } else {

      Body *current = game->snake->tail;

      while (current != game->snake->head) {
        if (game->snake->head->vector.x == current->vector.x && game->snake->head->vector.y == current->vector.y) {
          game->stopped = true;
          break;
        }
        current = current->next;
      }

      doTick(game->snake, false);
    }
  }
}
