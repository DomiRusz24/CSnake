#include "DisplayLinux.h"
#include <curses.h>

int numPlaces(int n);
void displayBorder(int x1, int y1, int x2, int y2);
void fill(int x1, int y1, int x2, int y2);

void displayPoints(SnakeGame *game) {
  attron(COLOR_PAIR(1));
  fill((game->board.xSize * 2) + 3,
       3,
       (game->board.xSize * 2) + 14 + numPlaces(game->snake->size),
       7);
  attroff(COLOR_PAIR(1));
  attron(COLOR_PAIR(4));
  displayBorder((game->board.xSize * 2) + 3,
                3,
                (game->board.xSize * 2) + 14 + numPlaces(game->snake->size),
                7);
  mvprintw(5, (game->board.xSize * 2) + 5, "Points: %u", game->snake->size - 2);
  attroff(COLOR_PAIR(4));
}

void display(SnakeGame *game) {

  attron(COLOR_PAIR(1));
  fill(1, 1, (2 * game->board.xSize), game->board.ySize);
  attroff(COLOR_PAIR(1));

  attron(COLOR_PAIR(3));
  mvprintw(game->board.apples[0].y + 1, (game->board.apples[0].x * 2) + 1, "■");
  attroff(COLOR_PAIR(3));

  Body *current = game->snake->tail;

  attron(COLOR_PAIR(2));
  mvprintw(game->snake->head->vector.y + 1, (game->snake->head->vector.x * 2) + 1, "%c", directionToChar(game->snake->direction));
  while (current != game->snake->head) {
    mvprintw(current->vector.y + 1, (current->vector.x * 2) + 1, "o");
    current = current->next;
  }
  attroff(COLOR_PAIR(2));

  if (game->sound) {
    beep();
  }

  displayPoints(game);

  refresh();
}

void end(SnakeGame *game) {
  endwin();

  printf("\n\n\033[1;35m+-------------+\n");
  printf("\033[1;37m  Game over!\n");
  printf("\033[1;37m   Score: %u\n", game->snake->size - 2);
  printf("\033[1;35m+-------------+\n\n");
}

void init(SnakeGame *game) {
  setlocale(LC_ALL, "");
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
  nodelay(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(2, COLOR_GREEN, COLOR_BLUE);
  init_pair(3, COLOR_RED, COLOR_BLUE);
  init_pair(4, COLOR_WHITE, COLOR_BLUE);

  attron(COLOR_PAIR(4));

  displayBorder(0, 0, (game->board.xSize * 2) + 1, (game->board.ySize) + 1);

  attroff(COLOR_PAIR(4));

  display(game);
}

void registerKeyPresses(SnakeGame *game) {
  int ch = getch();

  if (ch == ERR) return;

  switch (ch) {
  case KEY_UP: {
    setDirection(game->snake, UP);
    break;
  }
  case KEY_DOWN: {
    setDirection(game->snake, DOWN);
    break;
  }
  case KEY_LEFT: {
    setDirection(game->snake, LEFT);
    break;
  }
  case KEY_RIGHT: {
    setDirection(game->snake, RIGHT);
    break;
  }
  case 27: {
    game->stopped = true;
    break;
  }
  }
}

void displayBorder(int x1, int y1, int x2, int y2) {
  mvprintw(y1, x1, "╔");
  mvprintw(y2, x1, "╚");
  mvprintw(y1, x2, "╗");
  mvprintw(y2, x2, "╝");

  for (int i = (x1 + 1); i < x2; i++) {
    mvprintw(y1, i, "═");
    mvprintw(y2, i, "═");
  }

  for (int i = (y1 + 1); i < y2; i++) {
    mvprintw(i, x1, "║");
    mvprintw(i, x2, "║");
  }
}

void fill(int x1, int y1, int x2, int y2) {
  for (int y = y1; y <= y2; y++) {
    for (int x = x1; x <= x2; x++) {
      mvprintw((y), (x), "█");
    }
  }
}

int numPlaces(int n) {
  if (n == 0)
    return 1;
  return floor(log10(abs(n))) + 1;
}
