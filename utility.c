#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

// function that prints all environment variables in the shell
void environ(char **args) {
	char call[50] = "printenv";
	for (int i = 1; i < 100; i++){
		if (args[i] == NULL){
            break;
        }
		// checks for the occurrence of each redirector
		if ((strcmp(args[i], ">") == 0) || (strcmp(args[i], ">>") == 0)){
			// checks if there exists an argument after the redirector
			if (args[i+1] == NULL) {
				printf("Error: expected arg after %s \n", args[i]); 
				return;
			}
			// sends formatted output to the string call
			sprintf(call, "%s %s %s", call, args[i], args[i+1]);	
			break;
		}
	}
	// sends the printenv command to the system so it can make call to output all environment variables
    system(call);
}

// function that echos the string entered by user
void callEcho(char **s) {
	for (int i = 1; i < 100; i++){
		// breaks if nothing is entered
		if(s[i] == NULL) {
			break; 
		}
		// sends formatted output to the string s[0]
		sprintf(s[0], "%s %s", s[0], s[i]);	
	}
	// sends echo command to the system so it can make the call
    system(s[0]);
}

// function that pauses the execution of the shell
void pauseEnter() {
	// makes call to allow user to press enter for shell execution resumption
    system("read -p 'Press [Enter] key to start backup...' enter");
}

// function that clears the screen
void clr(){
	// makes system call for clearing the shell screen with either the cls or clear command
    system("cls||clear");
}

// function that displays the UNIX manual in shell
void help(char **args) {
	char call[50] = "more README.md";
	for (int i = 1; i < 100; i++){
		// break if no user input
		if (args[i] == NULL){
            break;
        }
		printf("%s\n", args[i+1]);
		// checks for the occurrence of each redirector
		if ((strcmp(args[i], ">") == 0) || (strcmp(args[i], ">>") == 0)){
			// checks if there exists an argument after the redirector
			if (args[i+1] == NULL) {
				printf("Error: expected arg after %s \n", args[i]); 
				return;
			}
			// sends formatted output to the string
			sprintf(call, "%s %s %s", call, args[i], args[i+1]);	
			break;
		}
	}
	// sends help command to the system so it can make the call for displaying the README.md file
	system(call);
}
