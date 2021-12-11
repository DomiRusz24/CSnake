#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "display/DisplayLinux.h"

#ifdef _WINDOWS
#include <windows.h>
#define sleep(x) Sleep((x))
#else
#include <unistd.h>
#define sleep(x) usleep((x)*1000)
#endif
