#include "Point.h"
#include <time.h>

typedef struct Board Board;

struct Board {
  unsigned int xSize, ySize;
  unsigned int amount;
  Point *apples;
};

void randomizeApple(Board *board);




