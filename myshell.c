#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#define pMax _MAX_PATH
#else
#include <unistd.h>
#define pMax PATH_MAX
#endif

#include "myshell.h"
#include "utility.c"

#define BUFFER_LEN 256

int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };

    char currDir[pMax];

    getcwd(currDir, sizeof(currDir));

    printf("%s$ ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){

        printf("%s$ ", currDir);
        
        if(strcmp(command, "quit")){

            break;
        }

    }
}