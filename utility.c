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

void callEcho(char *s) {
    system(s);
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

//change the current working directory
void cd(char* pwd, char* path){
    int changed_dir = chdir(path);
    if (strcmp(path, "") != 0){
	    if(changed_dir == 0){
		    getcwd(pwd, 256);
	    }
	    printf("%s> No such directory found\n", pwd);
    }
}

//change the current working directory
void cd(char* pwd, char* path){
    int changed_dir = chdir(path);
    if (changed_dir == 0){
        printf("Current working directory has been changed to: %s\n ", path);
        getcwd(pwd, 256);
    }
    else{
        printf("%s> The specified directory was not found\n", pwd);
    }
}

//clear the screen
void clr(){
    system("cls||clear");
}

//display the contents of the specified directory
void dir(char* path){
	struct dirent *direct;
	DIR *dr = NULL;
	if(strcmp(path, "") == 0){
		dr = opendir(".");
	}
	else{
		dr = opendir(path);
	}
	if (dr == NULL){
		printf("The directory could not be found");
	}
	while ((direct = readdir(dr)) != NULL){
		printf("%s\n" , direct -> d_name);
	}
	closedir(dr);

}
