#include "header.h"

void echo(char * e) {
    int num=0;
    char ** s = malloc(100 * sizeof(char *));
    while(e!=NULL) {
        s[num++]=e;
        printf("%s ",s[num-1]);
        e = strtok(NULL, " \t\n");
    }
    printf("\n");
}