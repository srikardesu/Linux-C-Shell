#include "header.h"

void write_history(char * command) {
    char fname[10*SIZE];
    strcpy(fname,home);
    strcat(fname,"/history.txt");
    FILE *f = fopen(fname, "r+");
    int stt=0;
    char * line = NULL;
    ssize_t read;
    ssize_t len=0;
    if(f==NULL) {
        perror("Error: in file operations");
    }
    while(read = getline(&line,&len,f) != -1) {
        strcpy(hist[stt],line);
        stt++;
    }
    char temp[21][SIZE];
    if(stt==20) {
        if(!strcmp(hist[19],command)) goto L;
        for(int i=1;i<20;i++) {
            strcpy(temp[i-1],hist[i]);
        }
        strcpy(temp[19],command);
        fclose(f);
        f = fopen(fname, "w");
        for(int i=0;i<20;i++) {
            fprintf(f,"%s",temp[i]);
        }
    }
    else {
        if(!strcmp(hist[stt-1],command)) goto L;
        fprintf(f,"%s",command);
    }
    L : fclose(f);
}

void history() {
    char fname[SIZE];
    strcpy(fname,home);
    strcat(fname,"/history.txt");
    FILE *f = fopen(fname, "r");
    int stt=0;
    char * line = NULL;
    ssize_t read;
    ssize_t len=0;
    char temp[21][SIZE];
    while(read = getline(&line,&len,f) != -1) {
        strcpy(temp[stt],line);
        stt++;
    }
    if(stt < 10) {
        for(int i=0;i<stt;i++) {
            printf("%s",temp[i]);
        }
    }
    else {
        for(int i = stt-10;i<stt;i++) {
            printf("%s",temp[i]);
        }
    }
}

void history_num(int num) {
    char fname[SIZE];
    strcpy(fname,home);
    strcat(fname,"/history.txt");
    FILE *f = fopen(fname, "r");
    int stt=0;
    char * line = NULL;
    ssize_t read;
    ssize_t len=0;
    char temp[21][SIZE];
    while(read = getline(&line,&len,f) != -1) {
        strcpy(temp[stt],line);
        stt++;
    }
    if(num > stt) {
        printf("Error: numbered entered more than total commands entered.\n");
    }
    else {
        for(int i=stt-num;i<stt;i++) {
            printf("%s",temp[i]);
        }
    }
}