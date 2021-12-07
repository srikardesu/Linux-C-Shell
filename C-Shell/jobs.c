#include "header.h"

pid_t child_id;

struct tosort {
    char proc_name[1000];
    int proc_id;
    char stat;
    int job_no_in_array;
};

void sortfunc(struct tosort sortingg[], int f) {
    for(int i=0;i<f;i++) {
        for(int j=i+1;j<f;j++) {
            if(strcmp(sortingg[j].proc_name,sortingg[i].proc_name) < 0) {
                struct tosort storing;
                storing = sortingg[j];
                sortingg[j]=sortingg[i];
                sortingg[i]=storing;
            }
        }
    }
}

int processjobs(struct tosort sortingg[1000]) {
    int f=0;
    char st;
    for(int i=0;i<start;i++) {
        int pid = bgPid[i];
        if(!pid) continue;
        char filename[1000];
        sprintf(filename, "/proc/%d/stat", bgPid[i]);
        FILE * fptr = fopen(filename,"r");
        if(fptr) {
            /*fscanf(fptr, "%*d %*s %c", &st);

            printf("[%d] %s %s [%d]\n", l, st == 'T' ? "Stopped" : "Running",bgproc[i], bgPid[i]);*/
            strcpy(sortingg[f].proc_name,bgproc[i]);
            sortingg[f].proc_id=bgPid[i];
            sortingg[f].stat=st;
            sortingg[f].job_no_in_array=i;
            f++;
        }
        else {
            perror("Error");
        }
        fclose(fptr);
    }
    return f;
}


void jobs(char ** s, int num, int type) {
    struct tosort sortingg[1000];
    int f = processjobs(sortingg);
    sortfunc(sortingg,f);
    /*printf("sorted is : \n");
    for(int i=0;i<f;i++) {
        printf("%s\n",sortingg[i].proc_name);
    }*/
    if(type==1) {
        if(num==1) {
            char st;
            for(int i=0;i<f;i++) {
                char filename[1000];
                int location = sortingg[i].job_no_in_array;
                sprintf(filename, "/proc/%d/stat", bgPid[location]);
                FILE * fptr = fopen(filename,"r");
                if(fptr) {
                    fscanf(fptr, "%*d %*s %c", &st);
                    if(st=='T')
                        printf("[%d] %s %s [%d]\n", location+1, "Stopped",bgproc[location], bgPid[location]);
                    else 
                        printf("[%d] %s %s [%d]\n", location+1, "Running",bgproc[location], bgPid[location]);
                }
            }
        }
        else {
            if(!strcmp(s[1],"-r")) {
                int from=0; char st;
                for(int i=0;i<f;i++) {
                    char filename[1000];
                    int location = sortingg[i].job_no_in_array;
                    sprintf(filename, "/proc/%d/stat", bgPid[location]);
                    FILE * fptr = fopen(filename,"r");
                    if(fptr) {
                        fscanf(fptr, "%*d %*s %c", &st);
                        if(st != 'T') {
                            printf("[%d] %s %s [%d]\n", location+1, "Running",bgproc[location], bgPid[location]);
                            from++;
                        } 
                    }
                }
            }
            else if(!strcmp(s[1],"-s")) {
                int from=0; char st;
                for(int i=0;i<f;i++) {
                    char filename[1000];
                    int location = sortingg[i].job_no_in_array;
                    sprintf(filename, "/proc/%d/stat", bgPid[location]);
                    FILE * fptr = fopen(filename,"r");
                    if(fptr) {
                        fscanf(fptr, "%*d %*s %c", &st);
                        if(st == 'T') {
                            printf("[%d] %s %s [%d]\n", location+1, "Stopped",bgproc[location], bgPid[location]);
                            from++;
                        } 
                    }
                } 
            }
            else {
                printf("Wrong command, please enter a valid command\n");
            }
        }
    }
    else if(type==2) {
        if(num!=3) {
            printf("Incorrect number of arguments received.\n");
            return;
        }
        int which = atoi(s[1]);
        int sig = atoi(s[2]);
        if(which <=0) {
            printf("Bounds error\n");
            return;
        }
        else {
            int location = which-1;
            if(!bgPid[location]) {
                printf("Accesing a job which is not in the job queue anymore\n");
                return;
            }
            kill(bgPid[location],sig);
        }
    }
    else if(type==3) {
        if(num!=2) {
            printf("Incorrect number of arguments received.\n");
        }
        int which = atoi(s[1]);
        if(which <= 0) {
            printf("Bounds error\n");
            return;
        }
        int location = which-1;
        if(!bgPid[location]) {
            printf("Accesing a job which is not in the job queue anymore\n");
            return;
        }
        int pid = bgPid[location];
        int status;
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU,SIG_IGN);
        tcsetpgrp(STDIN_FILENO,pid);
        child_id=pid;
        strcpy(curr_fore,bgproc[location]);
        kill(pid, SIGCONT); 
        free(bgproc[location]);
        bgPid[location]=0;
        waitpid(pid, &status, WUNTRACED); 
        if(WIFSTOPPED(status)) {
            printf("%s with PID %d is suspended\n",curr_fore,child_id);
            bgPid[location]=child_id;
            bgproc[location]=malloc(1000 * sizeof(char));
            strcpy(bgproc[location],curr_fore);
            //start = start + 1;
        }  
        tcsetpgrp(STDIN_FILENO,getpgrp());
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);
        return;
    }
    else if(type==4) {
        if(num!=2) {
            printf("Incorrect number of arguments received.\n");
        }
        int which = atoi(s[1]);
        if(which <=0) {
            printf("Bounds error\n");
            return;
        }
        else {
            int location = which-1;
            if(!bgPid[location]) {
                printf("Accesing a job which is not in the job queue anymore\n");
                return;
            }
            kill(bgPid[location],SIGCONT);
        }
    }
}