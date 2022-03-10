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

void pause() {
    system("read -p 'Press [Enter] key to start backup...' enter");
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
    struct dirent *dir;
    DIR *d = NULL;
    d = opendir(path);
    if(d == NULL){
        printf("Could not find the directory specified by pathname: %s\n", path);
    }
    while ((dir == readdir(d))!= NULL){
        printf("%s\n", dir->d_name);
    }

    closedir(d);

}
