### To Run The Shell :

- Clone the repository into the system.
- cd into the corresponding directory
- run make.
- use ./a.out to run the shell.
- To exit the shell use quit.

Note : Run the shell in the directory that it has been cloned into. 

### Files and functions :

Supporting Files :

- main.c - Calls the prompt() function which in turn calls the exec_com function after parsing the input wrt semicolon.
- exec_com.c - Calls the exec_com function which executes the corresponding functionality.
- history.c - Adds commands to a file history.txt and keeps record of the last 20 commands.

Command Files :

- pwd.c - calls the pwd function.
- echo.c - calls the echo function with the corresponding string.
- cd.c - calls the cd function which helps in navigating between different directories.
- foreground.c - helps in executing any process in the foreground using execvp()
- ls.c - calls the ls function which helps in listing files and directories according to different flags.
- background.c - helps in executing any process in the background . Any process with its last token as '&' is treated as a background process.
- jobs.c - helps in calling jobs, sig ,fg and bg functions.
- pinfo.c - helps in calling the pinfo command which gives details about the process under consideration.
- redirection.c - calls the redirection command and checks if there is redirection in a command and sets input and output streams accoridngly.

### Commands implemented :

- cd - cd command changes the directory. The cd command has been implemented with the flags -  { cd . , cd .. , cd - , cd ~ , cd <directory> }.
- pwd - pwd helps in printing the absolute path of the current working directory.
- ls - ls helps in listing all the files and directories under the current working directory. The ls command has been implemented with the flags - { ls , ls -a , ls -l , ls -al , ls -la , ls ~ , ls . , ls .. , ls <directory> }.
- echo - echo helps in printing a string on the terminal, it neglects tabs and spaces.

      Usage :  echo "string"

- pinfo - pinfo command can be used as pinfo or pinfo <pid>. The pinfo command gives us the information about the process that is specified.
- Foreground Processes - These are processes that take control of the terminal until they are executed completely (Terminated). These have been implemented using execvp.

      Usage : sleep 100

- Background Processes - These are the processes that are executed in the background and give us the control over the terminal. These can be identified by the last character '&'.

      Usage : sleep 100 &

- repeat - repeat command executes a particular command multiple times

      Usage : repeat 2 echo "hi"

- history - history command can be used in two ways, history and history <num>. The history command returns the last 'num' commands entered and preserves it over multiple terminal sessions. When num is not specified it return last 10 commands executed.
- Input/Output redirection : These allows us to redirect input or output into different input/output streams like files. I/O redirection has been implemented using '<' , '>' and '>>'.

      Usage : cat < a.txt > b.txt         sort < a.txt >> b.txt

- Piping and piping with redirection : piping has been implemented and can accessed using '|' separator.

      Usage : cat < in.txt | wc -l > lines.txt

- jobs : jobs prints the list of the currently running/stopped processes with their pids in alphabetically sorted order. jobs also has 2 flags '-r' and '-s' that allows us to view running/stopped processes separately.

      Usage : jobs -r        jobs             jobs -s

- sig : It takes the job number assigned by the shell shown in jobs and sends the corresponding signal to that particular process.

      Usage : sig 2 9

- fg : Brings the running or stopped background job corresponding to the job number to the foreground and changes its state to running.

      Usage : fg 4

- bg : bg changes the state of a stopped background job to running (in the background).

      Usage : bg 1

- replay : replay executes a command for a particular interval of time for a certain period of time.

      Usage : replay -command echo "hi" -interval 3 -period 6

- quit : helps us to quit from the current shell session.

### Signal handling :

The C shell also handles the signals Ctrl C, Ctrl Z and Ctrl D.

- Ctrl C interrupts the current foreground process by sending it a SIG_INT signal.
- Ctrl Z pushes the current running foreground process into the background and changes the state from running to stopped.
- Ctrl D logs the user out of the shell.

### Coding Style :

This code is completely modular and is distributed over multiple .c files for each of the functionality. The header.h consists of all the function prototypes and the global variables. The main.c calls the prompt which in turn calls the exec_com function which calls the respective functionality that has been requested. 

### Assumptions made :

- The shell is run in the directory that it has been cloned into.
- history.txt is already present in the directory that it has been cloned into.
- Files and directory names do not contain special characters.
- redirection operator '>' and '>>' does not contain multiple output files, if there are multiple output files then the last file is considered.
- Commands that may not be executed successfully are also stored in history.txt.