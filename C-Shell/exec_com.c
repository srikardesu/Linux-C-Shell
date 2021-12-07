#include "header.h"

char ** spaceremover(char ** s, int len) {
    char ** send=malloc(100 * sizeof(char *));
    for(int i=0;i<len;i++) {
        char * out;
        out = malloc(1000 * sizeof(char));
        int cnt=0;
        for (int ii = 0; ii<=strlen(s[i]); ii++) {
            if (s[i][ii]!=' ' && s[i][ii]!='\t' && s[i][ii]!='\n')                                                 
                out[cnt++]=s[i][ii];                                                                                                        
        }
        s[i]=out;
    }
    return s;
}
void repeat(int num, char * store_old_dir, char ** ripit, int len) {
    char ** t = malloc(100 * sizeof(char *));
    char ** s = malloc(100 * sizeof(char *));
    int tnum = 0;
    char * store;
    if(!strcmp(ripit[2],"cd")) {
        for(int j=0;j<num;j++) {
            char ** temp;
            temp = malloc(100 * sizeof(char *));
            int numm=0;
            for(int i=2;i<len;i++) {
                temp[numm++]=ripit[i];
            }
            temp[numm]=NULL;
            char rn1[SIZE];
            getcwd(rn1,SIZE);
            int flag = cd(temp,store_old_dir,numm);
            char rn2[SIZE];
            getcwd(rn2,SIZE);
            if(!flag) {
                int siz=strlen(rn1);
                for(int i=0;i<=siz; i++) store_old_dir[i]=rn1[i];
            }
        }    
    }
    else if(!strcmp(ripit[2],"echo")) {
        int nummm=0;
        char ** ss = malloc(100 * sizeof(char *));
        for(int i=3;i<len;i++) {
            ss[nummm++]=ripit[i];
        }
        char ** final = spaceremover(ss,nummm);
        for(int i=0;i<num;i++) {
            for(int j=0;j<nummm;j++) printf("%s ",final[j]);
            printf("\n");
        }
    }
    else if(!strcmp(ripit[2],"pwd")) {
        for(int i=0;i<num;i++) pwd();
    }
    else if(!strcmp(ripit[2],"ls")) { 
        int numm = 0;
        char ** s = malloc(100 * sizeof(char *));
        for(int i=2;i<len;i++) {
            s[numm++]=ripit[i];
        }
        for(int i=0;i<num;i++) ls(s,numm);
    }
    else if(!strcmp(ripit[2],"repeat")) {
        int numm = 0;
        char ** s = malloc(100 * sizeof(char *));
        for(int i=2;i<len;i++) {
            s[numm++]=ripit[i];
        }
        for(int i=0;i<num;i++) repeat(atoi(s[1]),store_old_dir,s,numm);
    }
    else if(!strcmp(ripit[2],"pinfo")) {
        int numm=0;
        for(int i=2;i<len;i++) {
            s[numm++]=ripit[i];
        }
        s[numm]=NULL;
        for(int i=0;i<num;i++) pinfo(s,numm),printf("********************************************************************************\n");
    }
    else if(!strcmp(ripit[2],"history")) {
        int numm=0;
        for(int i=2;i<len;i++) {
            s[numm++]=ripit[i];
        }
        s[numm]=NULL;
        if(numm==1) for(int i=0;i<num;i++) history();
        else for(int i=0;i<num; i++) history_num(atoi(s[1]));
    }
    else {
        int numm=0;
        for(int i=2;i<len;i++) {
            s[numm++]=ripit[i];
        }
        if(!strcmp(s[numm-1],"&")) {
            char ** t = malloc(100 * sizeof(char *));
            for(int i=0;i<numm-1;i++) t[i]=s[i];
            t[numm-1]=NULL;
            background(t);
        }
        else { s[numm++]=NULL; for(int i=0;i<num;i++) foreground(s,numm); }
    }
} 

int is_redirection(char command[SIZE]) {
    char * output = strstr(command, ">");
    char * input = strstr(command, "<");
    if(output!=NULL || input!=NULL) return 1;
    else return 0; 
}
int is_piping(char command[SIZE]) {
    char * output = strstr(command, "|");
    if(output!=NULL) return 1;
    else return 0; 
}
void piping(char * command, char * store_old_dir) {
    char ** pipeargs;
    pipeargs=malloc(100 * sizeof(char *));
    char * store;
    store=malloc(1000 * sizeof(char));
    strcpy(store,command);
    char * temporary;
    int num=0;
    temporary = strtok(store,"|");
    while(temporary!=NULL) {
        pipeargs[num]=temporary;
        num++;
        temporary=strtok(NULL,"|");
    }
    pipeargs[num]=NULL; int pipes[2];
    pid_t pid; int filed=0;
    for(int i=0;i<num;i++) {
        pipe(pipes);
        pid = fork();
        if(pid < 0) {
            perror("Error in forking:");
        }
        else if(pid==0) {
            dup2(filed,0);
            if(pipeargs[i+1]!=NULL) {
                dup2(pipes[1],1);
            }
            close(pipes[0]);
            exec_com(pipeargs[i],store_old_dir);
            exit(0);
        }
        else if(pid > 0) {
            wait(NULL);
            close(pipes[1]);
            filed=pipes[0];
        }
    }
}

