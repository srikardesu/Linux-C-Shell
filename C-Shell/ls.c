#include "header.h"

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void ls_normal(char * dir) {
    if(!isDirectory(dir)) {
        FILE *f = fopen(dir,"r");
        if(f==NULL) {
            printf("ls: cannot access '%s': No such file or directory\n",dir);
            return;
        }
        printf("%s\n",dir);
        return;
    }
    DIR *p;
    struct dirent *d;
    p = opendir(dir);
    if(p==NULL) {
        perror("Error");
    }
    else {
        char ** sorted = malloc(100 * sizeof(char *));
        int sz=0;
        while(d=readdir(p)) {
            char * filename = d->d_name;
            if(filename[0]=='.') continue;
            sorted[sz++]=filename;
        }
        char * temp = malloc(1000*sizeof(char));
        for(int i=0;i<sz;i++) {
            for(int j=i+1;j<sz;j++) {
                if(strcmp(sorted[i],sorted[j])>0) {
                    strcpy(temp,sorted[i]);
                    strcpy(sorted[i],sorted[j]);
                    strcpy(sorted[j],temp);
                }
            }
        }
        for(int i=0;i<sz;i++) printf( "%s\n",sorted[i]);
    }
    closedir(p);
}

void lsa(char * dir) {
    if(!isDirectory(dir)) {
        FILE *f = fopen(dir,"r");
        if(f==NULL) {
            printf("ls: cannot access '%s': No such file or directory\n",dir);
            return;
        }
        printf("%s\n",dir);
        return;
    }
    DIR *p;
    struct dirent *d;
    p = opendir(dir);
    if(p==NULL) {
        perror("Error");
    }
    else {
        char ** sorted = malloc(100 * sizeof(char *));
        int sz=0;
        while(d=readdir(p)) {
            char * filename = d->d_name;
            sorted[sz++]=filename;
        }
        char * temp = malloc(1000*sizeof(char));
        for(int i=0;i<sz;i++) {
            for(int j=i+1;j<sz;j++) {
                if(strcmp(sorted[i],sorted[j])>0) {
                    strcpy(temp,sorted[i]);
                    strcpy(sorted[i],sorted[j]);
                    strcpy(sorted[j],temp);
                }
            }
        }
        for(int i=0;i<sz;i++) printf( "%s\n",sorted[i]);
    }
    closedir(p);
}

void lsl(char * dir) {
    if(!isDirectory(dir)) {
        FILE *f = fopen(dir,"r");
        if(f==NULL) {
            printf("ls: cannot access '%s': No such file or directory\n",dir);
            return;
        }
        struct stat s_file;
        stat(dir,&s_file);
        printf((s_file.st_mode & S_IRUSR) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWUSR) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXUSR) ?  "x" :  "-");
        printf((s_file.st_mode & S_IRGRP) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWGRP) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXGRP) ?  "x" :  "-");
        printf((s_file.st_mode & S_IROTH) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWOTH) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXOTH) ?  "x" :  "-");
        printf( " %3d", (int)s_file.st_nlink);
        printf( " %8.8s", getpwuid(s_file.st_uid)->pw_name);
        printf( "%8.8s", getgrgid(s_file.st_gid)->gr_name);
        printf( " %6lld", (long long int)s_file.st_size);
        struct tm *time;
        char date[SIZE];
        char realdate[SIZE];
        time = localtime(&s_file.st_mtime);
        strftime(date, SIZE, "%b  %d %H:%M", time);
        printf( " %s ",date);
        printf(HRED "%s\n",dir);
        return;
    }
    DIR *p;
    struct dirent *d;
    p = opendir(dir);
    if(p==NULL) {
        perror("Error");
    }
    else {
        char ** sorted = malloc(100 * sizeof(char *));
        int sz=0; long long int blocks = 0;
        while(d=readdir(p)) {
            char * filename = d->d_name;
            if(filename[0]=='.') continue;
            sorted[sz++]=filename;
            char path[SIZE];
            strcpy(path,dir);
            strcat(path,"/");
            strcat(path,filename);
            struct stat s_file;
            stat(path,&s_file);
            blocks+=s_file.st_blocks;
        }
        printf( "total %lld\n",blocks/2);
        char * temp = malloc(1000*sizeof(char));
        for(int i=0;i<sz;i++) {
            for(int j=i+1;j<sz;j++) {
                if(strcmp(sorted[i],sorted[j])>0) {
                    strcpy(temp,sorted[i]);
                    strcpy(sorted[i],sorted[j]);
                    strcpy(sorted[j],temp);
                }
            }
        }
        for(int i=0;i<sz;i++) {
            char * filename = sorted[i];
            char *filepath;
            filepath = malloc(100 *sizeof(char));
            // filepath of all files
            strcpy(filepath,dir);
            strcat(filepath,"/");
            strcat(filepath,filename);
            struct stat s_file;
            stat(filepath,&s_file);
            printf((s_file.st_mode & S_IRUSR) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWUSR) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXUSR) ?  "x" :  "-");
            printf((s_file.st_mode & S_IRGRP) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWGRP) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXGRP) ?  "x" :  "-");
            printf((s_file.st_mode & S_IROTH) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWOTH) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXOTH) ?  "x" :  "-");
            printf( " %3d", (int)s_file.st_nlink);
            printf( " %8.8s", getpwuid(s_file.st_uid)->pw_name);
            printf( "%8.8s", getgrgid(s_file.st_gid)->gr_name);
            printf( " %6lld", (long long int)s_file.st_size);
            struct tm *time;
            char date[SIZE];
            char realdate[SIZE];
            time = localtime(&s_file.st_mtime);
            strftime(date, SIZE, "%b  %d %H:%M", time);
            printf( " %s ",date);
            printf(HRED "%s\n",filename);
        }
    }
    closedir(p);
}

