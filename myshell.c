#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include "myshell.h"
#include "utility.c"

#define BUFFER_LEN 256

int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };

    char currDir[_MAX_PATH];

    getcwd(currDir, sizeof(currDir));

    printf("%s: ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){

        printf("%s: ", currDir);

    }
}