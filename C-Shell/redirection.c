#include "header.h"

void redirection(char exec[SIZE]) {
    int mode_in; int mode_out; int st;
    char * input = strstr(exec,"<");
    char * output = strstr(exec,">>");
    if(input!=NULL) {
        mode_in=1;
    }
    else {
        mode_in=0;
    }
    if(output!=NULL) {
        mode_out=2;
    }
    else {
        output = strstr(exec,">");
        if(output!=NULL) {
            mode_out=1;
        }
        else {
            mode_out=0;
        }
    }
    //printf("input mode is : %d\n",mode_in);
    //printf("output mode is: %d\n",mode_out);
    int save_in = dup(STDIN_FILENO);
    int save_out = dup(STDOUT_FILENO);
    char * outputfile; char * inputfile;
    char * storing[10]; int var=0;
    if(mode_out) {
        var=0;
        char * temp;
        char command[SIZE];
        strcpy(command,exec);
        if(mode_out==1) {
            temp = strtok(command,">");
            while(temp!=NULL) {
                storing[var]=malloc(100*sizeof(char));
                strcpy(storing[var],temp);
                var++;
                temp = strtok(NULL,">");
            }
        }
        else {
            temp = strtok(command,">>");
            while(temp!=NULL) {
                storing[var]=malloc(100*sizeof(char));
                strcpy(storing[var],temp);
                var++;
                temp = strtok(NULL,">>");
            }
        }
       // printf("stroing[0] is : %s\n",storing[0]);
        storing[var]=NULL;
        var++; 
        char * tempo = strtok(storing[1]," \r\t\n");
        outputfile = malloc(100*sizeof(char));
        strcpy(outputfile,tempo);
        //printf("output file is %s\n",outputfile);
    } 
    if(mode_in) {
        var=0;
        char * temp;
        char command[SIZE];
        strcpy(command,exec);
        if(mode_in==1) {
            temp = strtok(command,"<");
            while(temp!=NULL) {
                storing[var]=malloc(100*sizeof(char));
                strcpy(storing[var],temp);
                var++;
                temp = strtok(NULL,"<");
            }
            storing[var]=NULL;
        }
        var++;
        char * tempo;
        tempo = strtok(storing[1]," \r\t\n");
        char ** onemorestore=malloc(100*sizeof(char * ));
        int pos;
        onemorestore[0]=malloc(100*sizeof(char));
        strcpy(onemorestore[0],tempo);
        int ii=0;
        while(tempo!=NULL) {
            ii++;
            onemorestore[ii]=malloc(100*sizeof(char));
            strcpy(onemorestore[ii],tempo);
            if(!strcmp(onemorestore[ii],">") || !strcmp(onemorestore[ii],">>")) {pos = ii-1; break;}
            tempo = strtok(NULL," \r\t\n");
            if(tempo==NULL) {pos=ii; break;}
        } 
        inputfile = malloc(100*sizeof(char));
        strcpy(inputfile,onemorestore[pos]);
        //printf("stroing[0] is : %s\n",storing[0]);
    }

    if(mode_in) {
        //error handle here
        if(inputfile==NULL) {
            printf("Please specify the input file name\n");
            return;
        }
    }
    if(mode_out) {
        //error handle here
        if(outputfile==NULL) {
            printf("Please specify the output file name\n");
            return;
        }
    }
    /*printf("inputfile is : %s\n",inputfile);
    printf("outputfile is : %s\n",outputfile);*/
    char ** arg = malloc(100 * sizeof(char *));
    arg[0] = strtok(storing[0]," \t\n\r");
    //printf("%s\n",arg[0]);
    int from=0;
    while(arg[from]!=NULL) {
        from++;
        arg[from]=strtok(NULL, " \n\t\r");
    }
    arg[from]=NULL;
    //printf("arg[0] is : %s\n",arg[0]);
    int offset=0;
    char ** send = malloc(1000 * sizeof(char *));
    for(int i=0;i<from;i++) {
        if(!strcmp(arg[i],"<") || !strcmp(arg[i],">") || !strcmp(arg[i],">>")) {
            break;
        }
        else {
            send[offset]=malloc(1000 * sizeof(char));
            strcpy(send[offset],arg[i]);
            offset++;
        }
    }
    send[offset]=NULL;
    /*for(int i=0;i<offset;i++) {
        printf("%s\n",send[i]);
    }*/
    //printf("INPUT FILE IS : %s\n",inputfile);
    pid_t pid = fork();
    if(pid < 0) {
        printf("Error: in forking\n");
        return ;
    }
    if(pid == 0) {
        // in child
        if(mode_in) {
            int fd_inp=open(inputfile,O_RDONLY);
            //printf("%d\n",fd_inp);
            if(fd_inp < 0) {
                perror("Input redirection");
                exit(0);
            }   
            dup2(fd_inp, 0);
            close(fd_inp);
        }

        if(mode_out)
        {
            int fd_out;
            if(mode_out == 1)
                fd_out = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if(mode_out == 2)
                fd_out = open(outputfile, O_WRONLY | O_CREAT | O_APPEND, 0644);

            if(fd_out < 0) {
                printf("Error ................\n");
                exit(EXIT_FAILURE);
            } 
            dup2(fd_out, 1);         
            close(fd_out);
        }
        if (execvp(send[0], send) < 0) {     
            perror("Command not found");
            exit(EXIT_FAILURE);
        }
        
        dup2(save_in, 0);
        close(save_in);
        
        dup2(save_out, 1);
        close(save_out);
    }        
    
    else {
        while (wait(&st) != pid);
    }

}