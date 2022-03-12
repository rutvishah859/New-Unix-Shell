#ifndef MYSHELL_H_
#define MYSHELL_H_

#include <stdbool.h>

#ifdef _WIN32
#include <io.h>
#define pMax _MAX_PATH
#else
#include <unistd.h>
#define pMax FILENAME_MAX
#endif

#define BUFFER_LEN 256
#define DELIM " \t\r\n\a"

char currDir[pMax];

// all the command line functions
int cd(char **args);
int dir();
void environ(char **args);
void callEcho(char **s);
void pauseEnter();
void clr();
void help(char **s);
void myshell(char **filename);

// all the build in command line commands that shell supports
char *builtin[] = {
    "cd",
    "dir",
    "environ",
    "echo",
    "pause",
    "clr",
    "help",
    "myshell"
};

// functions associated with each valid command line input
int (*builtinFunc[]) (char **) = {
    &cd,
    &dir,
    &environ,
    &callEcho,
    &pauseEnter,
    &clr,
    &help,
    &myshell
};

int numBuiltIns();
int dir(char **args);
char **splitComm(char *command);
int cd(char **args); 
void myshell(char **filename);
int execute(char **args);
#endif /* MYSHELL_H_ */