#include "header.h"

void foreground(char ** s, int num) {
    int process_id = fork();
    child_id=process_id;
    strcpy(curr_fore,*s);
    if(process_id < 0) {
        perror("Error:\n");
    }
    else if(process_id == 0) {
        setpgid(0,0);
        if(execvp(*s,s) < 0) {
            perror("Error: exec failed\n");
            printf("shell error: %s doesnt work\n",s[0]);
            exit(1);
        }
    }
    else {
        int stat;
        waitpid(process_id,&stat,WUNTRACED);
    }
}