#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include "myshell.h"

// returns the number of build in functions
int numBuiltIns(){
    return sizeof(builtin) / sizeof(char *);
}

// prints all the contents of the directory
// if there is a stdout redirection then that output is written to the file name passed
int dir(char **args){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char directory[pMax] = ""; 

    if(d){
        // concat name of each item in direcotry into directory string var
        while ((dir = readdir(d)) != NULL) {
            sprintf(directory, "%s\n%s", directory, dir->d_name);	
        }
        closedir(d);
    }
    // if there is stdout redirection (> or >>) then write the direcotry content into file else print to shell
    for (int i = 1; i < 100; i++){
        // if there is no redirection, print to shell
		if (args[i] == NULL){
            printf("%s\n", directory);
            break;
        }
        // if there is arg after a redirection token (> and >>) print error
        if (args[i+1] == NULL) {
			printf("Error: expected arg after %s \n", args[i]); 
            return;
		}
        // if > redirection open file with w (write) permission (create file if not created, otherwise overwrite content of file)
		if ((strcmp(args[i], ">") == 0)){
			FILE *fptr = fopen(args[i+1],"w");
            fprintf(fptr,"%s",directory);
            fclose(fptr);
            break;
		}
        // if >> redirection open file with a (append) permission (create file if not created, otherwise append content of file)
        else if (strcmp(args[i], ">>") == 0){
            FILE *fptr = fopen(args[i+1],"a");
            fprintf(fptr,"%s",directory);
            fclose(fptr);
            break;
        }
	}
    return(0);
}

// function called when cd command is run (change directory)
int cd(char **args){
    // if no command after cd then print error (expected arg)
    if (args[1] == NULL){
        fprintf(stderr, "expected argument to \"cd\"\n");
    // otherwise change directory according to current direcotry
    // e.g.) cd .. will take you into the parent directory of current directory
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

    // open given arg file and read the file to extract the commands to run
	FILE *fptr;
	fptr = fopen(filename[1], "r");

    // file error
	if (fptr == NULL) {
		printf("Couldn't open file\n");
	}

    // while there are lines in the file keep reading each line and run each command    
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
        // according to input, if it's in the build in commands dictionary run the associated funtion with all the command args from shell input
        if(strcmp(args[0], builtin[i]) == 0){
            return (*builtinFunc[i])(args);
        }
    }
    return launch(args);
}

// creating child process to run commands
int launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
        perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
        wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// Creating array from input command by splitting it with the delimeters defined in DELIM
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
  // return all the tokens from the command input from shell
  return tokens;
}


int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };
    char **args;
    
    getcwd(currDir, pMax); // get current path to directory 
    printf("%s$ ", currDir); // print current directory
    // get shell input until command doesn't equal quit
    while (fgets(command, BUFFER_LEN, stdin) != NULL){
        // if command is quit exit the shell
        if(strcmp(command, "quit\n") == 0){
            break;
        }
        // get all the arguments (split by space) from the command
        args = splitComm(command);
        // execute the command
        execute(args);
        free(args);

        printf("%s$ ", currDir);
    }
}
