#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void environ() {
    // be able to support piping
    system("printenv");
}

void callEcho(char *s) {
    system(s);
}

void pause() {
    system("read -p 'Press [Enter] key to start backup...' enter");
}