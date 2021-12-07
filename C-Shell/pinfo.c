#include "header.h"

void pinfo(char ** s, int num) {
    char toadd[SIZE];
    pid_t process_id;
    if(num==1) process_id = getpid();
    else process_id = atoi(s[1]);
    char *path = malloc(1000 * sizeof(char));
    sprintf(path,"/proc/%d/stat",process_id);
    FILE *status = fopen(path,"r");
    if(status == NULL) {
        perror("Error: no process\n");
        return;
    }
    int storepid;
    char r_s = '-';
    int par_group;
    int set_group;
    long long int me;
    fscanf(status,
           "%d %*s %c %*s %d %*s %*s %d %*s %*s %*s %*s %*s %*s %*s %*s %*s "
           "%*s %*s %*s %*s %*s %lld",
           &storepid, &r_s, &par_group, &set_group, &me);
    char fgorbg;
    if(par_group==set_group) fgorbg='+';
    else fgorbg=' ';
    printf("pid -- %d\n",process_id);
    printf("Process Status -- %c%c\n", r_s,fgorbg);
    printf("Memory -- %lld {Virtual Memory}\n",me);
    fclose(status);
    char * execpath = malloc(1000 * sizeof(char));
    sprintf(execpath,"/proc/%d/exe",process_id);
    char exepath[SIZE];
    int temp = readlink(execpath,exepath,sizeof(exepath));
    exepath[strlen(exepath)]='\0';
    int len = strlen(home);
    int n = strlen(exepath);
    char display[SIZE];
    if(n<len) {
        int size=0;
        for(int i=0;i<=n;i++) display[size++]=exepath[i];
    }
    else {
        char compare[SIZE]; int szz=0;
        for(int i = 0; i<len; i++) {
            compare[szz++]=exepath[i];
        }
        compare[szz++]='\0';
        if(!strcmp(compare,home)) {
            display[0]='~';
            int size=1;
            for(int i = len; i<=n; i++) {
                display[size++]=exepath[i];
            }
        }
        else {
            strcpy(display,exepath);
        }
    }
    printf("Executable Path -- %s\n", display);
}