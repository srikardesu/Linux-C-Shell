#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define CYAN "\e[0;36m"
#define GREENBG "\e[42m"
#define reset "\e[0m"
#define YELLOW "\e[0;33m"
#define MAG "\e[0;35m"
#define HMAG "\e[0;95m"
#define BHMAG "\e[1;95m"
#define YELHB "\e[0;103m"
#define HRED "\e[0;91m"


#define SIZE 1500
char host[SIZE], user[SIZE], cwd[SIZE], home[SIZE];
char hist[30][SIZE];
extern int start;
char ** bgproc;
int * bgPid;
extern int child_id,shell_id;
char curr_fore[SIZE];

void prompt();
void pwd();
void echo(char *e);
void ls(char ** s, int num);
int cd(char ** s, char * store_old_dir, int num);
int background(char ** s);
void pinfo(char ** s, int num);
void write_history(char * command);
void history();
void history_num(int num);
void foreground(char ** s, int num);
void exec_com(char execute[SIZE], char * store_old_dir);
void redirection(char exec[SIZE]);
void jobs(char ** s, int num, int type);

#endif

