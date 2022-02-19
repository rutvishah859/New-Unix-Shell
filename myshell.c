#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "myshell.h"
#include "utility.c"

#define BUFFER_LEN 256

int main(int argc, char *argv[]) {
    char command[BUFFER_LEN] = { 0 };
    while(true) {
        printf("$");
        scanf("%[^\n]%*c", command);
        break;
    }
}