void lsla(char *dir) {
    if(!isDirectory(dir)) {
        FILE *f = fopen(dir,"r");
        if(f==NULL) {
            printf("ls: cannot access '%s': No such file or directory\n",dir);
            return;
        }
        struct stat s_file;
        stat(dir,&s_file);
        printf((s_file.st_mode & S_IRUSR) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWUSR) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXUSR) ?  "x" :  "-");
        printf((s_file.st_mode & S_IRGRP) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWGRP) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXGRP) ?  "x" :  "-");
        printf((s_file.st_mode & S_IROTH) ?  "r" :  "-");
        printf((s_file.st_mode & S_IWOTH) ?  "w" :  "-");
        printf((s_file.st_mode & S_IXOTH) ?  "x" :  "-");
        printf( " %3d", (int)s_file.st_nlink);
        printf( " %8.8s", getpwuid(s_file.st_uid)->pw_name);
        printf( "%8.8s", getgrgid(s_file.st_gid)->gr_name);
        printf( " %6lld", (long long int)s_file.st_size);
        struct tm *time;
        char date[SIZE];
        time = localtime(&s_file.st_mtime);
        strftime(date, SIZE, "%b  %d %H:%M", time);
        printf( " %s ",date);
        printf(HRED "%s\n",dir);
        return;
    }
    DIR *p;
    struct dirent *d;
    p = opendir(dir);
    if(p==NULL) {
        perror("Error");
    }
    else {
        char ** sorted = malloc(100 * sizeof(char *));
        int sz=0; long long int blocks = 0;
        while(d=readdir(p)) {
            char * filename = d->d_name;
            sorted[sz++]=filename;
            char path[SIZE];
            strcpy(path,dir);
            strcat(path,"/");
            strcat(path,filename);
            struct stat s_file;
            stat(path,&s_file);
            blocks+=s_file.st_blocks;
        }
        printf( "total %lld\n",blocks/2);
        char * temp = malloc(1000*sizeof(char));
        for(int i=0;i<sz;i++) {
            for(int j=i+1;j<sz;j++) {
                if(strcmp(sorted[i],sorted[j])>0) {
                    strcpy(temp,sorted[i]);
                    strcpy(sorted[i],sorted[j]);
                    strcpy(sorted[j],temp);
                }
            }
        }
        for(int i=0;i<sz;i++) {
            char * filename = sorted[i];
            char *filepath;
            filepath = malloc(100 *sizeof(char));
            strcpy(filepath,dir);
            strcat(filepath,"/");
            strcat(filepath,filename);
            struct stat s_file;
            stat(filepath,&s_file);
            printf((s_file.st_mode & S_IRUSR) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWUSR) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXUSR) ?  "x" :  "-");
            printf((s_file.st_mode & S_IRGRP) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWGRP) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXGRP) ?  "x" :  "-");
            printf((s_file.st_mode & S_IROTH) ?  "r" :  "-");
            printf((s_file.st_mode & S_IWOTH) ?  "w" :  "-");
            printf((s_file.st_mode & S_IXOTH) ?  "x" :  "-");
            printf( " %3d", (int)s_file.st_nlink);
            printf( " %8.8s", getpwuid(s_file.st_uid)->pw_name);
            printf( "%8.8s", getgrgid(s_file.st_gid)->gr_name);
            printf( " %6lld", (long long int)s_file.st_size);
            struct tm *time;
            char date[SIZE];
            char realdate[SIZE];
            time = localtime(&s_file.st_mtime);
            strftime(date, SIZE, "%b  %d %H:%M", time);
            printf( " %s ",date);
            printf(HRED "%s\n",filename);
        }
    }
    closedir(p);
}

void lsprev() {
    char dir[SIZE];
    getcwd(dir,SIZE);
    if(!isDirectory(dir)) {
        FILE *f = fopen(dir,"r");
        if(f==NULL) {
            printf("ls: cannot access '%s': No such file or directory\n",dir);
            return;
        }
        printf("%s\n",dir);
        return;
    }
    if(strlen(dir)==1) {
        return;
    }
    else {
        int len = strlen(dir); int pos = -1;
        for(int i=0;i<len;i++) {
            if(dir[i]=='/') pos=i;
        }
        char * curr=malloc(1000*sizeof(char)); int sz=0;
        for(int i=0;i<pos;i++) curr[sz++]=dir[i];
        curr[sz++]='\0';
        ls_normal(curr);
    }
}

