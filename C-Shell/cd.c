#include "header.h"

int cd(char ** s, char * store_old_dir, int num) {
    if(num > 2) {
        printf("enter valid number of parameters\n");
        return -1;
    }
    else if(num==1) {
        if(chdir(home)) {
            perror("Error");
            return -1;
        }
    }
    else if(s[1][0]=='~') {
        char * s1 = home;
        char * tojump = malloc(1000 * sizeof(char));
        char *s2;
        if(s[1][1]=='\0') {
            if(chdir(home)) {
                perror("Error");
                return -1;
            } 
        }
        else {
            s2 = malloc(1000 * sizeof(char));
            int start=0;
            for(int i=1; i<strlen(s[1]); i++) {
                s2[start++]=s[1][i];
            }
            s2[start++]='\0';
            strcpy(tojump,s1);
            strcat(tojump,s2);
            if(chdir(tojump)) {
                perror("Error");
                return -1;
            }
        }
    }
    else if(s[1][0]=='-') {
        printf("%s\n",store_old_dir);
        if(chdir(store_old_dir)) {
            perror("Error");
            return -1;
        }
    }
    else if(chdir(s[1]) != 0) {
        perror("Error");
        return -1;
    }
    return 0;
}