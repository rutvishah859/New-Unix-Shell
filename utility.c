#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

void environ(char **args) {
	char call[50] = "printenv";
	for (int i = 1; i < 100; i++){
		if (args[i] == NULL){
            break;
        }
		printf("%s\n", args[i+1]);
		if ((strcmp(args[i], ">") == 0) || (strcmp(args[i], ">>") == 0)){
			if (args[i+1] == NULL) {
				printf("Error: expected arg after %s \n", args[i]); 
			}
			sprintf(call, "%s %s %s", call, args[i], args[i+1]);	
			break;
		}
	}
    system(call);
}

void callEcho(char **s) {
	for (int i = 1; i < 100; i++){
		if(s[i] == NULL) {
			break; 
		}
		sprintf(s[0], "%s %s", s[0], s[i]);	
	}
    system(s[0]);
}

void pauseEnter() {
    system("read -p 'Press [Enter] key to start backup...' enter");
}

int str_tokens(char* str, char tokens[][256]){
	const char dem[2] = " ";
	int count = 0;
	char* token = strtok(str, dem);
	while (token != NULL){
		strcpy(tokens[count], token);
		count ++;
		token = strtok(NULL, dem);
	}
	return count;
}

//clear the screen
void clr(){
    system("cls||clear");
}

// display the UNIX manual in terminal
void help(char **args) {
	char call[50] = "more README.md";
	for (int i = 1; i < 100; i++){
		if (args[i] == NULL){
            break;
        }
		printf("%s\n", args[i+1]);
		if ((strcmp(args[i], ">") == 0) || (strcmp(args[i], ">>") == 0)){
			if (args[i+1] == NULL) {
				printf("Error: expected arg after %s \n", args[i]); 
			}
			sprintf(call, "%s %s %s", call, args[i], args[i+1]);	
			break;
		}
	}
	system(call);
}