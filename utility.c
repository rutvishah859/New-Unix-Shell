#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

void environ() {
    // be able to support piping
    system("printenv");
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
void help() {
	system("more README.md"); 
}