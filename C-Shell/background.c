#include "header.h"

pid_t process_id;

int background(char ** s) {
    process_id = fork();
    setpgid(0,0);
    if(process_id < 0) {
        perror("Error: Fork failed\n");
        return -1;
    }
    else if(process_id == 0) {
        //pid_t p_child = getpid();
        int status = execvp(s[0],s);
        if(status < 0) {
            perror("Shell: Error\n");
        }
        //printf("Exited with\n");
        return process_id;
    }
    else { printf("Process ID: %d\n",process_id); return process_id; }
}