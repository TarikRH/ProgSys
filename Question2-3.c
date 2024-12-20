#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

#define SIZE 4096



int main() {
    char buf[SIZE];
    ssize_t bytes_read;
    const char *prompt;
    const char *message = "$ ./enseash \nBienvenue dans la shell ENSEA. \nPour quitter, tapez 'exit'\n";
    const char *message_exit = "Bye bye...\n";


    write(STDOUT_FILENO, message, strlen(message)); // Write the introduction to the shell


    while(1){
        write(STDOUT_FILENO, "enseash % ", 10);

        bytes_read = read(STDIN_FILENO, buf, SIZE-1);  // Reads the input command of the user
        buf[bytes_read]='\0';
        buf[strcspn(buf,"\n")]='\0';

    if (strcmp(buf,"exit")==0){ // If the written command corresponds to "exit", writes the exit message
        write(STDOUT_FILENO,message_exit,strlen(message_exit));
        exit(EXIT_SUCCESS);
    }

    int argc = 0;
    char *argv[SIZE] = {};
    char *token = strtok(buf, " ");

    // Configuration of argv and splitting it in two parts (command and arguments) [Question 2 and 6 at the same time]
    while (token != NULL && argc < ((SIZE)-1))
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    if (argc == 0)
    { // Deals with the case when pressing "Enter"
        continue;
    }



    pid_t process = fork();

    if (process < 0)
    { // Handles possible errors when calling the fork
        perror("Fork failed");
        return -1;
    }

    if (process == 0) { // Child Process
        execvp(argv[0], argv);


        perror("Error: Command not found");
        exit(EXIT_FAILURE);
    } else { // Parent process
        int status;
        waitpid(process, &status, 0);
        }
    
        
    }
    exit(EXIT_SUCCESS);
}
