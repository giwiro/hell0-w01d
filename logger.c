#include <stdio.h>
#include "logger.h"

void printError(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

