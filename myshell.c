#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#define pMax _MAX_PATH
#else
#include <unistd.h>
#define pMax FILENAME_MAX
#endif

#include "myshell.h"
// #include "utility.c"

#define BUFFER_LEN 256

char* strsep(char** stringp, const char* delim)
{
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}

void parseComm(char* str, char** parsed){
    for (int i = 0; i < 100; i++){
        parsed[i] = strsep(&str, " ");

        if(parsed[i] == NULL){
            break;
        }

        if(strlen(parsed[i]) == 0){
            i--;
        }
    }
}

int processCommand(char* str, char** parsed){


    parseComm(str, parsed);

    return 0;

}

int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };
    char currDir[pMax];
    char *parsedArgs[pMax];

    getcwd(currDir, pMax);
    printf("%s$ ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){
        if(strcmp(command, "quit\n") == 0){
            break;
        }

        // paese the input command to get all the tokens
        parseComm(command, parsedArgs);
        // print path to current directory 
        printf("%s$ ", currDir);
        // if the command is 'clr' clear the terminal 
        if (strncmp(parsedArgs[0], "clr", 3) == 0) {
            clr();
        }  
        // if the command is 'environ' list all the environ strings in the terminal
        else if (strncmp(parsedArgs[0], "environ", 7) == 0) {
            environ();
        }
        // if the command is 'echo' print the provided string to the terminal 
        else if (strncmp(parsedArgs[0], "echo", 4) == 0)
        {
            sprintf(parsedArgs[0], "%s %s", parsedArgs[0], parsedArgs[1]);
            callEcho(parsedArgs[0]);
        }
        // if the command is 'pause' pause terminal input until Enter is pressed 
        else if (strncmp(parsedArgs[0], "pause", 5) == 0) {
            pauseEnter();
        }

    }
}


