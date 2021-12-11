#include "DisplayLinux.h"
#include <curses.h>

void display(SnakeGame *game) {
  attron(COLOR_PAIR(1));
  for (int y = 0; y < game->board.ySize; y++) {
    for (int x = 0; x < game->board.xSize; x++) {
      mvprintw((y + 1), (x + 1), "█");
    }
  }
  attroff(COLOR_PAIR(1));

  attron(COLOR_PAIR(3));
  mvprintw(game->board.apples[0].y + 1, game->board.apples[0].x + 1, "x");
  attroff(COLOR_PAIR(3));

  Body *current = game->snake->tail;

  attron(COLOR_PAIR(2));
  while (current != NULL) {
    mvprintw(current->vector.y + 1, current->vector.x + 1, "o");
    current = current->next;
  }
  attroff(COLOR_PAIR(2));

  refresh();
}

void end(SnakeGame *game) {
  endwin();
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
  init_pair(2, COLOR_GREEN, COLOR_BLUE);
  init_pair(3, COLOR_RED, COLOR_BLUE);

  mvprintw(0, 0, "╔");
  mvprintw(game->board.ySize + 1, 0, "╚");
  mvprintw(0, game->board.xSize + 1, "╗");
  mvprintw(game->board.ySize + 1, game->board.xSize + 1, "╝");

  for (int i = 1; i <= game->board.xSize; i++) {
    mvprintw(0, i, "═");
  }

  for (int i = 1; i <= game->board.xSize; i++) {
    mvprintw(game->board.ySize + 1, i, "═");
  }

  for (int i = 1; i <= game->board.ySize; i++) {
    mvprintw(i, 0, "║");
  }

  for (int i = 1; i <= game->board.ySize; i++) {
    mvprintw(i, game->board.xSize + 1, "║");
  }

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
