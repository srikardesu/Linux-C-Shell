#include "header.h"

void pwd(void) {
    char *dir = malloc(1000*sizeof(char));
    getcwd(dir,SIZE);
    printf("%s\n",dir);
}