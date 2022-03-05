#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#define pMax _MAX_PATH
#else
#include <unistd.h>
<<<<<<< HEAD
#define pMax FILENAME_MAX
=======
#define pMax FILENAME_MAX 
>>>>>>> 94a70b6a250cb60da4414d27dd5403a87c52f8a9
#endif

#include "myshell.h"
#include "utility.c"

#define BUFFER_LEN 256

void parseComm(char *input){

    

}

int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };

    char currDir[pMax];

    getcwd(currDir, pMax);
    printf("%s$ ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){

        if(strcmp(command, "quit\n") == 0){
            break;
        }

        printf("%s$ ", currDir);

        char *tokenizedComm;
        parseComm(command);

        


        
        

    }
}


