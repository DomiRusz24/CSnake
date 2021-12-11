#include "Point.h"


typedef struct Body Body;

struct Body {
  Point vector;
  Body *next;
};


