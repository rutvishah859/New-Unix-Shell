#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include "myshell.h"

int numBuiltIns(){
    return sizeof(builtin) / sizeof(char *);
}

int dir(char **args){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char directory[pMax] = ""; 

    if(d){
        while ((dir = readdir(d)) != NULL) {
            sprintf(directory, "%s\n%s", directory, dir->d_name);	
        }
        closedir(d);
    }
    for (int i = 1; i < 100; i++){
		if (args[i] == NULL){
            printf("%s\n", directory);
            break;
        }
        if (args[i+1] == NULL) {
			printf("Error: expected arg after %s \n", args[i]); 
            return;
		}
		if ((strcmp(args[i], ">") == 0)){
			FILE *fptr = fopen(args[i+1],"w");
            fprintf(fptr,"%s",directory);
            fclose(fptr);
            break;
		}
        else if (strcmp(args[i], ">>") == 0){
            FILE *fptr = fopen(args[i+1],"a");
            fprintf(fptr,"%s",directory);
            fclose(fptr);
            break;
        }
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


// read and execute the commands in the given file
void myshell(char **filename) {
	int bufferLength = 255;
	char buffer[bufferLength];
	char str_arr[255];
	char ** args;

	FILE *fptr;
	fptr = fopen(filename[1], "r");

	if (fptr == NULL) {
		printf("Couldn't open file\n");
	}
    
	while (fgets(buffer, bufferLength, fptr) != NULL) {
		args = splitComm(buffer);
		execute(args);
		free(args);
    }
}

// execute inputted command
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

// splits command at space to get each token of the command
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
    char **args;
    

    getcwd(currDir, pMax);
    printf("%s$ ", currDir);
    while (fgets(command, BUFFER_LEN, stdin) != NULL){
        if(strcmp(command, "quit\n") == 0){
            break;
        }
        args = splitComm(command);
        execute(args);
        free(args);

        printf("%s$ ", currDir);
    }
}
