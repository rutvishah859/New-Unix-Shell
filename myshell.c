#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <dirent.h>

#ifdef _WIN32
#include <io.h>
#define pMax _MAX_PATH
#else
#include <unistd.h>
#define pMax FILENAME_MAX
#endif

#include "myshell.h"
#include "utility.c"

#define BUFFER_LEN 256
#define DELIM " \t\r\n\a"

char currDir[pMax];

int cd(char **args);
int dir();

char *builtin[] = {

    "cd",
    "dir"
};

int (*builtinFunc[]) (char **) = {
    &cd,
    &dir
};

int numBuiltIns(){
    return sizeof(builtin) / sizeof(char *);
}

int dir(){

    DIR *d;

    struct dirent *dir;

    d = opendir(".");

    if(d){
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return(0);
}

int cd(char **args){

    if (args[1] == NULL){
        fprintf(stderr, "expected argument to \"cd\"\n");
    }else {
        if(chdir(args[1]) != 0){
            perror("shell");
        }else{
            getcwd(currDir, pMax);
        }
    }

    return 1;
}

int execute(char **args){

    if(args[0] == NULL){
        return 1;
    }

    for (int i = 0; i < numBuiltIns(); i++){
        
        if(strcmp(args[0], builtin[i]) == 0){
            return (*builtinFunc[i])(args);
        }
    }

    return 1;
    
}

char **splitComm(char *command){

    int bufsize = BUFFER_LEN, pos = 0;

    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens){
         fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, DELIM);
  while (token != NULL) {
    tokens[pos] = token;
    pos++;

    if (pos >= bufsize) {
      bufsize += BUFFER_LEN;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, DELIM);
  }
  tokens[pos] = NULL;
  return tokens;
}


int main(int argc, char *argv[]) {

    char command[BUFFER_LEN] = { 0 };

    char currDir[pMax];

    char **args;
    

    int execFlag = 0;

    getcwd(currDir, pMax);
    printf("%s$ ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){

        char *parsedArgs[pMax];

        if(strcmp(command, "quit\n") == 0){
            break;
        }

        args = splitComm(command);

        execute(args);

        free(args);

        printf("%s$ ", currDir);
        
        

    }
}