void exec_com(char execute[SIZE], char * store_old_dir) {
    char temporary[SIZE]; char ppcommand[SIZE];
    strcpy(temporary,execute);
    strcpy(ppcommand,execute);
    int check = is_redirection(temporary);
    int check_pp = is_piping(ppcommand);
    if(check_pp) {
        piping(ppcommand,store_old_dir);
        return;
    }
    if(check) {
        redirection(temporary);
        return;
    }
    char ** s = malloc(1000 * sizeof(char *));
    char * e = strtok(execute," \n");
    s[0]=e;
    int num=0;
    if(!strcmp(s[0],"cd")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL, " \n");
        }
        char rn1[SIZE];
        getcwd(rn1,SIZE);
        int flag = cd(s,store_old_dir,num);
        char rn2[SIZE];
        getcwd(rn2,SIZE);
        if(!flag) {
            int siz=strlen(rn1);
            for(int i=0;i<=siz; i++) store_old_dir[i]=rn1[i];
        }
    }
    else if(!strcmp(s[0],"echo")) {
        e = strtok(NULL, " \t\n");
        echo(e);
    }
    else if(!strcmp(s[0],"pwd")) {
        pwd();
    }
    else if(!strcmp(s[0],"ls")) {
        char * exec = e;
        int num = 0;
        char ** s = malloc(100 * sizeof(char *));
        while(exec != NULL) {
            s[num++]=exec;
            exec = strtok(NULL, " \t\n");
        }
        ls(s,num);
    }
    else if(!strcmp(s[0],"repeat")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL, " \t\n");
        }
        int val = atoi(s[1]);
        repeat(val,store_old_dir,s,num);
    }
    else if(!strcmp(s[0],"pinfo")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL, " \n");
        }
        s[num]=NULL;
        pinfo(s,num);
    }
    else if(!strcmp(s[0],"history")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL, " \n");
        }
        if(num==1) history();
        else history_num(atoi(s[1]));
    }
    else if(!strcmp(s[0],"jobs")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL," \n");
        }
        s[num]=NULL;
        /*for(int i=0;i<num;i++) printf("%s\n",s[i]);
        printf("%d\n",num);*/
        jobs(s,num,1);
    }
    else if(!strcmp(s[0],"sig")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL," \n");
        }
        s[num]=NULL;
        jobs(s,num,2);
    }
    else if(!strcmp(s[0],"replay")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL," \n");
        }
        s[num]=NULL;
        /*clock_t t;
        t = clock();*/
        int time_int = atoi(s[num-3]);
        int tot_time = atoi(s[num-1]);
        char * send;
        send = malloc(100 * sizeof(char));
        strcpy(send,s[2]);
        strcat(send," ");
        for(int i=3;i<num-4;i++) {
            strcat(send,s[i]);
            strcat(send," ");
        }
        //printf("%s\n",send);
        /*clock_t elapsed;
        elapsed = clock()-t;
        double time_taken1 = ((double)t)/CLOCKS_PER_SEC;
        double time_taken2 = ((double)elapsed)/CLOCKS_PER_SEC;
        printf("%lf\n%lf\n",time_taken1,time_taken2);*/
        int count;
        count = tot_time/time_int;
        int from=0;
        while(from<count) {
            sleep(time_int);
            char * temp = malloc(1000 * sizeof(char));
            strcpy(temp,send);
            exec_com(temp,store_old_dir);
            from++;
        }
        sleep(tot_time-time_int*count);
    }
    else if(!strcmp(s[0],"fg")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL," \n");
        }
        s[num]=NULL;
        jobs(s,num,3);
    }
    else if(!strcmp(s[0],"bg")) {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL," \n");
        }
        s[num]=NULL;
        jobs(s,num,4);
    }
    else if(!strcmp(s[0],"quit")) {
        exit(1);
    }
    else {
        while(e!=NULL) {
            s[num++]=e;
            e = strtok(NULL, " \t\n");
        }
        if(!strcmp(s[num-1],"&")) {
            char ** t = malloc(100 * sizeof(char *));
            for(int i=0;i<num-1;i++) {
                t[i]=s[i];
            }
            t[num-1]=NULL;
            int id = background(t);
            bgPid[start]=id;
            bgproc[start]=malloc(1000 * sizeof(char));
            strcpy(bgproc[start],s[0]);
            start = start + 1;
        }
        else { s[num++]=NULL; foreground(s,num); }
    }
}