void ls(char ** s, int num) {
    if(num  == 1) {
        char dir[SIZE];
        getcwd(dir,SIZE);
        ls_normal(dir);
    }
    else if(num == 2) {
        char dir[SIZE];
        getcwd(dir,SIZE);
        if(!strcmp(s[1],".")) {
            ls_normal(dir);
        }
        else if(!strcmp(s[1],"-a")) {
            lsa(dir);
        }
        else if(!strcmp(s[1],"-l")) {
            lsl(dir);
        }
        else if(!strcmp(s[1],"..")) {
            lsprev();   
        }
        else if(!strcmp(s[1],"~")) {
            ls_normal(home);   
        }
        else if(!strcmp(s[1],"-la") || !strcmp(s[1],"-al")) {
            lsla(dir);
        }
        else {
            int f=0;
            f=1; int i=1; int a_flag=0,l_flag=0;
            if(s[i][0]=='~') {
                char * path = malloc(1000 * sizeof(char));
                int j;
                for(j=0;j<strlen(home);j++) {
                    path[j]=home[j];
                }
                for(int k=1;k<=strlen(s[i]);k++) {
                    path[j++]=s[i][k];
                }
                if(a_flag && l_flag) lsla(path);
                else if(a_flag) lsa(path);
                else if(l_flag) lsl(path);
                else ls_normal(path);
            }
            else {
                if(a_flag && l_flag) lsla(s[i]);
                else if(a_flag) lsa(s[i]);
                else if(l_flag) lsl(s[i]);
                else ls_normal(s[i]);
            }
        }
    }
    else {
        int a_flag=0,l_flag=0;
        int f = 0;
        for(int i=1; i<num; i++) {
            if(!strcmp(s[i],"-l")) l_flag=1;
            else if(!strcmp(s[i],"-a")) a_flag=1;
            else if(!strcmp(s[i],"-al") || !strcmp(s[i],"-la")) a_flag=1,l_flag=1;
        }
        int cnt=0;
        for(int i=1;i<num;i++) {
            if(!strcmp(s[i],"-l")) continue;
            else if(!strcmp(s[i],"-a")) continue;
            else if(!strcmp(s[i],"-al") || !strcmp(s[i],"-la")) continue;
            else {
                cnt++;
            }
        }
        if(cnt==1) {
            for(int i=1; i<num; i++) {
                if(!strcmp(s[i],"-l")) continue;
                else if(!strcmp(s[i],"-a")) continue;
                else if(!strcmp(s[i],"-al") || !strcmp(s[i],"-la")) continue;
                else {
                    f=1;
                    if(s[i][0]=='~') {
                        char * path = malloc(1000 * sizeof(char));
                        int j;
                        for(j=0;j<strlen(home);j++) {
                            path[j]=home[j];
                        }
                        for(int k=1;k<=strlen(s[i]);k++) {
                            path[j++]=s[i][k];
                        }
                        if(a_flag && l_flag) lsla(path);
                        else if(a_flag) lsa(path);
                        else if(l_flag) lsl(path);
                        else ls_normal(path);
                    }
                    else {
                        if(a_flag && l_flag) lsla(s[i]);
                        else if(a_flag) lsa(s[i]);
                        else if(l_flag) lsl(s[i]);
                        else ls_normal(s[i]);
                    }
                }
            }
        }
        else {
            for(int i=1; i<num; i++) {
                if(!strcmp(s[i],"-l")) continue;
                else if(!strcmp(s[i],"-a")) continue;
                else if(!strcmp(s[i],"-al") || !strcmp(s[i],"-la")) continue;
                else {
                    f=1;
                    if(s[i][0]=='~') {
                        char * path = malloc(1000 * sizeof(char));
                        int j;
                        for(j=0;j<strlen(home);j++) {
                            path[j]=home[j];
                        }
                        for(int k=1;k<=strlen(s[i]);k++) {
                            path[j++]=s[i][k];
                        }
                        printf(HRED "%s :\n",path);
                        if(a_flag && l_flag) lsla(path);
                        else if(a_flag) lsa(path);
                        else if(l_flag) lsl(path);
                        else ls_normal(path);
                    }
                    else {
                        printf(HRED "%s :\n",s[i]);
                        if(a_flag && l_flag) lsla(s[i]);
                        else if(a_flag) lsa(s[i]);
                        else if(l_flag) lsl(s[i]);
                        else ls_normal(s[i]);
                    }
                }
            }
        }
        char dir[SIZE];
        getcwd(dir,SIZE);
        if(!f) {
            if(a_flag && l_flag) lsla(dir);
            else if(a_flag) lsa(dir);
            else if(l_flag) lsl(dir);
            else ls_normal(dir);
        }
    }
}