#include "header.h"

/*int START=0;
char ** bgproc;
int * bgPid;*/
int GLOBAL_FLAG=0;
char * store_old_dir;
int hist_start=0;
int start=0;
int child_id;
int shell_id;

void bgHandler() {
    int status;
    int process_id = waitpid(-1,&status,WNOHANG);
    if(process_id > 0) {
        int pos = 0;
        int f = 0;
        for(int i=0;i<100;i++) {
            if(bgPid[i] == process_id) {
                pos = i; f=1;
                break;
            }
        }
        int flg = 0;
        flg = WIFEXITED(status);
        if(flg) fprintf(stderr, "\n%s with pid %d exited %s\n", bgproc[pos], bgPid[pos],"normally");
        else fprintf(stderr, "\n%s with pid %d exited %s\n", bgproc[pos], bgPid[pos],"abnormally");
        GLOBAL_FLAG=1;
        bgPid[pos] = 0;
        free(bgproc[pos]);
        prompt();
        fflush(stdout);
    }
}

void ctrl_c_handler(int sig) {
    pid_t p = getpid();
    GLOBAL_FLAG=1;
    if(p!=shell_id) {
        kill(child_id,SIGINT);
    }
    else if(p==shell_id && child_id==-1) {
        printf("\n");
        prompt();
        fflush(stdout);
    }
    signal(SIGINT,ctrl_c_handler);
}

void ctrl_z_handler(int sig) {
    pid_t p =getpid();
    GLOBAL_FLAG=1;
    if(p!=shell_id) return;
    if(child_id!=-1) {
        kill(child_id,SIGTTIN);
        kill(child_id,SIGTSTP);
        bgPid[start]=child_id;
        bgproc[start]=malloc(1000 * sizeof(char));
        strcpy(bgproc[start],curr_fore);
        start++;
        return;
    }
    signal(SIGTSTP,ctrl_z_handler);
    if(p==shell_id) {
        printf("\n");
        prompt();
        fflush(stdout);
    }
    return;
}

/*int is_redirection(char command[SIZE]) {
    char * output = strstr(command, ">");
    char * input = strstr(command, "<");
    if(output!=NULL || input!=NULL) return 1;
    else return 0; 
}*/

void prompt() {
    char currdirpath[SIZE];
    getcwd(currdirpath,SIZE);
    int n = strlen(currdirpath);
    int len = strlen(home);
    char display[SIZE];
    if(n<len) {
        int size=0;
        for(int i=0;i<=n;i++) display[size++]=currdirpath[i];
    }
    else {
        display[0]='~';
        int size=1;
        for(int i = len; i<=n; i++) {
            display[size++]=currdirpath[i];
        }
    }
    printf(HMAG "<%s@%s:" CYAN "%s> ", user, host, display);
    if(GLOBAL_FLAG==1) return;
    char * command = NULL;
    ssize_t sz=0;
    int failure = getline(&command, &sz, stdin);
    if(failure==-1) {
        printf("\n");
        exit(0);
    }
    char send[SIZE];
    strcpy(send,command);                                                                                                                                                                                                                                                            
    write_history(send);
    char* token = strtok(command, ";");
    char ** execute =                                                                                                           
    int numm=0; 
    while(token!=NULL) {
        execute[numm++]=token;                                                                                                                                                                                                                                                      
        token = strtok(NULL, ";");
    }
    for(int i=0;i<numm;i++) {
        /*char temporary[SIZE];
        strcpy(temporary,execute[i]);
        int check = is_redirection(temporary);
        if(check) {
            redirection(temporary);
            continue;
        }*/
        exec_com(execute[i],store_old_dir);
    }
}



int main(int argc, char *argv[]) {
    shell_id=getpid();
    signal(SIGCHLD, bgHandler);
    signal(SIGINT, ctrl_c_handler);
    signal(SIGTSTP,ctrl_z_handler);
    printf(CYAN "\n----------------------------------------------------------Welcome to My Shell!!----------------------------------------------------- \n\n" CYAN);
    gethostname(host, sizeof(host));
    getlogin_r(user, sizeof(user));
    getcwd(home,SIZE);
    int len = strlen(home);
    store_old_dir = malloc(1000 * sizeof(char));
    for(int i=0;i<=strlen(home);i++) store_old_dir[i]=home[i];
    bgproc = malloc(1000 * sizeof(char *)); 
    bgPid = malloc(1000 * sizeof(int));
    while(1) {
        child_id=-1;
        prompt();
        GLOBAL_FLAG=0;
    }
}

