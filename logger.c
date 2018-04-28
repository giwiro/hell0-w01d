#include <stdio.h>
#include "logger.h"

void printError(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

void printMsg(char *tag, char *msg) {
    fprintf(stdout, "[%s]: %s\n", tag, msg);
}
